
# ifndef __WSI_MODEL_ITEM_B71DAF1671084AE0898CE8C1E11634D3_H_INCLUDED
# define __WSI_MODEL_ITEM_B71DAF1671084AE0898CE8C1E11634D3_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface MItem : WSIObject {
    
    //! store child items.
    NSMutableArray* _children;
    
}

@property (nonatomic, retain, readonly) NSArray* children;

- (void)insertItem:(MItem*)item atIndex:(NSUInteger)index;
- (void)addItem:(MItem*)item;
- (NSUInteger)count;
- (NSUInteger)sum;
- (void)clear;
- (MItem*)itemAt:(NSUInteger)idx;

@end

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(model)

class Item
: public RefObject
{
public:
    
    typedef core::refpointer_vector<Item> store_type;
    
    Item()
    {
        PASS;
    }
    
    virtual ~Item()
    {
        PASS;
    }
    
    void insert(Item* obj, uint idx)
    {
        _children.insert(_children.begin() + idx, obj); 
        obj->grab();
    }
    
    void add(Item* obj)
    {
        _children.push_back(obj);
        obj->grab();
    }
    
    void clear()
    {
        _children.clear();
    }
    
    uint count() const
    {
        return _children.size();
    }
    
    uint size() const
    {
        return _children.size();
    }
    
    uint sum() const
    {
        uint ret = _children.size();
        for (store_type::const_iterator each = _children.begin();
             each != _children.end();
             ++each)
        {
            ret += (*each)->sum();
        }
        return ret;
    }
    
    Item* at(uint idx)
    {
        return _children[idx];
    }
    
    Item const* at(uint idx) const
    {
        return _children[idx];
    }
    
protected:
    
    store_type _children;
    
};

WSI_BEGIN_NS(ui)

template <typename valT, typename varT, typename strT>
class Item
: public model::Item
{
public:
    
    Item()
    : height(0), width(0)
    {
        PASS;
    }
    
    strT name;
    valT height, width;
    varT value;
};

WSI_END_NS

WSI_END_NS
WSI_END_HEADER_OBJC

# endif

# endif
