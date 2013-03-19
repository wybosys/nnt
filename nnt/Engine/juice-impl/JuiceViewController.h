
# ifndef __JUICE_VIEWCONTROLLER_6DD0E277F1164031965C5D2528F5DDD3_H_INCLUDED
# define __JUICE_VIEWCONTROLLER_6DD0E277F1164031965C5D2528F5DDD3_H_INCLUDED

# import "Juice.hpp"
# import "../../UIKit/UIView+NNT.h"
# import "../../UIKit/UIViewController+NNT.h"

NNT_BEGIN_HEADER_CXX JUICE_BEGIN

using namespace ::juice;

struct _Types
{
    typedef ::juice::ColorRGBA<float> color_type;
    typedef ::juice::Vertex3d<float> vertex_type;
    typedef uint index_type;
    typedef ::juice::cocoa::Matrix matrix_type;
    typedef ::juice::Rect<vertex_type, ::juice::Size2d<float> > viewport_type;
    typedef ::juice::BoundingBox<vertex_type> bounding_type;
    typedef ::nnt::core::vector< ::juice::renderentity_wrapper> entities_type;
    typedef ::nnt::core::vector<vertex_type> vertices_type;
    typedef ::nnt::core::vector<index_type> indexies_type;
    typedef ::nnt::core::vector<color_type> colors_type;
};

class Material
: public ::juice::Material<Material, _Types>
{
};

struct Types
: _Types
{
    typedef Material material_type;
};

class Driver
: public ::juice::CococaDriver<Driver, Types>
{
    typedef ::juice::CococaDriver<Driver, Types> super;
    
public:
    
    Driver(Driver* obj): super(obj) 
    {
        PASS;
    }    
    
    ~Driver()
    {
        PASS;
    }

};

class Camera
: public ::juice::CameraFlat<Camera, Types>
{    
    typedef ::juice::CameraFlat<Camera, Types> super;
    
public:
    
    Camera()
    {
        PASS;
    }
    
    ~Camera()
    {
        PASS;
    }
    
};

class OriginCamera
: public ::juice::CameraFlat<OriginCamera, Types>
{    
    typedef ::juice::CameraFlat<OriginCamera, Types> super;
    
public:
    
    OriginCamera()
    {
        PASS;
    }
    
    ~OriginCamera()
    {
        PASS;
    }
    
    void set_viewport(viewport_type const& vp)
    {
        super::set_viewport(vp);
        
        int x = -vp.size.w * .5f;
        int y = -vp.size.h * .5f;
        _position.x = _target.x = x;
        _position.y = _target.y = y;
    }
    
};

class Light
: public ::juice::Light<Light, Types>
{
public:
    
    Light() 
    {
        PASS;
    }
    
    ~Light()
    {
        PASS;
    }
    
};

class Tree
: public ::juice::Tree<Tree, Types>,
public ::juice::TreeRender<Tree, Types>
{
    typedef ::juice::TreeRender<Tree, Types> render_type;
    
public:
    
    Tree()
    {
        PASS;
    }
    
    ~Tree()
    {
        PASS;
    }
    
    entity_type* collision(Camera::line_type* line)
    {
        return render_type::collision(this, line);
    }
    
};

template <typename implT>
class ScreenManager
: public ::juice::ScreenManager<implT, Driver>
{
public:
    
    typedef Tree tree_type;
    
    ScreenManager()
    {
        PASS;
    }
    
    ~ScreenManager()
    {
        this->stop();
    }
    
    void begin_frame()
    {
        this->_painter()->set_background(backgroundColor);
        cast_pointer(jimpl->camera)->see(this->_painter());
    }
    
    void next_frame()
    {
        tree.render(this->_painter(), &tree, &this->_renderinfo);
    }
    
    Types::color_type backgroundColor;
    tree_type tree;
    
};

template <typename implT, typename screenmanagerT>
class View
: public ::nnt::ui::View<implT>
{
    typedef ::nnt::ui::View<implT> super;
    typedef View<implT, screenmanagerT> self_type;
    
public:
    
    typedef screenmanagerT screenmanager_type;
    
    View()
    {
        PASS;
    }
    
    void set_frame(cg::Rect const& frame)
    {
        super::set_frame(frame);
        
        typename screenmanagerT::driver_type::viewport_type vp;
        vp.origin.x = vp.origin.y = 0;
        vp.size.w = frame.width();
        vp.size.h = frame.height();
        
        cast_pointer(_scrmgr.camera)->set_viewport(vp);
    }    
    
    void draw(CGContextRef, CGRect const&)
    {
        //trace_msg(@"update screen manager.");
        _scrmgr.update();     
        _scrmgr.flush();
    }
    
    screenmanager_type const& screenManager() const
    {
        return _scrmgr;
    }
    
    screenmanager_type& screenManager()
    {
        return _scrmgr;
    }
    
    void layout_subviews()
    {
        PASS;
    }
    
    void* collision(CGPoint const& _pt)
    {
        CGPoint pt = cast_pointer(_scrmgr.camera)->location_in(_pt);
        Camera::line_type line = cast_pointer(_scrmgr.camera)->nfline(pt);
        return _scrmgr.tree.collision(&line);
    }
    
protected:
    screenmanagerT _scrmgr;
};

template <typename implT, typename viewT>
class ViewController
: public ::nnt::ui::Controller<implT, viewT>
{
    typedef ::nnt::ui::Controller<implT, viewT> super;
    typedef ViewController<implT, viewT> self_type;
    
public:
    
    typedef viewT view_type;    
    
    ViewController()
    {
        this->register_signal(kSignalSelectChanged);
    }
    
    ~ViewController()
    {
        this->disconnect(this);
    }
    
    void view_loaded()
    {
        super::impl()->view().screenManager().set_drawable(*super::impl()->view());
        super::impl()->view().screenManager().resume();
        
        this->connect(kSignalViewAppear, _action(self_type::act_appear), this);
        this->connect(kSignalViewDisappear, _action(self_type::act_disappear), this);               
        this->view().connect(kSignalViewClicked, _action(self_type::act_clicked), this);
    }
    
    typename view_type::screenmanager_type::tree_type::entity_type const& tree_entity(void* obj) const
    {
        return *((typename view_type::screenmanager_type::tree_type::entity_type*)obj);
    }
    
    void* tree_object(void* obj) const
    {
        return **((typename view_type::screenmanager_type::tree_type::entity_type*)obj);
    }
    
protected:
    
    void act_appear(EventObj&)
    {
        //trace_msg(@"resume screen manager");
        super::impl()->view().screenManager().resume();
    }
    
    void act_disappear(EventObj&)
    {
        //trace_msg(@"suspend screen manager");
        super::impl()->view().screenManager().suspend();
    }
    
    void act_clicked(EventObj& evt)
    {
        ns::Set touches(evt.result());
        ui::Touch touch(touches.any());
        CGPoint pt = touch.location(this->view());
        void* obj = this->view().collision(pt);        
        if (obj) {
            this->emit(kSignalSelectChanged, pointerAsObj(obj));
        } else {
            this->emit(kSignalSelectChanged, NULL);
        }        
    }
    
};

NNT_BEGIN_NS(spirit)

class Translate
: public ::juice::spirit::Translate<Translate, Types>
{
    
};

class Rotate
: public ::juice::spirit::Rotate<Rotate, Types>
{
    
};

NNT_END_NS

JUICE_END NNT_END_HEADER_CXX

# endif