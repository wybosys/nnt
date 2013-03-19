
# ifndef __JUICE_OPENGLDARWIN_49CF1F06A5724334BCFA60084BC3953C_H_INCLUDED
# define __JUICE_OPENGLDARWIN_49CF1F06A5724334BCFA60084BC3953C_H_INCLUDED

JUICE_BEGIN

# if defined(NNT_OBJC) && defined(NNT_TARGET_MAC)

typedef struct {
    typedef NSView* drawable_type;
    typedef NSOpenGLContext* context_type;
} _macgl_types;

template <typename implT, typename typesT>
class _macgl_Driver
: public _openglpc_Driver<implT, typesT, _macgl_types>
{
    typedef _openglpc_Driver<implT, typesT, _macgl_types> super;
    
public:
    
    typedef _macgl_types::drawable_type drawable_type;
    typedef _macgl_types::context_type context_type;
    
    _macgl_Driver(implT* obj)
    {
        typedef ::wsi::ntl::value_type<context_type>::type context_impl;
        
        NSOpenGLPixelFormatAttribute attributes[] = { 
            NSOpenGLPFADoubleBuffer,
            nil 
        };
        NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        if (obj)
            _context = [[context_impl alloc] initWithFormat:pixelFormat shareContext:obj->_context];
        else
            _context = [[context_impl alloc] initWithFormat:pixelFormat shareContext:nil];
        [pixelFormat release];
        
        // set async nowait for vec.
        GLint swapInt = 0;
        [_context setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
        
        [_context makeCurrentContext];
    }
    
    ~_macgl_Driver()
    {
        zero_release(_context);
    }
    
    void set_drawable(drawable_type view)
    {
        if ([_context view] != view)
            [_context setView:view];
        
        [_context makeCurrentContext];
    }
    
    context_type get_context() const
    {
        return _context;
    }
    
    void update()
    {
        [_context update];
    }
    
    void flush()
    {
        [_context flushBuffer];
    }
    
    void clear_drawable()
    {
        [_context clearDrawable];
    }
    
    void set_current()
    {
        [_context makeCurrentContext];
    }
    
    bool valid() const
    {
        return _context != nil;
    }
    
protected:
    context_type _context;
    
};

# define JUICE_OPENGL_DRIVER_IMPL _macgl_Driver<implT, typesT>

# elif defined(NNT_OBJC) && defined(NNT_TARGET_IOS)

typedef struct {
    typedef id drawable_type;
    typedef EAGLContext* context_type;
} _iosgl_types;

template <uint ver>
struct _iosgl_version
{};

template <>
struct _iosgl_version<1>
{
    enum { GLES_VERSION = kEAGLRenderingAPIOpenGLES1 };
};

template <>
struct _iosgl_version<2>
{
    enum { GLES_VERSION = kEAGLRenderingAPIOpenGLES2 };
};

template <typename implT, typename typesT>
class _iosgl_Driver
: public
# ifdef OPENGLES_1
_opengles1x_Driver<implT, typesT, _iosgl_types>
# endif
# ifdef OPENGLES_2
_opengles2x_Driver<implT, typesT, _iosgl_types>
# endif
{
    typedef     
# ifdef OPENGLES_1
    _opengles1x_Driver<implT, typesT, _iosgl_types>
# endif
# ifdef OPENGLES_2
    _opengles2x_Driver<implT, typesT, _iosgl_types>
# endif    
    super;
    
public:
    
    typedef _iosgl_types::drawable_type drawable_type;
    typedef _iosgl_types::context_type context_type;
    
    _iosgl_Driver(implT* obj)
    : _frameBuffer(0), _renderBuffer(0), _depthBuffer(0)
    {
        typedef ::wsi::ntl::value_type<context_type>::type context_impl;
        
        if (obj == NULL)
        {
            _context = [[context_impl alloc] initWithAPI:_iosgl_version<super::GLES_VERSION>::GLES_VERSION]; 
            if (_context)
            {
                _layer = [[CAEAGLLayer alloc] init];
                _layer.opaque = YES;
            }
        }
        else
        {
            _context = [[context_impl alloc] initWithAPI:[obj->_context API]
                                              sharegroup:[obj->_context sharegroup]];
            _layer = [obj->_layer retain];
        }
        
        [context_impl setCurrentContext:_context];
    }
    
    ~_iosgl_Driver()
    {
        zero_release(_context);
        zero_release(_layer);
    }
    
    void set_drawable(drawable_type obj)
    {
        // set context.
        [EAGLContext setCurrentContext:_context]; 
        
        // had inserted.
        if (_layer.superlayer)
            return;
        
        // add layer.
        CALayer* super_layer = nil;
        if ([obj isKindOfClass:[UIView class]])
            super_layer = ((UIView*)obj).layer;
        else if ([obj isKindOfClass:[CALayer class]])
            super_layer = (CALayer*)obj;
        
        if (super_layer == nil || super_layer.superlayer)
            return;
        
        _layer.frame = super_layer.bounds;
        [super_layer addSublayer:_layer];                            
    }
    
    context_type get_context() const
    {
        return _context;
    }
    
    bool valid() const
    {
        return _context != NULL;
    }
    
    void flush()
    {
        [_context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    void update()
    {
        CALayer* super_layer = _layer.superlayer;
        if (super_layer == nil)
            return;
        CGRect oldfm = _layer.frame;
        CGRect newfm = super_layer.bounds;
        if (CGRectEqualToRect(oldfm, newfm))
            return;        
        _layer.frame = newfm;
        
        if (_renderBuffer)
            glDeleteBuffers(1, &_renderBuffer);
        if (_frameBuffer)
            glDeleteBuffers(1, &_frameBuffer);
        if (_depthBuffer)
            glDeleteBuffers(1, &_depthBuffer);
        
        // setup depth buffer.
        glGenRenderbuffers(1, &_depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,
                              (GLshort)newfm.size.width, (GLshort)newfm.size.height);
        
        // setup renderbuffer.
        glGenRenderbuffers(1, &_renderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);        
        [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_layer];          
        
        // setup framebuffer.        
        glGenFramebuffers(1, &_frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                                  GL_RENDERBUFFER, _renderBuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
                                  GL_RENDERBUFFER, _depthBuffer);        
    }
    
    void clear_drawable()
    {
        [_layer removeFromSuperLayer];
    }
    
    void set_current()
    {
        [EAGLContext setCurrentContext:_context];
    }
    
protected:
    
    context_type _context;
    CAEAGLLayer* _layer;
    GLuint _frameBuffer, _renderBuffer, _depthBuffer;
    
};

# define JUICE_OPENGL_DRIVER_IMPL _iosgl_Driver<implT, typesT>

# endif

JUICE_END

# endif