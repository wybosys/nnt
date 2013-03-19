
# ifndef __JUICE_OPENGLES_2_560DCED3B5904A11A5D1E04E200E6957_H_INCLUDED
# define __JUICE_OPENGLES_2_560DCED3B5904A11A5D1E04E200E6957_H_INCLUDED

# include "JuiceGlslLibrary.hpp"

JUICE_BEGIN

template <typename implT, typename typesT, typename archT>
class _opengles2x_Driver
: public _opengl_Driver<implT, typesT, archT>
{
    typedef _opengl_Driver<implT, typesT, archT> super;
    
public:
    
    enum { GLES_VERSION = 2 };
    
    typedef typename super::context_type context_type;
    typedef typename super::vectorcomp_type vectorcomp_type;
    typedef typename super::vertex_type vertex_type;
    typedef typename super::index_type index_type;
    typedef typename super::color_type color_type;
    typedef typename super::colorcomp_type colorcomp_type;
    typedef typename super::matrix_type matrix_type;
    
    _opengles2x_Driver()
    : _glsl_handle(0), _glsl_directvextex(0), _glsl_directfrag(0)
    {
        PASS;
    }
    
    void init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    
    void push_matrix()
    {
        
    }
    
    void pop_matrix()
    {
        
    }
    
    void set_matrix(matrix_type const&)
    {
        
    }
    
    void mult_matrix(matrix_type const&)
    {
        
    }
    
    void set_color(color_type const& color)
    {

    }
    
    void add_vertices(vectorcomp_type const* ptr, usize sz)
    {
        _prepare_glsl();
        
        // bind data.
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sz, ptr, GL_STATIC_DRAW);
        
        // set.
        glVertexAttribPointer(_glsl_vextexslot, vertex_type::COUNT, _glvaluetype<vectorcomp_type>::GL_VALUETYPE, GL_FALSE, vertex_type::SIZE, 0);
        OGLERRCHECK;
    }
    
    void add_normals(vectorcomp_type const*, usize)
    {
        PASS;
    }
    
    void add_indexies(index_type const* ptr, usize sz)
    {
        _prepare_glsl();
        
        // bind data.
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sz, ptr, GL_STATIC_DRAW);  
        OGLERRCHECK;
        
        super::_ptr_indexies = NULL;
        super::_len_indexies = sz;
    }
    
    void add_colors(colorcomp_type const* ptr, usize sz)
    {
        _prepare_glsl();
        
        // set.
        glVertexAttribPointer(_glsl_colorslot, color_type::COUNT, _glvaluetype<colorcomp_type>::GL_VALUETYPE, GL_FALSE, color_type::SIZE, ptr);
        OGLERRCHECK;
    }
    
    void purge()
    {
        
    }
    
public:
    
    GLuint compile_shader(GLenum type, char const* data, GLint dlen) const
    {
        GLuint handle = glCreateShader(type);
        glShaderSource(handle, 1, &data, &dlen);
        glCompileShader(handle);
        GLint suc;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &suc);
        if (GL_FALSE == suc)
        {
            GLchar messages[256];
            glGetShaderInfoLog(handle, sizeof(messages), 0, &messages[0]);
            printf("failed to compile shader: %s\n.", messages);
            return 0;
        }
        return handle;
    }    
    
protected:
    
    void _prepare_glsl()
    {
        if (_glsl_handle)
            return;
        implT* obj = (implT*)this;
        _glsl_handle = glCreateProgram();
        if (0 == _glsl_directvextex)
            _glsl_directvextex = obj->compile_shader(GL_VERTEX_SHADER, glsl::direct_vextex.c_str(), glsl::direct_vextex.length());
        if (0 == _glsl_directfrag)
            _glsl_directfrag = obj->compile_shader(GL_FRAGMENT_SHADER, glsl::direct_fragment.c_str(), glsl::direct_fragment.length());
        glAttachShader(_glsl_handle, _glsl_directvextex);
        glAttachShader(_glsl_handle, _glsl_directfrag);
        glLinkProgram(_glsl_handle);
        
        // check
        GLint suc;
        glGetProgramiv(_glsl_handle, GL_LINK_STATUS, &suc);
        if (GL_FALSE == suc)
        {
            GLchar messages[256];
            glGetProgramInfoLog(_glsl_handle, sizeof(messages), 0, &messages[0]);
            printf("failed to init shader program: %s .\n", messages);
            return;
        }
        
        glUseProgram(_glsl_handle);
        
        // get slot.
        _glsl_vextexslot = glGetAttribLocation(_glsl_handle, glsl_source_position);
        _glsl_colorslot = glGetAttribLocation(_glsl_handle, glsl_source_color);
        glEnableVertexAttribArray(_glsl_vextexslot);
        glEnableVertexAttribArray(_glsl_colorslot);
        
        _glsl_matprojectslot = glGetUniformLocation(_glsl_handle, glsl_projection_matrix);
        _glsl_matmodelviewslot = glGetUniformLocation(_glsl_handle, glsl_modelview_matrix);
    }
    
protected:
    GLuint _glsl_handle, _glsl_directvextex, _glsl_directfrag, _glsl_vextexslot, _glsl_colorslot, _glsl_matprojectslot, _glsl_matmodelviewslot;
};

JUICE_END

# endif