
# include "WSIFoundation.h"
# include "MainController.h"
# include "JuiceImpl.h"
# include "WSIResource.h"

WSIAPP_BEGIN

class MaterialImpl
: public ::juice::Material<MaterialImpl, ::juice::Types3d>
{
    
};

struct TypesImpl
: ::juice::Types3d
{
    typedef MaterialImpl material_type;
};

class DriverImpl
: public ::juice::OpenGLDriver<DriverImpl, TypesImpl>
{
    typedef ::juice::OpenGLDriver<DriverImpl, TypesImpl> super;
    
public:
    
    DriverImpl(DriverImpl* obj)
    : super(obj)
    {
        PASS;
    }    
    
};

class CameraImpl
: public ::juice::CameraEye<CameraImpl, TypesImpl>
//: public ::juice::CameraFlat<CameraImpl, TypesImpl>
{    
public:
    
    CameraImpl()
    {
        if (CameraImpl::ORTHO == false)
            this->set_target(vertex_type(0, 0, -1000));
    }
    
};

class LightImpl
: public ::juice::Light<LightImpl, TypesImpl>
{
public:
    
    LightImpl()
    {
        position = vertex_type(1, 1, 1, 0);
        ambient.set(0x00FF00FF);
    }
    
};

class TranslateImpl
: public ::juice::spirit::Translate<TranslateImpl, TypesImpl>
{
    
};

class RotateImpl
: public ::juice::spirit::Rotate<RotateImpl, TypesImpl>
{
    
};

class TriangleMeshImpl
: public ::juice::RenderEntity<TriangleMeshImpl, TypesImpl>,
public ::juice::TriangleMesh<TriangleMeshImpl, TypesImpl>
{
    typedef ::juice::TriangleMeshRender<TriangleMeshImpl, TypesImpl> render_type;
    typedef ::juice::TriangleMesh<TriangleMeshImpl, TypesImpl> mesh_type;
    
public:
    
    TriangleMeshImpl() 
    {        
        _sp_trans.set_repeat(true);
        _sp_trans.set_reverse(true);
        _sp_trans.set(200, 0, 0);
        _sp_trans.set_duration(1000);
        
        _sp_rotate.set_repeat(true);
        _sp_rotate.set(M_2PI, M_2PI, M_2PI);
        _sp_rotate.set_duration(2000);
        
        // load model.
        ::juice::impl::Archive3dmax archive;
        core::string file = Resource::PathOf("box.3ds");
        if (archive.open(file))
        {
            trace_msg(@"success open box.3ds.");
            if (archive.insert((mesh_type*)this))
            {
                this->material.color.set(1, 1, 1);
                this->transform.set_scale(100, 100, 100);
            }
        }
    }    
    
    void prepare(DriverImpl* drv, ::juice::renderinfo* info)
    {
        _sp_trans.next((render_type*)this, info);
        _sp_rotate.next((render_type*)this, info); 
    }
    
    void render(DriverImpl* drv, ::juice::renderinfo* info)
    {                                      
        _render_mesh.render(drv, (mesh_type*)this, info);       
        _render_frame.render(drv, (mesh_type*)this, info);
    }
    
protected:
    
    TranslateImpl _sp_trans;
    RotateImpl _sp_rotate;
    ::juice::TriangleMeshRender<TriangleMeshImpl, TypesImpl> _render_mesh;
    ::juice::FrameLinesMeshRender<TriangleMeshImpl, TypesImpl> _render_frame;
    
};

class TreeImpl
: public ::juice::Tree<TreeImpl, TypesImpl>,
public ::juice::TreeRender<TreeImpl, TypesImpl>
{
public:    
    
    TreeImpl()
    {
        ::wsiapp::TriangleMeshImpl* mesh = ::wsiapp::TriangleMeshImpl::New();
        this->add_entity((::juice::RenderEntity<TriangleMeshImpl, TypesImpl>*)mesh);
        mesh->drop();
    }
    
    bool collision(CameraImpl::line_type const* line)
    {
        TriangleMeshImpl* mesh = (TriangleMeshImpl*)this->object_at(0);
        matrix_type mat = mesh->get_transform().inverse();
        
        CameraImpl::line_type* cur_line = line->clone();
        cur_line->start = mat * cur_line->start;
        cur_line->end = mat * cur_line->end;
        
        bool suc = ::juice::bounding_collision(*cur_line, mesh->bounding);
                
        delete cur_line;
        return suc;
    }
    
};

class ScreenManagerImpl
: public ::juice::ScreenManager<ScreenManagerImpl, DriverImpl>
{    
public:    
    
    ScreenManagerImpl()
    {
        // alloc tree.
        tree = new TreeImpl;
        
        // alloc camera.
        camera = new CameraImpl;
        
        // alloc light.
        light = new LightImpl;
    }
    
    ~ScreenManagerImpl()
    {
        safe_delete(tree);
        safe_delete(camera);
        safe_delete(light);
    }
        
    void begin_frame()
    {
        // set background.
        _painter()->set_background(driver_type::color_type(.5f, .5f, .5f));
     
        // set camera.
        camera->see(_painter());
        //camera->see(tree);
        
        // set light.
        light->pack(_painter());
    }
    
    void next_frame()
    {
        tree->render(_painter(), tree, &_renderinfo);                
    }
    
    TreeImpl* tree;
    CameraImpl* camera;
    LightImpl* light;
    
};

MainView::MainView()
{
    scrMgr = new wsiapp::ScreenManagerImpl;
    set_background(ui::Color::Orange());
}

MainView::~MainView()
{
    safe_delete(scrMgr);
}

void MainView::layout_subviews()
{
    cg::Rect rc = bounds();
    ::wsiapp::TypesImpl::viewport_type vp;
    vp.origin.x = vp.origin.y = 0;
    vp.size.w = rc.width();
    vp.size.h = rc.height();
    scrMgr->camera->set_viewport(vp);
    scrMgr->resume();
}

void MainView::draw(CGContextRef, CGRect const&)
{
    scrMgr->update();
    scrMgr->flush();
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().scrMgr->set_drawable(view());    
    view().connect(kSignalViewClicked, _action(_class::act_clicked), this);
}

void MainController::act_clicked(EventObj& evt)
{
    ns::Set touches(evt.result());
    cg::Point pt = ui::Touch(touches.any()).location(view());
    pt = view().scrMgr->camera->location_in(pt);
    ::wsiapp::CameraImpl::line_type line = view().scrMgr->camera->nfline(pt);
    if (view().scrMgr->tree->collision(&line))
    {
        trace_msg(@"success.");
    } else
    {
        trace_msg(@"failed.");
    }
}

WSIAPP_END
