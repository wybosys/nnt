
# ifndef __JUICE_ENTITY_08A0DBE3A66A4BCBAA3B15D0EE8A0856_H_INCLUDED
# define __JUICE_ENTITY_08A0DBE3A66A4BCBAA3B15D0EE8A0856_H_INCLUDED

# include "JuicePhysics.hpp"

JUICE_BEGIN

template <typename implT, typename typesT>
class Entity
: public RefObject<implT>
{
public:
    typedef typename typesT::bounding_type bounding_type;
    
protected:    
    
    Entity()
    : tag(-1)
    {
        PASS;
    }
    
    ~Entity()
    {
        PASS;
    }
        
public:
    
    //! name.
    ::wsi::core::string name;
    
    //! identity.
    ::wsi::core::string identity;
    
    //! tag.
    int tag;
    
    //! bounding box.
    bounding_type bbx;    
};

template <typename implT, typename typesT>
class PhyEntity
: public Entity<implT, typesT>
{
    
public:
    
    PhyEntity()
    : shapetype(PHY_SHAPETYPE_POLYGON), phyobj(NULL)
    {
        PASS;
    }
    
    ~PhyEntity()
    {
        PASS;
    }
    
public:
    
    //! phy params.
    phyparam_t params;
    
    //! shape type.
    PHY_SHAPETYPE shapetype;
    
    //! physics object.
    phyobj_t* phyobj;
    
};

struct renderinfo
{
    ulonglong frame_begin, frame_cost, frame_end;
    double frame_time;
};

typedef void (*func_render)(Object*, Object*, renderinfo*);
typedef void* (*func_collision)(Object*, void*);

struct renderentity_wrapper : object_wrapper
{
    func_render frender;
    func_collision fcollision;
    ::wsi::core::string const* identity;
    ::wsi::core::string const* name;
    int* tag;        
};

typedef struct {} renderable, empty_renderentity_type;

template <typename entityT>
typename entityT::matrix_type& _ref_transform(entityT*);

template <typename implT, typename typesT>
class RenderEntity
: public Entity<implT, typesT>
{   
    typedef RenderEntity<implT, typesT> self_type;
    
    template <typename entityT>
    friend typename entityT::matrix_type& _ref_transform(entityT*);
    
public:
    
    typedef renderable renderable;
    typedef empty_renderentity_type empty_type;
    
    typedef typename typesT::vertex_type vertex_type;
    typedef typename typesT::matrix_type matrix_type;
    
protected:
    
    RenderEntity()
    {
        this->transform.set_identity();
        this->_transform.set_identity();
    }
    
    template <typename driverT, typename argT>
    static argT _todriver(void (implT::*render)(argT, renderinfo*), driverT* drv)
    {
        return (argT)drv;
    }
    
    template <typename lineT, typename argT>
    static argT _toline(void *(implT::*collision)(argT), lineT* line)
    {
        return (argT)line;
    }
    
    static void* _toline(void *(self_type::*collision)(void*), void* line)
    {
        return line;
    }
        
    template <typename driverT>
    void _update_driver(driverT* drv)
    {
        matrix_type mat = this->get_transform();
        drv->mult_matrix(mat);
    }
    
    template <typename lineT>
    lineT* _update_line(lineT* line)
    {
        matrix_type mat = this->get_transform();
        mat.set_inverse();
        lineT* newline = line->clone();
        *newline *= mat;
        return newline;
    }
    
    void* _update_line(void* line)
    {
        return line;
    }
    
    template <typename lineT>
    void _free_line(lineT* line)
    {
        delete line;
    }
    
    void _free_line(void* line)
    {
        PASS;
    }
        
public:            
    
    //! render.
    static void Render(implT* obj, Object* drv, renderinfo* info) 
    {   
        // reset transform.
        obj->_transform.set_identity();
        
        // save state.
        _todriver(&implT::render, drv)->save_state();
        
        // prepare.
        obj->prepare(_todriver(&implT::render, drv), info);
        
        // update.
        ((self_type*)obj)->_update_driver(_todriver(&implT::render, drv));
        
        // render object use info.
        obj->render(_todriver(&implT::render, drv), info);
        
        // restore state.
        _todriver(&implT::render, drv)->restore_state();
    }
    
    //! collision.
    static void* Collision(implT* obj, void* line)
    {
        void* newline = ((self_type*)obj)->_update_line(_toline(&implT::collision, line));
        void* ret = obj->collision(_toline(&implT::collision, newline));
        if (newline != line)
            ((self_type*)obj)->_free_line(_toline(&implT::collision, newline));
        return ret;
    }
    
    //! prepare.
    void prepare(Object* drv, renderinfo* info) {}
    
    //! render function.
    void render(Object* drv, renderinfo* info);
    
    //! get transform.
    matrix_type get_transform() const
    {
        return _transform * transform;
    }
    
    //! collision.
    void* collision(void* line)
    {
        return NULL;
    }
    
public:        
    
    //! position of this entity.
    vertex_type position;
    
    //! transform of this entity.
    matrix_type transform;
    
protected:
    
    //! addition transform.
    matrix_type _transform;
    
};

template <typename entityT>
inline_impl typename entityT::matrix_type& _ref_transform(entityT* ent)
{
    return ent->_transform;
}

JUICE_END

# endif
