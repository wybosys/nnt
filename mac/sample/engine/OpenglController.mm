
# import <WSI/WSIFoundation.h>
# import "OpenglController.h"
# import <WSI/Engine/JuiceImpl.h>
# import <WSI/Core/WSIResource.h>

WSIAPP_BEGIN

class DriverImpl
: public juice::OpenGLDriver<DriverImpl, juice::Types>
{
    typedef juice::OpenGLDriver<DriverImpl, juice::Types> super;
    
public:
    DriverImpl(DriverImpl* obj): super(obj) 
    {
    }
    
};

class CameraImpl
//: public juice::CameraFlat<CameraImpl, juice::Types>
: public juice::CameraEye<CameraImpl, juice::Types>
{
public:
    CameraImpl()
    {
        this->set_target(vertex_type(0, 0, -1000));
    }
};

class TreeImpl
: public juice::RenderTree<TreeImpl, juice::Types>
{
public:
};

class TriangleMeshImpl
: public juice::RenderTriangleMesh<TriangleMeshImpl, juice::Types>,
public juice::spirit::Translate<TriangleMeshImpl, juice::Types>,
public juice::spirit::Rotate<TriangleMeshImpl, juice::Types>
{
    typedef juice::RenderTriangleMesh<TriangleMeshImpl, juice::Types> super;
    typedef juice::spirit::Translate<TriangleMeshImpl, juice::Types> translate_spirit;
    typedef juice::spirit::Rotate<TriangleMeshImpl, juice::Types> rotate_spirit;
    
public:
    
    TriangleMeshImpl() 
    {
        super::enable_framelines = true;
        super::color_frameline.set(0, 0, 0);
        
        translate_spirit::set_repeat(true);
        translate_spirit::set_reverse(true);
        translate_spirit::set(100, 0, 0);
        translate_spirit::set_duration(2000);
        
        rotate_spirit::set_repeat(true);
        //rotate_spirit::set_reverse(true);
        rotate_spirit::set(M_2PI, M_2PI, M_2PI);
        rotate_spirit::set_duration(2000);
    }    
    
    void render(DriverImpl* drv, juice::renderinfo* info)
    {                
        //translate_spirit::next(this, info);
        rotate_spirit::next(this, info);
     
        super::begin(drv);
        super::render(drv, info);
        super::end(drv);
    }
};

class ScreenManagerImpl
: public juice::ScreenManager<ScreenManagerImpl, DriverImpl>
{
    typedef juice::ScreenManager<ScreenManagerImpl, DriverImpl> super;
    
public:    
    
    ScreenManagerImpl()
    {
        tree = new TreeImpl;
        camera = new CameraImpl;
    }
    
    ~ScreenManagerImpl()
    {
        safe_delete(tree);
        safe_delete(camera);
    }
    
    void begin_frame()
    {
        _painter()->set_backgroundColor(1, 1, 1);
        camera->see(_painter());
        camera->see(tree);
    }
    
    void next_frame()
    {
        tree->render(_painter(), &_renderinfo);
    }
    
    TreeImpl* tree;
    CameraImpl* camera;
};

WSIAPP_END

WSIAPP_BEGIN_OBJC

@interface OpenglView : WSINSView {
    wsiapp::ScreenManagerImpl* scrMgr;
}

@property (nonatomic, readonly) wsiapp::ScreenManagerImpl* scrMgr;

@end

@implementation OpenglView

@synthesize scrMgr;

- (id)initWithZero {
    self = [super initWithZero];
    
    scrMgr = new wsiapp::ScreenManagerImpl;
    
    return self;
}

- (void)dealloc {
    safe_delete(scrMgr);
    [super dealloc];
}

- (void)setFrame:(NSRect)frameRect {
    [super setFrame:frameRect];
    
    if (scrMgr) {
        juice::Types::viewport_type vp;
        vp.origin.x = vp.origin.y = 0;
        vp.size.w = frameRect.size.width;
        vp.size.h = frameRect.size.height;
        scrMgr->camera->set_viewport(vp);
    }
}

- (void)lockFocus {
    [super lockFocus];        
    scrMgr->set_drawable(self);
    scrMgr->resume();
}

- (void)drawRect:(NSRect)dirtyRect {
    scrMgr->update();     
    scrMgr->flush();
}

- (void)viewDidMoveToWindow {
    [super viewDidMoveToWindow];
    if ([self window] == nil)
        scrMgr->clear_drawable();
}

@end

@implementation OpenglController

- (void)loadView {
    OpenglView* view = [[OpenglView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    OpenglView* view = (OpenglView*)self.view;
        
    ::juice::impl::Archive3dmax archive;
    ::wsi::core::string file = ::wsi::Resource::PathOf(
                                                       "box.3ds"
                                                       //"mulberry.3ds"
                                                       );
    if (archive.open(file))
    {
        wsiapp::TriangleMeshImpl* mesh = wsiapp::TriangleMeshImpl::New();
        if (archive.insert(mesh))
        {
            mesh->color.set(0.7, 0.7, 0.7);
            mesh->transform.scale(50, 50, 50);            
            view.scrMgr->tree->add_entity(mesh);
        }
        mesh->drop();
    }
}

@end

WSIAPP_END_OBJC