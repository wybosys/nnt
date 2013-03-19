
# ifndef __NNT_WTL_FUNCTION_7072AC909B7744159B8262D591A699CF_H_INCLUDED
# define __NNT_WTL_FUNCTION_7072AC909B7744159B8262D591A699CF_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(wtl)

template <typename T>
class function
{
public:
    
    function(T func = NULL)
    : _func(func)
    {
        PASS;
    }
    
    operator T () const
    {
        return _func;
    }
    
    function<T>& operator = (T r)
    {
        _func = r;
        return *this;
    }
    
    template <typename TR>
    function<T>& operator = (TR r)
    {
        _func = (T)r;
        return *this;
    }
    
    bool operator == (T r) const
    {
        return _func == r;
    }
    
    template <typename TR>
    bool operator == (TR r) const
    {
        return (void*)_func == (void*)r;
    }
    
    T operator () () const
    {
        return _func;
    }
    
    template <typename TR>
    static function<T> mk(TR r)
    {
        return (T)r;
    }
    
    void set(T r)
    {
        _func = r;
    }
    
    template <typename TR>
    void set(TR r)
    {
        _func = (T)r;
    }
    
    T _func;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
