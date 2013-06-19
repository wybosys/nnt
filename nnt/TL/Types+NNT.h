
# ifndef __NNT_TL_TYPES_E4EB5FF142A649B8AA7076512B7EA40A_H_INCLUDED
# define __NNT_TL_TYPES_E4EB5FF142A649B8AA7076512B7EA40A_H_INCLUDED

# if defined(NNT_CXX)

# ifdef NNT_USER_SPACE

# include <set>
# include <deque>
# include <stack>
# include <sstream>
# include <bitset>

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

using std::set;
using std::deque;
using std::stack;
using std::make_pair;
using std::bitset;
using std::pair;

NNT_END_NS
NNT_END_HEADER_CXX

# endif // user space

NNT_BEGIN_HEADER_CXX

template <typename valT>
class opt
{

protected:

    opt(valT const& r, bool f)
        : _flag(f),
        _val(r)
    {

    }

public:

    explicit opt(bool f)
        : _flag(f)
    {

    }

    opt& operator [] (valT const& r)
    {
        _val = r;
        return *this;
    }

    class failed
    {
    public:

        failed(valT const& r)
            : val(r)
        {
            PASS;
        }

        valT val;
    };

    class succ
    {
    public:

        succ(valT const& r)
            : val(r)
        {
            PASS;
        }

        valT val;
    };

    opt operator | (opt const& r) const
    {
        if (_flag && !r._flag)
            return opt(_val, true);
        if (r._flag && !_flag)
            return opt(r._val, true);
        if (_flag && r._flag)
            return opt(_val | r._val, true);
        return opt(false);
    }

    opt operator | (valT const& r) const
    {
        if (_flag)
            return opt(_val | r, true);
        return opt(r, true);
    }

    opt operator & (opt const& r) const
    {
        if (_flag && !r._flag)
            return opt(_val, true);
        if (r._flag && !_flag)
            return opt(r._val, true);
        if (_flag && r._flag)
            return opt(_val & r._val, true);
        return opt(false);
    }

    opt operator & (valT const& r) const
    {
        if (_flag)
            return opt(_val & r, true);
        return opt(r, true);
    }
    
    opt operator + (opt const& r) const
    {
        if (_flag && !r._flag)
            return opt(_val, true);
        if (r._flag && !_flag)
            return opt(r._val, true);
        if (_flag && r._flag)
            return opt(_val + r._val, true);
        return opt(false);
    }
    
    opt operator + (valT const& r) const
    {
        if (_flag)
            return opt(_val + r, true);
        return opt(r, true);
    }

    opt operator << (failed const& r) const
    {
        if (_flag)
            return *this;
        return opt(r.val, true);
    }

    opt operator << (succ const& r) const
    {
        if (_flag)
            return opt(r.val, true);
        return *this;
    }

    operator valT& ()
    {
        return _val;
    }

    operator valT const& () const
    {
        return _val;
    }

protected:

    bool _flag;
    valT _val;

};

# ifdef NNT_OBJC

template <typename valT>
inline_impl id to_object(valT const& obj)
{
    return obj;
}

# endif

NNT_BEGIN_NS(ntl)

typedef struct {} true_type;
typedef struct {} false_type;

NNT_CONST_VAR(true_type, true_o);
NNT_CONST_VAR(false_type, false_o);

typedef struct {} same_type;
typedef struct {} diff_type;

NNT_CONST_VAR(same_type, same_o);
NNT_CONST_VAR(diff_type, diff_o);

typedef struct {} match_type;
typedef struct {} failed_type;

NNT_CONST_VAR(match_type, match_o);
NNT_CONST_VAR(failed_type, failed_o);

template <typename lT, typename rT>
struct is_same
{
    typedef diff_type type, diff;
};

template <typename lT>
struct is_same<lT, lT>
{
    typedef same_type type, same;
};

typedef struct {} class_type;
typedef struct {} std_type;

NNT_CONST_VAR(class_type, class_o);
NNT_CONST_VAR(std_type, std_o);

template <typename T>
struct is_stdtype
{
    typedef false_type type;
};

# define _NNTNTL_IMPL_STDTYPE(in) \
template <> \
struct is_stdtype < in > \
{ \
typedef true_type type; \
};

_NNTNTL_IMPL_STDTYPE(int);
_NNTNTL_IMPL_STDTYPE(uint);
_NNTNTL_IMPL_STDTYPE(float);
_NNTNTL_IMPL_STDTYPE(double);
_NNTNTL_IMPL_STDTYPE(void*);
_NNTNTL_IMPL_STDTYPE(void);
_NNTNTL_IMPL_STDTYPE(short);
_NNTNTL_IMPL_STDTYPE(ushort);
_NNTNTL_IMPL_STDTYPE(char);
_NNTNTL_IMPL_STDTYPE(uchar);
_NNTNTL_IMPL_STDTYPE(long);
_NNTNTL_IMPL_STDTYPE(ulong);
_NNTNTL_IMPL_STDTYPE(longlong);
_NNTNTL_IMPL_STDTYPE(ulonglong);

template <typename T, typename stdT = typename is_stdtype<T>::type >
struct is_class
{
    typedef class_type type;
    typedef match_type match;
};

template <typename T>
struct is_class <T, true_type>
{
    typedef std_type type;
    typedef failed_type failed;
};

typedef enum
{
    copy = true,
    assign = false,
} _bool_copy;

template <bool cond, typename A, typename B>
struct triple_select
{
    typedef A type;
};

template <typename A, typename B>
struct triple_select<false, A, B>
{
    typedef B type;
};

# define NNT_TL_CLASS_HAS_FUNC(func, name) \
template<typename T, typename Sign> \
struct name { \
    template <typename U, U> struct type_check; \
    template <typename _1> static char &chk(type_check<Sign, &_1::func> *); \
    template <typename   > static long  &chk(...); \
    enum { value = sizeof(chk<T>(0)) == sizeof(char) }; \
    typedef typename ntl::triple_select<value, ntl::true_type, ntl::false_type>::type type; \
}

template <typename T>
struct to_object
{
    T& operator () (T* ptr) const
    {
        return *ptr;
    }
    
    T const& operator () (T const* ptr) const
    {
        return *ptr;
    }
};

# ifdef NNT_OBJC

template <typename T>
struct to_objcobject
{
    T* operator () (T* ptr) const
    {
        return ptr;
    }
    
    T* operator () (T const* ptr) const
    {
        return (T*)ptr;
    }
};

# endif

typedef struct {} pointer_type;
typedef struct {} instance_type;
typedef struct {} wrapper_type;
typedef struct {} nonwrapper_type;

NNT_CONST_VAR(pointer_type, pointer_o);
NNT_CONST_VAR(instance_type, instance_o);
NNT_CONST_VAR(wrapper_type, wrapper_o);
NNT_CONST_VAR(nonwrapper_type, nonwrapper_o);

template <typename T>
struct is_instance
{
    enum { IS_INSTANCE = true };
    typedef instance_type const& type;
};

template <typename T>
struct is_instance <T*>
{
    enum { IS_INSTANCE = false };
    typedef pointer_type const& diff;
};

template <typename T>
struct is_pointer
{
    enum { IS_POINTER = false };
    typedef instance_type const& diff;
};

template <typename T>
struct is_pointer <T*>
{
    enum { IS_POINTER = true };
    typedef pointer_type const& type;
};

typedef struct {} equal_t;
typedef struct {} unequal_t;

NNT_CONST_VAR(equal_t, equal_o);
NNT_CONST_VAR(unequal_t, unequal_o);

template <typename lT, typename rT>
struct is_equal
{
    enum { IS_EQUAL = false };
    typedef unequal_t type, unequal;
};

template <typename lT>
struct is_equal<lT, lT>
{
    enum { IS_EQUAL = true };
    typedef equal_t type, equal;
};

template <typename T>
struct check_wrapper
{
    template <typename TC, typename TS>
    struct _type {};
    
    template <typename N>
    static char _check(_type<N, typename N::is_wrapper_type> const*);
    
    template <typename N>
    static long _check(...);
    
    enum { IS_WRAPPER = sizeof(_check<T>(0)) == sizeof(char) };
    
};

template <typename T, bool IS = check_wrapper<T>::IS_WRAPPER >
struct is_wrapper
{
    typedef wrapper_type type, wrapper;
};

template <typename T>
struct is_wrapper <T, false>
{
    typedef nonwrapper_type type, nonwrapper;
};

template <typename T>
struct cxx_type
{
    typedef T type;
};

template <typename T>
struct cxx_type<T*>
{
    typedef T type;
};

template <typename T>
struct cxx_type<T const*>
{
    typedef T type;
};

template <typename T>
struct cxx_type<T&>
{
    typedef T type;
};

template <typename T>
struct cxx_type<T const&>
{
    typedef T type;
};

# ifdef NNT_OBJC

template <typename T>
struct objc_type
{
    typedef T* type;
};

template <typename T>
struct objc_type <T*>
{
    typedef T* type;
};

template <typename T>
struct objc_type <T const*>
{
    typedef T* type;
};

# endif

template <typename T>
struct mixin_type
{
    typedef T type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
};

template <typename T>
struct mixin_type<T*>
{
    typedef T type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
};

template <typename T>
struct mixin_type<T const*>
{
    typedef T type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
};

template <typename T>
struct mixin_type<T&>
{
    typedef T type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
};

template <typename T>
struct mixin_type<T const&>
{
    typedef T type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
};

# ifdef NNT_OBJC

template <>
struct mixin_type<id>
{
    typedef id type;
    typedef id reference;
    typedef id const_reference;
    typedef id pointer;
    typedef id const_pointer;
};

template <>
struct mixin_type< NSObject* >
{
    typedef NSObject* type;
    typedef NSObject* reference;
    typedef NSObject* const_reference;
    typedef NSObject* pointer;
    typedef NSObject* const_pointer;
};

# endif

template <typename T>
inline T* as_pointer(T* o)
{
    return o;
}

template <typename T>
inline T const* as_pointer(T const* o)
{
    return o;
}

template <typename T>
inline T* as_pointer(T& o)
{
    return &o;
}

template <typename T>
inline T const* as_pointer(T const& o)
{
    return &o;
}

template <typename typeT>
class const_pointer
{
public:
    
    typedef typename mixin_type<typeT>::type value_type;
    
    const_pointer(value_type const& obj)
    : _obj(&obj)
    {}
    
    const_pointer(value_type const* obj)
    : _obj(obj)
    {}    
    
    operator value_type const* () const
    {
        return (value_type const*)_obj;
    }
    
    value_type const& operator * () const
    {
        return *(value_type const*)_obj;
    }
    
    value_type const* operator -> () const
    {
        return (value_type const*)_obj;
    }
    
protected:
    
    value_type const* _obj;
    
};

template <typename typeT>
class mutable_pointer
{
public:
    
    typedef typename mixin_type<typeT>::type value_type;
    
    mutable_pointer(value_type& obj)
    : _obj(&obj)
    {}
    
    mutable_pointer(value_type const& obj)
    : _obj((value_type*)&obj)
    {}
    
    mutable_pointer(value_type* obj)
    : _obj(obj)
    {}
    
    operator value_type* () const
    {
        return (value_type*)_obj;
    }
    
    value_type& operator * () const
    {
        return *(value_type*)_obj;
    }
    
    value_type* operator -> () const
    {
        return (value_type*)_obj;
    }
    
protected:
    
    value_type* _obj;
    
};

# ifdef NNT_OBJC

template <>
class const_pointer < NSObject* >
{
public:
    
    typedef mixin_type<NSObject*>::type value_type;    
    
    const_pointer(NSObject* obj)
    : _obj(obj)
    {}    
    
    operator NSObject* () const
    {
        return (NSObject*)_obj;
    }
    
    NSObject* operator * () const
    {
        return (NSObject*)_obj;
    }
    
protected:
    
    NSObject* _obj;
    
};

# define NNTNS_CONST_POINTER(valT) \
NNT_BEGIN_NS(ntl) \
template <> \
class const_pointer <valT> \
{ \
public: \
typedef valT::objc_type* value_type; \
const_pointer(valT const& obj) \
: _obj(obj) \
{} \
operator value_type () const \
{ \
return (value_type)_obj; \
} \
value_type operator * () const \
{ \
return (value_type)_obj; \
} \
protected: \
value_type _obj; \
}; \
NNT_END_NS

# endif // objc

template <typename lT, typename rT>
inline_impl lT present_cast(rT const& r)
{
    return error_op();
}

template <typename TRe, typename TIn>
inline_impl TRe type_cast(TIn const*)
{ 
	return error_op(); 
}

template <typename TRe, typename TIn>
inline_impl TRe dup_cast(TIn const*)
{ 
	return error_op(); 
}

template <typename TRe, typename TIn>
inline_impl TRe type_cast(TIn*)
{ 
	return error_op(); 
}

template <typename TRe, typename TIn>
inline_impl TRe dup_cast(TIn*)
{ 
	return error_op(); 
}

template <typename TRe, typename TIn>
inline_impl TRe type_cast(TIn const&)
{ 
	return error_op(); 
}

template <typename TRe, typename TIn>
inline_impl TRe dup_cast(TIn const&)
{ 
	return error_op(); 
}

template <typename baseT, typename base2T>
struct inherit
    : public baseT,
    public base2T
{
    typedef baseT _1, super;
    typedef base2T _2;
};

NNT_BEGIN_NS(uml)

template <typename implT>
class implementation
{
protected:
    
    typedef implT impl_type;
    
    implT& _impl()
    {
        return *(implT*)this;
    }
    
    implT const& _impl() const
    {
        return *(implT const*)this;
    }
    
};

template <typename implT, typename T>
class realization
: public implementation<implT>,
public T
{
    
};

template <typename implT, typename T>
class generalization
: public implementation<implT>,
public T
{
    
};

template <typename implT, typename T>
class dependency
: public implementation<implT>
{
public:
    
    dependency(T& obj)
    : _obj(obj)
    {
        PASS;
    }
    
protected:
    
    T& _obj;
    
};

template <typename implT, typename T>
class association
: public implementation<implT>
{
public:
    
    association(T* obj = NULL)
    : _obj(obj)
    {
        PASS;
    }
    
    void set(T* obj)
    {
        _obj = obj;
    }
    
protected:
    
    T* _obj;
    
};

template <typename implT, typename T>
class aggregation
: public implementation<implT>
{
    
};

template <typename implT, typename T>
class composition
: public implementation<implT>
{
    typedef composition<implT, T> self_type;
    
public:
    
    typedef T value_type;
    
    operator T& ()
    {
        return _obj;
    }

    operator T* ()
    {
        return &_obj;
    }
    
    operator T const& () const
    {
        return _obj;
    }

    operator T const* () const
    {
        return &_obj;
    }
    
    T* operator -> ()
    {
        return &_obj;
    }
    
    T const* operator -> () const
    {
        return &_obj;
    }
    
    implT& operator += (T const& r)
    {
        _obj += r;
        return this->_impl();
    }
    
    implT operator + (T const& r) const
    {
        implT ret = this->_impl();
        return ret += r;
    }
    
    implT& operator -= (T const& r)
    {
        _obj -= r;
        return this->_impl();
    }
    
    implT operator - (T const& r) const
    {
        implT ret = this->_impl();
        return ret -= r;
    }
    
    implT& operator *= (T const& r)
    {
        _obj *= r;
        return this->_impl();
    }
    
    implT operator * (T const& r) const
    {
        implT ret = this->_impl();
        return ret *= r;
    }
    
    implT& operator /= (T const& r)
    {
        _obj += r;
        return this->_impl();
    }
    
    implT operator / (T const& r) const
    {
        implT ret = this->_impl();
        return ret += r;
    }
    
protected:
    
    T _obj;

};

NNT_END_NS // uml

template <typename T>
class reference
{
public:
    
    template <typename T2>
    reference(T2 const& obj)
    {
        _obj = (T*)&obj;
    }
    
    reference(void* obj)
    : _obj((T*)obj)
    {
        PASS;
    }
    
    reference(T* obj)
    : _obj(obj)
    {
        PASS;
    }
    
    operator T* ()
    {
        return _obj;
    }
    
    operator T const* () const
    {
        return _obj;
    }
    
    operator T& ()
    {
        return *_obj;
    }
    
    operator T const& () const
    {
        return *_obj;
    }
    
    T* operator -> ()
    {
        return _obj;
    }
    
    T const* operator -> () const
    {
        return _obj;
    }
    
    T& operator * ()
    {
        return *_obj;
    }
    
    T const& operator * () const
    {
        return *_obj;
    }
    
protected:
    
    T* _obj;
    
};

NNT_END_NS

NNT_END_HEADER_CXX

# endif

# endif
