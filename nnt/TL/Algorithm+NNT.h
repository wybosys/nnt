
# ifndef __NNT_CORE_ALGORITHM_45BD957B7E6D4B57BD205CC1B465CAA3_H_INCLUDED
# define __NNT_CORE_ALGORITHM_45BD957B7E6D4B57BD205CC1B465CAA3_H_INCLUDED

# ifdef NNT_CXX

# ifdef NNT_USER_SPACE

# include <memory>

# endif

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ntl)

# ifdef NNT_USER_SPACE

using ::std::auto_ptr;
using ::std::distance;

# endif

class offsets
{
public:
    
    template <typename valT, typename ptrT>
    static valT pop(ptrT *& ptr)
    {
        return *((valT*&)ptr)++;
    }
    
    template <typename ptrT>
    static ptrT* preoff(ptrT *& ptr, usize off)
    {
        ptrT* ret = ptr;
        ((byte*&)ptr) += off;
        return ret;
    }
    
    template <typename ptrT>
    static ptrT* offset(ptrT *& ptr, usize off)
    {
        ((byte*&)ptr) += off;
        return ptr;
    }
    
};

template <>
inline_impl data type_cast<data, ntl::string>(ntl::string const& str)
{
    return data((byte const*)str.c_str(), str.size());
}

template <>
inline_impl data dup_cast<data, ntl::string>(ntl::string const& str)
{
    return data((byte const*)str.c_str(), str.size(), ntl::copy);
}

template <>
inline_impl data type_cast<data, char>(char const* str)
{
    return data((byte const*)str, strlen(str));
}

template <>
inline_impl data dup_cast<data, char>(char const* str)
{
    return data((byte const*)str, strlen(str), ntl::copy);
}

template <>
inline_impl ntl::string type_cast<ntl::string, ntl::data>(ntl::data const& da)
{
    return ntl::string((ntl::cstr_type)da.c_str(), da.length());
}

template <>
inline_impl ntl::string type_cast<ntl::string, ntl::string>(ntl::string const& str)
{
	return str;
}

template <>
inline_impl data type_cast<data, bool>(bool const& val)
{
    return data((byte const*)&val, sizeof(bool));
}

template <>
inline_impl bool type_cast<bool, ntl::data>(ntl::data const& val)
{
    return *(bool*)val.bytes();
}

template <>
inline_impl data type_cast<data, int>(int const& val)
{
    return data((byte const*)&val, sizeof(int));
}

template <>
inline_impl int type_cast<int, ntl::data>(ntl::data const& val)
{
    return *(int*)val.bytes();
}

# ifdef NNT_HAS_FLOAT

template <>
inline_impl data type_cast<data, float>(float const& val)
{
    return data((byte const*)&val, sizeof(float));
}

template <>
inline_impl float type_cast<float, ntl::data>(ntl::data const& val)
{
    return *(float*)val.bytes();
}

template <>
inline_impl data type_cast<data, double>(double const& val)
{
    return data((byte const*)&val, sizeof(double));
}

template <>
inline_impl double type_cast<double, ntl::data>(ntl::data const& val)
{
    return *(double*)val.bytes();
}

# endif

template <typename TCon>
inline_impl usize size(TCon const& con)
{
    return con.size();
}

template <typename TCon>
inline_impl typename TCon::value_type* pointer(TCon& con)
{
    return &(con[0]);
}

template <typename TCon>
inline_impl typename TCon::value_type const* pointer(TCon const& con)
{
    return &(con[0]);
}

inline_impl byte const* pointer(ntl::data const& da)
{
    return da.bytes();
}

inline_impl byte* pointer(ntl::data& da)
{
    return (byte*)da.bytes();
}

inline_impl usize length(ntl::data const& da)
{
    return da.length();
}

# ifdef NNT_USER_SPACE

template <>
inline_impl ntl::string present_cast<ntl::string, ntl::data>(ntl::data const& da)
{
    return ntl::hex_cast(da.bytes(), da.length());
}

template <>
inline_impl ntl::data present_cast<ntl::data, ntl::string>(ntl::string const& str)
{
    byte* ptr;
    usize sz;
    if (ntl::hex_cast(str, &ptr, &sz))
    {
        ntl::data da(ptr, sz, ntl::copy);
        free(ptr);
        return da;
    }
    return ntl::null_data;
}

template <>
inline_impl data type_cast<data, ntl::vector<byte> >(ntl::vector<byte> const& vec)
{
    return data(ntl::pointer(vec), vec.size());
}

template <>
inline_impl ntl::string type_cast<ntl::string, ntl::vector<byte> >(ntl::vector<byte> const& d)
{
    return ntl::string((char const*)ntl::pointer(d), ntl::length(d));
}

template <>
inline_impl ntl::string type_cast<ntl::string, ntl::data_le>(ntl::data_le const& da)
{
    return _type_cast_data_lebe(da);
}

template <>
inline_impl ntl::string type_cast<ntl::string, ntl::data_be>(ntl::data_be const& da)
{
    return _type_cast_data_lebe(da);
}

# ifdef NNT_OBJC

template <>
inline_impl NSString* type_cast< NSString*, ntl::string>(ntl::string const& str)
{
    return [NSString stringWithUTF8String:str.c_str()];
}

# endif

template <typename TVal>
static void clear_destroy(ntl::stack<TVal>& sck)
{
    while (sck.size())
    {
        TVal val = sck.top();
        safe_delete(val);
        sck.pop();
    }
}

template <typename TMap>
static void clear_destroy(TMap& map, typename TMap::mapped_type* = NULL)
{
    typedef typename TMap::iterator iterator;
    for (iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        delete &(*iter->second);
    }
    map.clear();
}

template <typename TValue, typename TMap>
static void clear_destroy(TMap& map, typename TMap::mapped_type* = NULL)
{
    typedef typename TMap::iterator iterator;
    for (iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        delete &(*(TValue)iter->second);
    }
    map.clear();
}

template <typename TMap>
static void clear_drop(TMap& map, typename TMap::mapped_type* = NULL)
{
    typedef typename TMap::iterator iterator;
    for (iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        if (iter->second)
            iter->second->drop();
    }
    map.clear();
}

template <typename TValue, typename TMap>
static void clear_drop(TMap& map, typename TMap::mapped_type* = NULL)
{
    typedef typename TMap::iterator iterator;
    for (iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        TValue val = (TValue)iter->second;
        if (val)
            val->drop();
    }
    map.clear();
}

template <typename TVal>
static void clear_destroy(ntl::vector<TVal*>& con)
{
    con.clear_destroy();
}

template <typename TVal>
static void clear_destroy(ntl::list<TVal*>& con)
{
    con.clear_destroy();
}

# endif

template <typename ValT>
class counter
{
public:
    
    counter(ValT _val)
    : count(0), val(_val)
    {
        PASS;
    }
    
    template <typename T>
    counter(T const& _val)
    : count(0)
    {
        val = _val;
    }
    
    typedef counter<ValT> self_type;
    
    counter(self_type const& r)
    : count(r.count), val(r.val)
    {
        PASS;
    }
    
    operator ValT& ()
    {
        return val;
    }
    
    operator ValT const& () const
    {
        return val;
    }
    
    operator uint () const
    {
        return count;
    }
    
    counter operator ++ (int) const
    {
        self_type ret = *this;
        ++ret;
        return ret;
    }
    
    counter& operator ++ ()
    {
        ++val;
        ++count;
        return *this;       
    }
    
    counter operator -- (int) const
    {
        self_type ret = *this;
        --ret;
        return ret;
    }
    
    counter& operator -- ()
    {
        --val;
        --count;
        return *this;       
    }
    
    self_type& operator = (ValT& r)
    {
        val = r;
        count = 0;
        return *this;
    }
    
    bool operator == (ValT const& r) const
    {
        return val == r;
    }
    
    bool operator != (ValT const& r) const
    {
        return val != r;
    }
    
    typename ValT::reference operator * ()
    {
        return *val;
    }
    
# ifdef NNT_GCC
    
    typename ValT::reference const operator * () const
    {
        return *val;
    }
    
# endif
    
    ValT& operator -> ()
    {
        return val;
    }
    
    ValT const& operator -> () const
    {
        return val;
    }
    
    ValT val;
    uint count;

};

# ifdef NNT_USER_SPACE

template <typename ValT>
inline_impl void reserve(ntl::vector<ValT>& con, usize n)
{
    con.reserve(n);
}

template <typename ValT>
inline_impl void reserve(ntl::list<ValT>& con, usize n)
{
    con.reserve(n);
}

template <typename ConT>
inline_impl void reserve(ConT& con, usize n)
{
    PASS;
}

template <typename ConT, typename ValT, typename Op>
class container
{
public:
    
    container(ValT const& _0, Op const& f) {
        f(con, _0);
    }
    
    container(ValT const& _0, ValT const& _1, Op const& f) {
        reserve(con, 2); f(con, _0); f(con, _1);
    }
    
    container(ValT const& _0, ValT const& _1, ValT const& _2, Op const& f) {
        reserve(con, 3); f(con, _0); f(con, _1); f(con, _2);
    }
    
public:

    operator ConT const& () const 
    {
        return con; 
    }
    
    operator ConT& () 
    {
        return con; 
    }    

    ConT con;

};

template <typename ConT, typename ValT>
inline_impl container<ConT, ValT, op_push_back<ConT> > push_back(ValT const& _0) 
{ 
    return container<ConT, ValT, op_push_back<ConT> > (_0, op_push_back<ConT>()); 
}

template <typename ConT, typename ValT>
inline_impl container<ConT, ValT, op_push_back<ConT> > push_back(ValT const& _0, ValT const& _1) 
{
    return container<ConT, ValT, op_push_back<ConT> > (_0, _1, op_push_back<ConT>()); 
}

template <typename ConT, typename ValT>
inline_impl container<ConT, ValT, op_insert<ConT> > insert(ValT const& _0) 
{
    return container<ConT, ValT, op_insert<ConT> > (_0, op_insert<ConT>()); 
}

template <typename ConT, typename ValT>
inline_impl container<ConT, ValT, op_insert<ConT> > insert(ValT const& _0, ValT const& _1) 
{
    return container<ConT, ValT, op_insert<ConT> > (_0, _1, op_insert<ConT>()); 
}

enum 
{
    SEQUENCE_VECTOR = 0,
    SEQUENCE_LIST = 1,
    
# ifdef NNT_OBJC
    SEQUENCE_OBJC_MUTARRAY = 0x1000000,
# endif
};

template <typename valT, int enmT>
struct sequence
{};

template <typename valT>
struct sequence<valT, SEQUENCE_VECTOR>
{ typedef ntl::vector<valT> type; };

template <typename valT>
struct sequence<valT, SEQUENCE_LIST>
{ typedef ntl::list<valT> type; };

template <typename valT>
struct value_type
{ typedef valT type; };

template <typename valT>
struct value_type<valT*>
{ typedef valT type; };

template <typename valT>
struct value_type<valT const*>
{ typedef valT type; };

# ifdef NNT_OBJC

template <bool val, typename t0, typename t1>
struct ternary
{
    typedef t1 type;
};

template <typename t0, typename t1>
struct ternary<true, t0, t1>
{
    typedef t0 type;
};

# endif

template <typename conT, typename valT>
inline_impl uint find_index(valT const& val, conT const& con)
{
    typename conT::const_iterator iter = ::std::find(con.begin(), con.end(), val);
    if (iter == con.end())
        return -1;
    return ::std::distance(con.begin(), iter);
}

# endif

template <typename T>
class wrapper
{
public:
    
    typedef T type;
    
    operator T& ()
    {
        return obj;
    }
    
    operator T const& () const
    {
        return obj;
    }
    
    T* operator -> ()
    {
        return &obj;
    }
    
    T const* operator -> () const
    {
        return &obj;
    }
    
    bool operator == (T const& r) const
    {
        return obj == r.obj;
    }
    
    bool operator != (T const& r) const
    {
        return obj != r.obj;
    }
    
    bool operator > (T const& r) const
    {
        return obj > r.obj;
    }
    
    bool operator < (T const& r) const
    {
# define _XCODE_INDENT_BUG_FIX_LESSTHAN_OPERATOR <
        return obj _XCODE_INDENT_BUG_FIX_LESSTHAN_OPERATOR r.obj;
    }
    
    bool operator >= (T const& r) const
    {
        return obj >= r.obj;
    }
    
    bool operator <= (T const& r) const
    {
# define _XCODE_INDENT_BUG_FIX_LESSEQUALTHAN_OPERATOR <=
        return obj _XCODE_INDENT_BUG_FIX_LESSEQUALTHAN_OPERATOR r.obj;
    }
    
    T obj;
    
};

template <typename TL, typename TV>
class add
{
public:
    
    TL& operator () (TL& l, TV const& v) const
    {
# define _XCODE_INDENT_BUG_FIX_STREAMIN_OPERATOR <<
        l _XCODE_INDENT_BUG_FIX_STREAMIN_OPERATOR v;
        return l;
    }
    
    static const add<TL, TV> const_p;
    
};
        
template <typename TL, typename TV>
const add<TL, TV> add<TL, TV>::const_p = add<TL, TV>();

NNT_BEGIN_NS(initializer)
        
template <typename T,
typename ActionT>
class initializer
: public wrapper<T>
{
    typedef wrapper<T> super;
    
public:
    
    typedef ActionT action_type;
    typedef typename T::value_type value_type;
    typedef T type;
    
    initializer(value_type const& _0)
    {
        action_type::const_p(this->obj, _0);
    }
    
    initializer(value_type const& _0, value_type const& _1)
    {
        action_type::const_p(action_type::const_p(this->obj, _0), _1);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8), _9);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8), _9), _10);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8), _9), _10), _11);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8), _9), _10), _11), _12);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12, value_type const& _13)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8), _9), _10), _11), _12), _13);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12, value_type const& _13, value_type const& _14)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8), _9), _10), _11), _12), _13), _14);
    }
    
    initializer(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12, value_type const& _13, value_type const& _14, value_type const& _15)
    {
        action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(action_type::const_p(this->obj, _0), _1), _2), _3), _4), _5), _6), _7), _8), _9), _10), _11), _12), _13), _14), _15);
    }
    
};
        
# define NNTWTL_INITIALIZER_IMPL(cls) \
typedef typename super::value_type value_type; \
cls(value_type const& _0) : super(_0) {} \
cls(value_type const& _0, value_type const& _1) : super(_0, _1) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2) : super(_0, _1, _2) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3) : super(_0, _1, _2, _3) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4) : super(_0, _1, _2, _3, _4) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5) : super(_0, _1, _2, _3, _4, _5) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6) : super(_0, _1, _2, _3, _4, _5, _6) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7) : super(_0, _1, _2, _3, _4, _5, _6, _7) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12, value_type const& _13) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12, value_type const& _13, value_type const& _14) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) {} \
cls(value_type const& _0, value_type const& _1, value_type const& _2, value_type const& _3, value_type const& _4, value_type const& _5, value_type const& _6, value_type const& _7, value_type const& _8, value_type const& _9, value_type const& _10, value_type const& _11, value_type const& _12, value_type const& _13, value_type const& _14, value_type const& _15) : super(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) {}
        
template <typename T>
class add
: public initializer<T, ntl::add<T, typename T::value_type> >
{
    typedef initializer<T, ntl::add<T, typename T::value_type> > super;
    
public:
    
    NNTWTL_INITIALIZER_IMPL(add);
};
        
NNT_END_NS
        
template <typename T>
class used
{
public:
    
    used()
    : _used(false)
    {
        PASS;
    }
    
    operator T& ()
    {
        _used = true;
        return _obj;
    }
    
    operator T const& () const
    {
        return _obj;
    }
    
    T* operator -> ()
    {
        _used = true;
        return &_obj;
    }
    
    T const* operator -> () const
    {
        return &_obj;
    }
    
    bool is_used() const
    {
        return _used;
    }
    
protected:
    
    T _obj;
    bool _used;
    
};

class index
{
    
    NNT_TL_CLASS_HAS_FUNC(size, has_size);
    NNT_TL_CLASS_HAS_FUNC(count, has_count);
    
public:

    template <typename T>
    static uint last(T const& v,
                     typename is_equal<typename has_size<T, uint (T::*)() const>::type, true_type>::equal* = NULL)
    {
        return v.size() - 1;
    }
    
    template <typename T>
    static uint last(T const& v,
                     typename is_equal<typename has_count<T, uint (T::*)() const>::type, true_type>::equal* = NULL)
    {
        return v.count() - 1;
    }
    
};

template <typename T>
class range
{
public:

    typedef typename T::value_type value_type;
    
    value_type distance() const
    {
        return to - from;
    }
    
    bool inside(T const& obj) const
    {
        return
        obj > from &&
        obj < to;
    }
    
    bool onside(T const& obj) const
    {
        return
        obj >= from &&
        obj <= to;
    }

    T from, to;
};

template <typename conT, typename mapT>
static conT keys(mapT const& map)
{
    typedef typename mapT::const_iterator const_iterator;
    conT ret;
    for (const_iterator iter = map.begin();
         iter != map.end();
         ++iter)
    {
        ret.push_back(iter->first);
    }
    return ret;
}

template <typename conT, typename mapT>
static conT values(mapT const& map)
{
    typedef typename mapT::const_iterator const_iterator;
    conT ret;
    for (const_iterator iter = map.begin();
         iter != map.end();
         ++iter)
    {
        ret.push_back(iter->second);
    }
    return ret;
}

template <typename T>
inline void initial(T& val, typename is_class<T>::failed const& = failed_o)
{
    val = 0;
}

template <typename T>
inline void initial(T& val, typename is_class<T>::match const& = match_o)
{
    PASS;
}

template <typename T>
inline void initial(T*& ptr)
{
    ptr = NULL;
}

template <typename T>
inline T initial()
{
    T ret;
    alloc::Heap<T>::Fill(&ret, 1, 0);
    return ret;
}

# ifndef MAX
#   define MAX(a, b) ((a) > (b) ? (a) : (b))
# endif

# ifndef MIN
#   define MIN(a, b) ((a) < (b) ? (a) : (b))
# endif

# ifdef NNT_STL

template <typename valT, typename iterT>
static valT max(iterT begin, iterT const& end)
{
    valT ret = 0;
    for (; begin != end; ++begin)
        ret = MAX(ret, *begin);
    return ret;
}

template <typename valT, typename iterT>
static valT min(iterT begin, iterT const& end)
{
    valT ret = 0xFFFFFFFF;
    for (; begin != end; ++begin)
        ret = MIN(ret, *begin);
    return ret;
}

template <typename valT, typename iterT>
static ::std::pair<valT, valT> max_min(iterT begin, iterT const& end)
{
    ::std::pair<valT, valT> ret;
    ret.first = 0;
    ret.second = 0xFFFFFFFF;
    for (; begin != end; ++begin)
    {
        ret.first = MAX(ret.first, *begin);
        ret.second = MIN(ret.second, *begin);
    }
    return ret;
}

template <typename valT, typename iterT>
static valT sum(iterT begin, iterT const& end)
{
    valT ret = 0;
    for (; begin != end; ++begin)
        ret += *begin;
    return ret;
}

# endif

NNT_END_NS

NNT_END_HEADER_CXX

# endif // cxx

# endif
