
# ifndef __NNT_MODEL_ITEM_B71DAF1671084AE0898CE8C1E11634D3_H_INCLUDED
# define __NNT_MODEL_ITEM_B71DAF1671084AE0898CE8C1E11634D3_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface MItem : NNTObject {
    
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

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(model)

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

NNT_BEGIN_NS(ui)

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

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_OBJC

# endif

# endif
