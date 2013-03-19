
# ifndef __JUICE_OPENGLPC_6BFD1B5F06FF4C1898C0CF525D763E8E_H_INCLUDED
# define __JUICE_OPENGLPC_6BFD1B5F06FF4C1898C0CF525D763E8E_H_INCLUDED

JUICE_BEGIN

template <typename implT, typename typesT, typename archT>
class _openglpc_Driver
: public _opengl_Driver<implT, typesT, archT>
{
    typedef _opengl_Driver<implT, typesT, archT> super;
    
public:
    
    typedef typename super::context_type context_type;
    typedef typename super::vectorcomp_type vectorcomp_type;
    typedef typename super::vertex_type vertex_type;
    typedef typename super::index_type index_type;
    typedef typename super::color_type color_type;
    typedef typename super::colorcomp_type colorcomp_type;
    typedef typename super::matrix_type matrix_type;        
        
    void set_color(color_type const& color)
    {
        glColor4f(color.r, color.g, color.b, color.a);
        OGLERRCHECK;
    }
    
    void add_vertices(vectorcomp_type const* pointer, usize length)
    {
        glEnableClientState(GL_VERTEX_ARRAY); 
        OGLERRCHECK;
        glVertexPointer(vertex_type::COUNT, _glvaluetype<vectorcomp_type>::GL_VALUETYPE, vertex_type::SIZE, pointer);
        OGLERRCHECK;
        super::_len_vertexies = length;    
    }    
    
    void add_normals(vectorcomp_type const* pointer, usize length)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        OGLERRCHECK;
        glNormalPointer(_glvaluetype<vectorcomp_type>::GL_VALUETYPE, vertex_type::SIZE, pointer);   
        OGLERRCHECK;
        super::_len_normals = length;
    }
    
    void add_indexies(index_type const* pointer, usize length)
    {
        super::_ptr_indexies = pointer;
        super::_len_indexies = length;
    }
    
    void add_colors(colorcomp_type const* pointer, usize length) 
    {
        glEnableClientState(GL_COLOR_ARRAY);
        OGLERRCHECK;
        glColorPointer(color_type::COUNT, _glvaluetype<colorcomp_type>::GL_VALUETYPE, color_type::SIZE, pointer);
        OGLERRCHECK;
    }
    
    void push_matrix()
    {
        glPushMatrix();
        OGLERRCHECK;
    }
    
    void pop_matrix()
    {
        glPopMatrix();
        OGLERRCHECK;
    }
    
    void set_matrix(matrix_type const& mat)
    {
        glLoadMatrixf(mat.data());
        OGLERRCHECK;
    }
    
    void mult_matrix(matrix_type const& mat)
    {
        glMultMatrixf(mat.data());
        OGLERRCHECK;
    }        
    
    void save_state()
    {
        glPushMatrix();
        OGLERRCHECK;
    }
    
    void restore_state()
    {
        glPopMatrix();
        OGLERRCHECK;
    }
    
    void purge_elements()
    {
        glDisableClientState(GL_VERTEX_ARRAY);
        OGLERRCHECK;
        glDisableClientState(GL_COLOR_ARRAY);
        OGLERRCHECK;
        glDisableClientState(GL_NORMAL_ARRAY);
        OGLERRCHECK;
    }
    
    void prepare()
    {        
        glDisable(GL_LIGHTING);
        uint cnt_lights = _lights.size();
        _lights.clear();
        while (cnt_lights--)
        {
            glDisable(GL_LIGHT0 + cnt_lights);
        }
    }
    
    template <typename lightT>
    void set_light(lightT* light)
    {    
        if (_lights.size() >= GL_MAX_LIGHTS)
            return;
        
        if (_lights.find(light) == _lights.end())
        {
            light->index = _lights.size();
            _lights.insert(light);                        
        }
        
        if (glIsEnabled(GL_LIGHTING) == false)
        {
            glEnable(GL_LIGHTING);
            OGLERRCHECK;
        }
        
        // set light.
        GLint light_no = GL_LIGHT0 + light->index;
        
        if (glIsEnabled(light_no) == false)
        {
            glEnable(light_no);
            OGLERRCHECK;
        }
        
        glLightfv(light_no, GL_POSITION, light->position.data());
        OGLERRCHECK;
        
        glLightfv(light_no, GL_AMBIENT, light->ambient.data());
        OGLERRCHECK;
    }
    
    template <typename materialT>
    void set_material(materialT* mat)
    {
        // check light.
        if (mat->lightable == true)
        {
            if (glIsEnabled(GL_LIGHTING) == false)
                glEnable(GL_LIGHTING);            
        }
        else
        {
            if (glIsEnabled(GL_LIGHTING))
                glDisable(GL_LIGHTING);
        }
        
        // check deep.
        if (mat->deepness == true)
        {
            if (glIsEnabled(GL_DEPTH_TEST) == false)
                glEnable(GL_DEPTH_TEST);
        }
        else
        {
            if (glIsEnabled(GL_DEPTH_TEST))
                glDisable(GL_DEPTH_TEST);
        }
        
        // set color.
        jimpl->set_color(mat->color);
    }
    
protected:
    
    void _init()
    {
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();        
        
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    
protected:
    
    ::nnt::core::set<void*> _lights;
    
};

JUICE_END

# endif