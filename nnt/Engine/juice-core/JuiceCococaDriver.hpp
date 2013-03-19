
# ifndef __JUICE_COCOCA_DRIVER_C9DEF0BA8D35433B9970EE337339B551_H_INCLUDED
# define __JUICE_COCOCA_DRIVER_C9DEF0BA8D35433B9970EE337339B551_H_INCLUDED
# ifdef NNT_OBJC

# include "JuiceDriver.hpp"
# include "JuiceCocoa++.hpp"
# include "../../Graphic/NGContext.h"

JUICE_BEGIN

typedef struct {
    
# ifdef NNT_TARGET_IOS
    typedef UIView* drawable_type;
# endif
    
# ifdef NNT_TARGET_MAC
    typedef NSView* drawable_type;
# endif
    
    typedef cocoa::Graphics* context_type;
    
}
_cococa_types;

template <typename implT, typename typesT>
class CococaDriver
: public Driver<implT, typesT, _cococa_types>
{
    
    typedef Driver<implT, typesT, _cococa_types> super;
    
public:
    
    typedef _cococa_types::drawable_type drawable_type;
    typedef _cococa_types::context_type context_type;
    typedef typename super::color_type color_type;
    typedef typename super::viewport_type viewport_type;
    typedef typename super::matrix_type matrix_type;
    typedef typename super::vectorcomp_type vectorcomp_type;
    typedef typename super::vertex_type vertex_type;
    typedef typename super::index_type index_type;
    typedef typename super::colorcomp_type colorcomp_type;
    
    CococaDriver(implT* impl)
    : _drawable(NULL),
    _context(new cocoa::Graphics),
    _ptrcontext(NULL)
    {
        _bounds = CGRectZero;
        
        if (impl)
        {
            _ptrcontext = &impl->_context;
        }
    }
    
    ~CococaDriver()
    {
        safe_delete(_context);
    }
    
    void set_drawable(drawable_type obj)
    {                   
        _drawable = obj;
    }
    
    void set_current()
    {
        PASS;
    }
    
    context_type get_context() const
    {
        return _context;
    }
    
    void update()
    {
        if (_drawable == nil)
            return;
        
        _bounds = _drawable.bounds;
        if (CGRectEqualToRect(_bounds, CGRectZero))
            return;
        
        if (!_context->is_null())
        {
            if (_context->bounds() != _bounds)
            {
                trace_msg(@"context's size changed, will recreate the context.");
                _context->release();
            }                
        }
        
        if (_context->is_null())
        {
            if (_ptrcontext)
            {
                *_context = **_ptrcontext;
            }
            else
            {                
                this->_impl()->instance_context();
            }
        }        
    }
    
    bool instance_context()
    {
        _context->create_rgba(_bounds.size());
        
        if (_context->is_null())
        {
            trace_msg(@"failed to create context.");
        }
        else
        {
            _context->reverse();
        }
        
        return _context->is_null() == false;
    }
    
    void flush()
    {
        // draw _context to current.
        CGContextRef ctx = NgGetCurrentContext();
        if (ctx == NULL)
            return;
        
        jimpl->lock();
        
        // update
        _context->flush();

        // draw to ui.
        cocoa::Graphics gra(ctx, _bounds);
        cocoa::Image img = _context->to_image();
        img.fill(gra, gra.bounds());
        
        jimpl->unlock();
        
        // next draw.
        [_drawable performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:NO];
    }
    
    void clear_drawable()
    {
        PASS;
    }
    
    void prepare()
    {
        update();
    }
    
    void save_state()
    {
        _context->push_state();
    }
    
    void restore_state()
    {
        _context->pop_state();
    }
    
    void clear()
    {
        _context->clear(_bounds);
    }
    
    void set_background(color_type const& color)
    {
        _context->push_state();
        _context->set_matrix(cocoa::Matrix::Identity());
        cocoa::Brush br(cocoa::Color(color.r, color.g, color.b, color.a));
        br.fill(*_context, _bounds);
        _context->pop_state();
    }
    
    void set_viewport(viewport_type const& vp)
    {
        _vp = vp;
    }
    
    viewport_type const& get_viewport() const
    {
        return _vp;
    }
    
    template <typename lightT>
    void set_light(lightT* light)
    {
        PASS;
    }
    
    void mult_matrix(matrix_type const& mat)
    {
        _context->mult_matrix(mat);
    }
    
    template <typename materialT>
    void set_material(materialT* mat)
    {
        PASS;
    }
    
    void add_vertices(vectorcomp_type const* pointer, usize length)
    {
        PASS;
    }
    
    void add_normals(vectorcomp_type const* pointer, usize length)
    {
        PASS;
    }
    
    void add_indexies(index_type const* pointer, usize length)
    {
        PASS;
    }
    
    void add_colors(colorcomp_type const* pointer, usize length) 
    {
        PASS;
    }
    
    void draw_triangles()
    {
        PASS;
    }
    
    void draw_looplines()
    {
        PASS;
    }
    
    void purge_elements()
    {
        PASS;
    }
    
    bool valid() const
    {
        return !_context->is_null();
    }
    
    context_type& context() const
    {
        return (context_type&)_context;
    }
    
protected:
    
    ::nnt::cg::Rect _bounds;
    context_type _context;
    context_type* _ptrcontext;
    drawable_type _drawable;
    viewport_type _vp;
    
};

JUICE_END

# endif
# endif