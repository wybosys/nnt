
# ifndef __JUICE_DRIVER_4D7C76030B8B469AA04036A2AF72A0D1_H_INCLUDED
# define __JUICE_DRIVER_4D7C76030B8B469AA04036A2AF72A0D1_H_INCLUDED

# include "../../Core/Task+WSI.h"

JUICE_BEGIN

typedef struct {
    typedef null_struct* drawable_type;
    typedef null_struct* context_type;
} _noarch_types;

typedef struct {} empty_driver_type;

template <typename implT, typename typesT, typename archT = _noarch_types>
class Driver
: public RefObject<implT>
{
    
public:
    
    typedef empty_driver_type empty_type;
    
    typedef typename archT::drawable_type drawable_type;
    typedef typename archT::context_type context_type;    
    
    typedef typename typesT::vertex_type vertex_type;
    typedef typename vertex_type::value_type vectorcomp_type;
    typedef typename typesT::index_type index_type;
    typedef typename typesT::color_type color_type;
    typedef typename color_type::value_type colorcomp_type;
    typedef typename typesT::matrix_type matrix_type;
    typedef typename typesT::viewport_type viewport_type;   
    
    //! prepare for draw.
    void prepare();
    
    //! valid.
    bool valid() const;
    
    //! flush buffer.
    void flush();
    void update();
    
    //! create context.
    bool instance_context();
    
    //! void clear();
    void clear();    
    
    //! set drawable.
    void set_drawable(drawable_type);
    
    //! get context.
    context_type get_context() const;
    
    //! set background color.
    void set_background(color_type const& color);
    
    //! select color.
    void set_color(color_type const& color);
    
    //! set current.
    void set_current();
    
    //! add vertices pointer.
    void add_vertices(vectorcomp_type const*, usize);
    
    //! add normals pointer.
    void add_normals(vectorcomp_type const*, usize);
    
    //! add indexies pointer.
    void add_indexies(index_type const*, usize);
    
    //! add colors pointer.
    void add_colors(colorcomp_type const*, usize);
    
    //! draw element store in array.
    void draw_points();
    void draw_triangles();
    void draw_looplines();
    
    //! purge for next array draw.
    void purge_elements();
    
    //! matrix operations.
    void push_matrix();
    void pop_matrix();
    void set_matrix(matrix_type const&);
    void mult_matrix(matrix_type const&);
    
    //! save & restore state.
    void save_state();
    void restore_state();
    
    //! set viewport.
    void set_viewport(viewport_type const&);
    viewport_type get_viewport() const;
    
    //! set light.
    template <typename lightT>
    void set_light(lightT*);
    
    //! set material.
    template <typename materialT>
    void set_material(materialT*);

# ifdef WSI_DEBUG
    void _error_check();
# endif
    
    //! lock draw.
    void lock()
    {
        _mtx_draw.lock();
    }
    
    //! unlock draw.
    void unlock()
    {
        _mtx_draw.unlock();
    }
            
protected:
    
    //! init.
    void _init();
    
    //! finish.
    void _finish();
    
protected:
    
    //! mutex for draw.
    ::wsi::core::Mutex _mtx_draw;
            
};

JUICE_END

# endif