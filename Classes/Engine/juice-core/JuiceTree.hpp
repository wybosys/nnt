
# ifndef __JUICE_TREE_3EFEFCA35D9D4469B8F806D20A5311C8_H_INCLUDED
# define __JUICE_TREE_3EFEFCA35D9D4469B8F806D20A5311C8_H_INCLUDED

# include "JuiceEntity.hpp"

JUICE_BEGIN

typedef struct {} empty_tree_type;

template <typename implT, typename typesT>
class Tree
{
public:
    typedef empty_tree_type empty_type;
    
    typedef typename typesT::entities_type entities_type;
    typedef typename entities_type::value_type entity_type;
    typedef typename typesT::bounding_type bounding_type;
    
    Tree()
    {
        PASS;
    }
    
    ~Tree()
    {
        jimpl->clear();
    }
    
public:
    
    template <typename entityT>
    entity_type add_entity(entityT* obj)
    {
        typedef typename entityT::renderable renderable;
        typedef typename entityT::refable refable;
        
        entity_type entity;
        entity.object = obj;
        entity.fnew = (func_new)entityT::New;
        entity.fdestroy = (func_destroy)entityT::Destroy;
        entity.fref = (func_ref)entityT::Reference;
        entity.fderef = (func_deref)entityT::Dereference;
        entity.frender = (func_render)entityT::Render;
        entity.fcollision = (func_collision)entityT::Collision;
        entity.identity = &obj->identity;
        entity.name = &obj->name;
        entity.tag = &obj->tag;
        
        entities.push_back(entity);
        
        // ref object.        
        (*entity.fref)(entity.object);
                
        return entity;
    }
    
    template <typename entityT, typename posT>
    entity_type insert_entity(entityT* obj, posT const& pos)
    {
        typedef typename entityT::renderable renderable;
        typedef typename entityT::refable refable;
        
        entity_type entity;
        entity.object = obj;
        entity.fnew = (func_new)entityT::New;
        entity.fdestroy = (func_destroy)entityT::Destroy;
        entity.fref = (func_ref)entityT::Reference;
        entity.fderef = (func_deref)entityT::Dereference;
        entity.frender = (func_render)entityT::Render;
        entity.fcollision = (func_collision)entityT::Collision;
        entity.identity = &obj->identity;
        entity.name = &obj->name;
        entity.tag = &obj->tag;
        
        entities.insert(pos, entity);
        
        // ref object.        
        (*entity.fref)(entity.object);
        
        return entity;
    }
    
    entity_type const* find_byname(::nnt::core::string const& name) const
    {
        typename entities_type::const_iterator each = entities.begin();
        while (each != entities.end())
        {
            entity_type const& entry = *each;
            if (*entry.name == name)
                return &entry;
            ++each;
        }
        return NULL;
    }
    
    entity_type const* find_byidentity(::nnt::core::string const& identity) const
    {
        typename entities_type::const_iterator each = entities.begin();
        while (each != entities.end())
        {
            entity_type const& entry = *each;
            if (*entry.identity == identity)
                return &entry;
            ++each;
        }
        return NULL;
    }
    
    entity_type const* find_bytag(int tag) const
    {
        typename entities_type::const_iterator each = entities.begin();
        while (each != entities.end())
        {
            entity_type const& entry = *each;
            if (*entry.tag == tag)
                return &entry;
            ++each;
        }
        return NULL;
    }

    entity_type& entity_at(uindex idx)
    {
        return entities.at(idx);
    }
    
    entity_type const& entity_at(uindex idx) const
    {
        return entities.at(idx);
    }
    
    Object* object_at(uindex idx)
    {
        entity_type& entity = entities.at(idx);
        return entity.object;
    }
    
    Object const* object_at(uindex idx) const
    {
        entity_type const& entity = entities.at(idx);
        return entity.object;
    }
    
    void clear()
    {
        for (typename entities_type::iterator each = entities.begin();
             each != entities.end();
             ++each)
        {
            entity_type& entry = *each;   
            (*entry.fderef)(entry.object);
        }
        entities.clear();
    }
    
public:
    
    //! entities.
    entities_type entities;
    
};

template <typename implT, typename typesT>
class TreeRender
: public RenderEntity<implT, typesT>
{    
public:        
    
    template <typename driverT, typename treeT>
    void render(driverT* drv, treeT* tree, renderinfo* info)
    {
        typedef typename treeT::entities_type entities_type;
        typedef typename treeT::entity_type entity_type;
        
        for (typename entities_type::const_iterator each = tree->entities.begin();
             each != tree->entities.end();
             ++each)
        {
            entity_type const& cref = *each;
            (*cref.frender)(cref.object, drv, info);
        }
    }
    
    template <typename lineT, typename treeT>
    typename treeT::entity_type* collision(treeT* tree, lineT* line)
    {
        typedef typename treeT::entities_type entities_type;
        typedef typename treeT::entity_type entity_type;
        
        typename entities_type::iterator each = tree->entities.begin();
        while (each != tree->entities.end())
        {
            entity_type& entry = *each;
            if ((*entry.fcollision)(entry.object, line))
                return &entry;
            ++each;
        }
        return NULL;
    }
    
};

template <typename implT,
typename physicsT, 
typename entitiesT = ::nnt::core::vector<renderentity_wrapper>
>
class PhyTree
: public Tree<implT, entitiesT>
{
public:
    typedef physicsT physics_type;
    
public:
    
    void prepare()
    {
        this->physics.prepare();
    }
    
    void update()
    {
        this->physics.update();
    }
    
public:
    physics_type physics;
};

JUICE_END

# endif