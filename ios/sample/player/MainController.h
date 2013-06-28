
# ifndef MAIN_CTLR
# define MAIN_CTLR

# include "File+NNT.h"
# include "AudioPlayer.h"
# include "ColorPalette.h"

NNTAPP_BEGIN

class WaveView
: public ui::View<WaveView>
{
public:
    
    WaveView();
    void layout_subviews();
    
    virtual void draw(CGContextRef, CGRect const&);
    
    void add(real);
    
protected:
    
    core::vector<real> vals;
    
};

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    void layout_subviews();

    WaveView wave;
    ui::ProgressControl ctl_progress;
    ui::BevelButton btn_play;
    ui::BevelButton btn_stop;

protected:
    
    void cb_bkg();
    
    core::Timer _tmr_bkg;
    core::ColorWheel _cw;
    
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    ~MainController();
    void view_loaded();
    
protected:
    
    void act_play();
    void act_pause();
    void act_resume();
    void act_stop();
    void cb_progress();
    
protected:
    
    core::Timer _tmr_play;
    core::File _fd;
    audio::Player _player;    
    
};

NNTAPP_END

# endif
