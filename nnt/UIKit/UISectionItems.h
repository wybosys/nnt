
# ifndef __WSI_UIKIT_SECTIONITEMS_6E27D90148894DB8AEF28D8954DB44D4_H_INCLUDED
# define __WSI_UIKIT_SECTIONITEMS_6E27D90148894DB8AEF28D8954DB44D4_H_INCLUDED

WSI_BEGIN_OBJC


WSI_END_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class SectionItem
: public ns::RefObject
{
public:
    
    SectionItem()
    {
        register_signal(kSignalSelected);
    }
    
    ~SectionItem()
    {
        PASS;
    }
        
    operator variant_t const& () const
    {
        return var;
    }
    
    operator variant_t& ()
    {
        return var;
    }
    
    template <typename valT>
    operator valT () const
    {
        return var;
    }
    
    operator void* () const
    {
        return (void*)var;
    }
    
    template <typename valT>
    operator valT* () const
    {
        return (valT*)(void*)var;
    }
    
    template <typename valT>
    operator valT& () const
    {
        return *(valT*)(*this);
    }
    
    operator id () const
    {
        return (id)var;
    }
    
    //! var for store data.
    variant_t var;
    
};

template <typename itemT>
class Section
: public ::wsi::RefObject
{
public:
    
    typedef itemT item_type;
    
    Section()
    {
        PASS;
    }
    
    virtual ~Section()
    {
        PASS;
    }
    
    template <typename valT>
    item_type& add(valT const& val)
    {
        wtl::const_pointer<valT> ptr(val);
        
        item_type* var = new item_type;
        var->var = *ptr;
        
        return this->add(var);
    }
    
    virtual usize count() const
    {
        return _items.count();
    }
    
    virtual item_type& add(item_type* var)
    {
        _items.push_back(var);
        return *var;
    }
    
    virtual variant_t& at(uint idx)
    {
        return _items[idx]->var;
    }
    
    virtual variant_t const& at(uint idx) const
    {
        return _items[idx]->var;
    }
    
    virtual item_type& object_at(uint idx)
    {
        return *_items[idx];
    }
    
    virtual item_type const& object_at(uint idx) const
    {
        return *_items[idx];
    }
    
    virtual void remove(uint idx)
    {
        _items.erase_destroy(_items.begin() + idx);
    }
    
protected:
    
    core::pointer_vector<item_type> _items;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
