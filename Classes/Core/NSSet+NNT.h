
# ifndef __NNT_NSSET_22568F0E4BA24727A28A8C0EA1A1EAE5_H_INCLUDED
# define __NNT_NSSET_22568F0E4BA24727A28A8C0EA1A1EAE5_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSSet (NNT)

@end

NNTDECL_CATEGORY(NSSet, NNT);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

template <typename setT>
class _Set
: public ns::Object<setT>
{
    typedef ns::Object<setT> super;
    
public:
    
    _Set()
    {
        PASS;
    }
    
    _Set(setT* obj)
    : super(obj)
    {
        PASS;
    }
    
    explicit _Set(id obj)
    : super(obj)
    {
        PASS;
    }
    
    usize size() const
    {
        return [this->_self count];
    }

    usize length() const
    {
        return [this->_self count];
    }

    usize count() const
    {
        return [this->_self count];
    }
    
    id any() const
    {
        return [this->_self anyObject];
    }

};

class Set
: public _Set<NSSet>
{
    typedef _Set<NSSet> super;
    
public:
        
    Set(NSSet* set)
    : super(set)
    {
        PASS;
    }
    
    explicit Set(id obj)
    : super(obj)
    {
        PASS;
    }
    
    Set(void* obj)
    : super((id)obj)
    {
        PASS;
    }
    
};

class MutableSet
: public _Set<NSMutableSet>
{
    typedef _Set<NSMutableSet> super;
    
public:
    
    MutableSet()
    {
        PASS;
    }
    
    MutableSet(NSMutableSet* set)
    : super(set)
    {
        PASS;
    }
    
    explicit MutableSet(id obj)
    : super(obj)
    {
        PASS;
    }
    
    void add(id obj)
    {
        [this->_self addObject:obj];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
