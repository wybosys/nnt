
# ifndef __JUICE_SCREENMANAGER_A806F4C93DFF4324B3A2A526E5B263D3_H_INCLUDED
# define __JUICE_SCREENMANAGER_A806F4C93DFF4324B3A2A526E5B263D3_H_INCLUDED

# include "../../Core/Time+NNT.h"
# include "../../Core/Task+NNT.h"

JUICE_BEGIN

JUICE_EXCEPTION(thread_failed);

template <typename scrmgrT>
class _screenManagerTask
: public ::wsi::core::Task
{
    typedef ::wsi::core::Task task_type;
    
public:    
    
    _screenManagerTask()
    : _suspended(false)
    {
        PASS;
    }
    
    ~_screenManagerTask()
    {
        if (_suspended)
            resume();
    }
    
    //! task main routine.
    virtual int main();
    
    //! attach a screen manager.
    scrmgrT* scrmgr;
    
public:
    
    void resume()
    {
        if (_suspended == false)
            return;
        _suspended = false;
        
        _loop.unlock();
        //task_type::resume();       
    }
    
    void suspend()
    {
        if (_suspended == true)
            return;
        _suspended = true;
        
        _loop.lock();
        //task_type::suspend();        
    }
    
    void stop()
    {
        if (_suspended == true)
            resume();
        
        task_type::stop();
    }
    
protected:
    
    //! mutex for control render loop.
    ::wsi::core::Mutex _loop;
    
    //! suspended.
    bool _suspended;
    
};

template <typename implT, typename driverT, 
typename renderinfoT = renderinfo >
class ScreenManager
: public RefObject<implT>
{
    typedef ScreenManager<implT, driverT, renderinfoT> self_type;
    typedef _screenManagerTask<implT> task_render;
    friend class _screenManagerTask<implT>;
    
public:
    typedef driverT driver_type;
    typedef renderinfoT renderinfo_type;
    
public:    
    
    ScreenManager()
    : 
    fps_limit(60), 
    fps_real(0), 
    _drawable(NULL),
    _task_render(NULL)
    {        
        _drv_ui = new driver_type(NULL);
        memset(&_renderinfo, 0, sizeof(_renderinfo));        
    }
    
    ~ScreenManager()
    {
        stop();
        zero_drop(_drv_ui);
    }
    
public:
    
    //! create render thread.
    void render()
    {
        this->stop();
        
        // increase refcount.
        this->grab();
        
        // start render task.
        _task_render = new task_render;
        _task_render->scrmgr = (implT*)this;
        _task_render->start();        
    }
    
    //! render once.
    void render_frame(bool fps = false)
    {
        implT* scrmgr = (implT*)this;             
        
        // begin time.        
        scrmgr->_renderinfo.frame_begin = ::wsi::get_tick_count();
        
        // lock painter.
        scrmgr->_lock_painter();
                                
        // prepare.
        scrmgr->prepare_frame();
        
        // save state.
        scrmgr->_painter()->save_state();
            
        // begin render frame.     
        scrmgr->begin_frame();
        
        // render current frame.
        scrmgr->next_frame();                                      
            
        // end current frame.
        scrmgr->end_frame();
        
        // restore state.
        scrmgr->_painter()->restore_state();        
        
        // collect frame.
        scrmgr->collect_frame();        
        
        // unlock painter.
        scrmgr->_unlock_painter();
        
        // end time.
        scrmgr->_renderinfo.frame_end = ::wsi::get_tick_count();        
        scrmgr->_renderinfo.frame_cost = scrmgr->_renderinfo.frame_end - scrmgr->_renderinfo.frame_begin;        
        scrmgr->_renderinfo.frame_time = ::wsi::millisec_tick_count(scrmgr->_renderinfo.frame_cost);  
        
        // limit fps.
        if (fps && scrmgr->fps_limit)
        {
            int millisec_per_frame = 1e3 / scrmgr->fps_limit;
            int dif_per_frame = millisec_per_frame - scrmgr->_renderinfo.frame_time;
            if (dif_per_frame > 0)
            {
                // frame is fast.
                scrmgr->_renderinfo.frame_time = millisec_per_frame;
                // wait for frame.
                usleep(dif_per_frame * 1e3);
            }
        }
            
        // calc fps real.
        if (fps)
        {
            scrmgr->fps_real = 1e3 / scrmgr->_renderinfo.frame_time;    
        }
    }
    
    //! stop render.
    void stop()
    {        
        _task_mtx.lock();
        
        if (_task_render == NULL)
        {
            _task_mtx.unlock();
            return;        
        }
               
        _task_render->stop();
        _task_render->wait();
        _task_render->drop();
        _task_render = NULL;
        _task_mtx.unlock();
    }
    
    //! suspend render.
    void suspend()
    {
        _task_mtx.lock();
        
        if (_task_render == NULL)
        {
            _task_mtx.unlock();
            return;
        }
        
        _task_render->suspend();
        
        _task_mtx.unlock();
    }
    
    //! resume.
    void resume()
    {        
        if (_task_render)
            _task_render->resume();
        else
            this->render();
    }
    
    //! set drawable.
    void set_drawable(typename driver_type::drawable_type ptr)
    {        
        _drawable = ptr;
        _drv_ui->set_drawable(_drawable);
    }
    
    //! update.
    void update()
    {
        _drv_ui->set_current();
        _drv_ui->update();
    }
    
    //! flush.
    void flush()
    {
        _drv_ui->set_current();
        _drv_ui->flush();
    }
    
    //! clear.
    void clear_drawable()
    {
        _drv_ui->clear_drawable();
    }
    
protected:
    
    //! lock painter.
    void _lock_painter()
    {
        _painter()->lock();
        _uipainter()->lock();
    }
    
    //! unlock painter.
    void _unlock_painter()
    {
        _painter()->unlock();
        _uipainter()->unlock();
    }
    
    //! painter.
    driver_type* _painter() const
    {
        return (driver_type*)_drv_thd;
    }
    
    //! ui.
    driver_type* _uipainter() const
    {
        return (driver_type*)_drv_ui;
    }
    
    void prepare_scene()
    {
        _drv_thd = new driver_type(_drv_ui);
        _drv_thd->set_drawable(_drawable);
    }
    
    void collect_scene()
    {
        zero_drop(_drv_thd);
    }
    
    void prepare_frame()
    {
        _drv_thd->set_current();
        _drv_thd->update();
        _drv_thd->clear(); 
    }
    
    void begin_frame() {}
    void end_frame() {}
    
    void collect_frame()
    {
        _drv_thd->flush();        
    }
    
    void next_frame();    
    void pre_frame();
    
protected:
    
    driver_type *_drv_ui, *_drv_thd;
    typename driver_type::drawable_type _drawable;
    renderinfo_type _renderinfo;
    task_render* _task_render;
    
private:
    
    ::wsi::core::Mutex _task_mtx;

public:
    
    real fps_limit, fps_real;
    
};

template <typename scrmgrT>
inline_impl int _screenManagerTask<scrmgrT>::main()
{
# ifdef NNT_OBJC
    autocollect;
# endif
        
    // prepare for scene render.
    scrmgr->prepare_scene();
    
    // render loop.
    while (!this->complete())
    {                          
        _loop.lock();
        
# ifdef NNT_OBJC
        autocollect;
# endif
        
        // prepare painter.
        scrmgr->_painter()->prepare();        
        
        // render single frame with fps limit.
        if (scrmgr->_painter()->valid())
            scrmgr->render_frame(true);
        
# ifdef NNT_DEBUG
        // print fps.
        //printf("fps: %.0f\n", scrmgr->fps_real);
# endif
        
        _loop.unlock();
    };
    
    // collect scene.
    scrmgr->collect_scene();
    
    // decrease refcount.
    scrmgr->drop();
    
    return 0;
}

JUICE_END

# endif
