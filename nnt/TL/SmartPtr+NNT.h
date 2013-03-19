
# ifndef __NNT_WTL_SMARTPOINTER_AE45CE93328F4D6EB0F91000E3FDC6CB_H_INCLUDED
# define __NNT_WTL_SMARTPOINTER_AE45CE93328F4D6EB0F91000E3FDC6CB_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

template <typename valT>
class smart_drop
{
    typedef smart_drop<valT> self_type;
    
protected:
    
    smart_drop(valT* r)
    : _ptr(r)
    {
        PASS;
    }
    
public:
    
    typedef valT value_type;
    
    smart_drop(smart_drop const& r)
    : _ptr(r._ptr)
    {
        safe_grab(_ptr);
    }
    
    ~smart_drop()
    {
        safe_drop(_ptr);
    }
    
    self_type& operator = (self_type const& r)
    {
        safe_drop(_ptr);
        _ptr = r._ptr;
        safe_grab(_ptr);
        return *this;
    }
    
    self_type& operator = (valT* val)
    {
        safe_drop(_ptr);
        _ptr = val;
        safe_grab(_ptr);
        return *this;
    }
    
    operator valT* ()
    {
        return _ptr;
    }
    
    operator valT const* () const
    {
        return _ptr;
    }
    
    static self_type instance()
    {
        return self_type(new valT);
    }
    
    static self_type instance(valT* val)
    {
        return self_type(val);
    }
    
    valT* operator -> ()
    {
        return _ptr;
    }
    
    valT const* operator -> () const
    {
        return _ptr;
    }
    
protected:
    
    valT* _ptr;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif