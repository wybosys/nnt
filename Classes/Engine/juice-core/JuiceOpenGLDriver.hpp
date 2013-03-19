
# ifndef __JUICE_OPENGL_DRIVER_43B0953396B442FBAE0FF95F8458B1D4_H_INCLUDED
# define __JUICE_OPENGL_DRIVER_43B0953396B442FBAE0FF95F8458B1D4_H_INCLUDED

# include "JuiceDriver.hpp"

# ifdef WSI_TARGET_IOS
#   define OPENGLES 1
#   define OPENGLES_1 1
//#   define OPENGLES_2 1
# endif

# ifdef WSI_MACH
#   ifdef WSI_TARGET_IOS
#     ifdef WSI_OBJC
#       include <OpenGLES/EAGL.h>
#       include <OpenGLES/EAGLDrawable.h>
#     endif
#     ifdef OPENGLES_1
#       include <OpenGLES/ES1/gl.h>
#       include <OpenGLES/ES1/glext.h>
#     endif
#     ifdef OPENGLES_2
#       include <OpenGLES/ES2/gl.h>
#       include <OpenGLES/ES2/glext.h>
#     endif
#   else
#     include <OpenGL/OpenGL.h>
#     include <OpenGL/gl.h>
#     include <OpenGL/glext.h>
#     include <OpenGL/glu.h>
//#     include <OpenGL/gl3ext.h>
//#     include <OpenGL/gl3.h>
//#     include <OpenGL/gluMacro.h>
#   endif
# endif

template <typename valT> struct _glvaluetype {};

# ifdef GL_FLOAT
template <> struct _glvaluetype<float> { enum { GL_VALUETYPE = GL_FLOAT }; };
# endif

# ifdef GL_DOUBLE
template <> struct _glvaluetype<double> { enum { GL_VALUETYPE = GL_DOUBLE }; };
# endif

# ifdef GL_UNSIGNED_INT
template <> struct _glvaluetype<uint> { enum { GL_VALUETYPE = GL_UNSIGNED_INT }; };
# endif

# ifdef GL_UNSIGNED_BYTE
template <> struct _glvaluetype<ubyte> { enum { GL_VALUETYPE = GL_UNSIGNED_BYTE }; };
# endif

# ifdef WSI_DEBUG
#   define OGLERRCHECK this->_error_check();
# else
#   define OGLERRCHECK
# endif

JUICE_BEGIN

template <typename implT, typename typesT, typename archT>
class _opengl_Driver
: public Driver<implT, typesT, archT>
{
    typedef Driver<implT, typesT, archT> super;
    
public:
    
    typedef typename super::context_type context_type;
    typedef typename super::vectorcomp_type vectorcomp_type;
    typedef typename super::vertex_type vertex_type;
    typedef typename super::index_type index_type;
    typedef typename super::color_type color_type;
    typedef typename super::colorcomp_type colorcomp_type;
    typedef typename super::matrix_type matrix_type;
    typedef typename super::viewport_type viewport_type;
    
    _opengl_Driver()
    : _len_vertexies(0), _len_indexies(0), _len_normals(0),
    _ptr_indexies(0)
    {
    }
    
    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        OGLERRCHECK;
    }
    
    void set_background(color_type const& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        OGLERRCHECK;
    }
    
    void draw_points()
    {
        glDrawElements(GL_POINTS, _len_indexies, _glvaluetype<index_type>::GL_VALUETYPE, _ptr_indexies);
        OGLERRCHECK;
    }
    
    void draw_triangles()
    {        
        glDrawElements(GL_TRIANGLES, _len_indexies, _glvaluetype<index_type>::GL_VALUETYPE, _ptr_indexies);
        OGLERRCHECK;
    }
    
    void draw_looplines()
    {
        glDrawElements(GL_LINE_LOOP, _len_indexies, _glvaluetype<index_type>::GL_VALUETYPE, _ptr_indexies);
        OGLERRCHECK;
    }        
    
    void flush()
    {
        glFlush();
        OGLERRCHECK;
    }
    
    void set_viewport(viewport_type const& vp)
    {
        glViewport(vp.origin.x, vp.origin.y, vp.size.w, vp.size.h);
    }
    
# ifdef WSI_DEBUG
    void _error_check()
    {
        int err = glGetError();
        if (err)
        {
            printf("opengl error: %x.\n", err);            
        }
    }        
# endif
    
protected:
    
    void _finish()
    {
        glFinish();
    }
    
protected:
    usize _len_vertexies, _len_indexies, _len_normals;
    index_type const* _ptr_indexies;
    
};

JUICE_END

# ifdef WSI_MACH
#   ifdef WSI_TARGET_IOS
#     ifdef OPENGLES_1
#       include "JuiceOpenGLES1.hpp"
#     endif
#     ifdef OPENGLES_2
#       include "JuiceOpenGLES2.hpp"
#     endif
#   else
#     include "JuiceOpenGLPCDriver.hpp"
#   endif
#   include "JuiceOpenGLDarwinDriver.hpp"
# endif

JUICE_BEGIN

# ifndef JUICE_OPENGL_DRIVER_IMPL
#   define JUICE_OPENGL_DRIVER_IMPL _opengl_Driver<implT, typesT, _noarch_types>
# endif

template <typename implT, typename typesT>
class OpenGLDriver
: public JUICE_OPENGL_DRIVER_IMPL
{
    
    typedef JUICE_OPENGL_DRIVER_IMPL super;
    
public:
    
    OpenGLDriver(implT* obj)
    : super(obj)
    {
        obj->_init();
    }
    
    ~OpenGLDriver()
    {
        jimpl->_finish();
    }
    
};

JUICE_END

# endif