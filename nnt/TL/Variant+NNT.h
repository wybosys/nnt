
# ifndef __NNT_VARIANT_467F380F66F5458EAE6DBD03A6F110E1_H_INCLUDED
# define __NNT_VARIANT_467F380F66F5458EAE6DBD03A6F110E1_H_INCLUDED

# ifdef NNT_CXX

# include "./Memory+NNT.h"
# include "./Allocate+NNT.h"

NNT_BEGIN_HEADER_CXX

class variant_t
{
protected:

    typedef variant_t self_type;
    typedef ntl::Memory<> Mem;
    typedef ntl::alloc::Heap<byte> Heap;

public:        
    
    typedef enum {
        VT_UNKNOWN = 0,
        VT_SIGNEDINT = 1,
        VT_UNSIGNEDINT = 2,
        VT_SIGNEDCHAR = 3,
        VT_UNSIGNEDCHAR = 4,
        VT_SIGNEDSHORT = 5,
        VT_UNSIGNEDSHORT = 6,
        VT_SIGNEDLONG = 7,
        VT_UNSIGNEDLONG = 8,
        VT_FLOAT = 9,
        VT_DOUBLE = 10,
        VT_PCHAR = 11,
        VT_DATA = 12,        
        VT_BOOLEAN = 16,
        VT_ID = 13,
        VT_REFOBJ = 14,
        VT_POINTER = 15,
        
    } ValueType;
    
    ValueType vt;
    
protected:
    
    union 
    {
        signed int si;
        unsigned int ui;
        signed char sc;
        unsigned char uc;
        signed short ss;
        unsigned short us;
        signed long sl;
        unsigned long ul;
        char const* ssr;
        void* data;

# ifdef NNT_HAS_FLOAT
        float f;
        double d;
# endif
        
        bool b;
        
# ifdef NNT_OBJC
        id idobj;
# else
        void* idobj;
# endif
        
# ifdef NNT_USER_SPACE
        RefObject const* refobj;
# else
        void const* refobj;
# endif

        void* ptr;
        
    } _v;
    
public:

    variant_t()
    : _rel(false), _sz(0), vt(VT_UNKNOWN)
    {
        Mem::Fill(&_v, sizeof(_v), 0);
    }
    
    explicit variant_t(bool v)
    : _rel(false), _sz(sizeof(bool)), vt(VT_BOOLEAN)
    {
        _v.b = v;
    }
    
    explicit variant_t(signed int const v)
    : _rel(false), _sz(sizeof(signed int)), vt(VT_SIGNEDINT)
    {
        _v.si = v;
    }
    
    explicit variant_t(unsigned int v)
    : _rel(false), _sz(sizeof(unsigned int)), vt(VT_UNSIGNEDINT)
    {
        _v.ui = v;
    }
    
    explicit variant_t(signed char v)
    : _rel(false), _sz(sizeof(signed char)), vt(VT_SIGNEDCHAR)
    {
        _v.sc = v;
    }
    
    explicit variant_t(unsigned char v)
    : _rel(false), _sz(sizeof(unsigned char)), vt(VT_UNSIGNEDCHAR)
    {
        _v.uc = v;
    }
    
    explicit variant_t(signed short v)
    : _rel(false), _sz(sizeof(signed short)), vt(VT_SIGNEDSHORT)
    {
        _v.ss = v;
    }
    
    explicit variant_t(unsigned short v)
    : _rel(false), _sz(sizeof(unsigned short)), vt(VT_UNSIGNEDSHORT)
    {
        _v.us = v;
    }
    
    explicit variant_t(signed long v)
    : _rel(false), _sz(sizeof(signed long)), vt(VT_SIGNEDLONG)
    {
        _v.sl = v;
    }
    
    explicit variant_t(unsigned long v)
    : _rel(false), _sz(sizeof(unsigned long)), vt(VT_UNSIGNEDLONG)
    {
        _v.ul = v;
    }

# ifdef NNT_HAS_FLOAT
    
    explicit variant_t(float v)
    : _rel(false), _sz(sizeof(float)), vt(VT_FLOAT)
    {
        _v.f = v;
    }
    
    explicit variant_t(double v)
    : _rel(false), _sz(sizeof(double)), vt(VT_DOUBLE)
    {
        _v.d = v;
    }

# endif
    
# ifdef NNT_OBJC
    
    explicit variant_t(id v)
    : _rel(false), _sz(sizeof(id)), vt(VT_ID)
    {
        _v.idobj = [v retain];
    }
    
    explicit variant_t(NSObject* v)
    : _rel(false), _sz(sizeof(id)), vt(VT_ID)
    {
        _v.idobj = [v retain];
    }
    
# endif
    
# ifdef NNT_USER_SPACE

    explicit variant_t(RefObject const* v)
    : _rel(false), _sz(sizeof(void*)), vt(VT_REFOBJ)
    {
        if (v)
            v->grab();
        _v.refobj = v;
    }

# endif
    
    explicit variant_t(char const* str, core::_bool_copy cpy, usize len = -1)
    : vt(VT_PCHAR)
    {
        _rel = core::copy == cpy;
        _sz = ((int)len == -1) ? strlen(str) : len;
        if (cpy == core::copy)
        {
            _v.ssr = (char const*)Heap::Alloc(_sz);
            Heap::Copy((void*)_v.ssr, str, _sz);
        }
        else
        {
            _v.ssr = str;
        }
    }
    
    explicit variant_t(void* data, usize len, core::_bool_copy cpy)
    : vt(VT_DATA), _sz(len)
    {
        _rel = core::copy == cpy;
        if (cpy == core::copy)
        {
            _v.data = (void*)Heap::Alloc(_sz);
            Heap::Copy(_v.data, data, _sz);
        }
        else
        {
            _v.data = data;
        }
    }
    
    explicit variant_t(void* ptr)
    : _rel(false), vt(VT_POINTER), _sz(sizeof(void*))
    {
        _v.ptr = ptr;
    }
    
    variant_t(variant_t const& r)
    {
        _rel = r._rel;        
        _sz = r._sz;
        vt = r.vt;
        if (_rel)
        {
            _v.data = (void*)Heap::Alloc(_sz);
            Heap::Copy(_v.data, r._v.data, _sz);
        }
        else
        {
            _v = r._v;
        }
    }
    
    variant_t& operator = (variant_t const& r)
    {
        this->clear();
        
        _rel = r._rel;        
        _sz = r._sz;
        vt = r.vt;
        
        if (_rel)
        {
            _v.data = Heap::Alloc(_sz);
            Heap::Copy(_v.data, r._v.data, _sz);
        }
        else 
        {
            _v = r._v;
        }
        
# ifdef NNT_USER_SPACE

        if (vt == VT_REFOBJ)
        {
            if (_v.refobj)
                _v.refobj->grab();
        }

# endif
        
# ifdef NNT_OBJC
       
        if (vt == VT_ID)
        {
            [_v.idobj retain];
        }
        
# endif
        
        return *this;
    }
    
    ~variant_t()
    {
        this->clear();
    }
        
    void clear()
    {
        if (vt == VT_UNKNOWN)
            return;
        
        _sz = 0;
        if (_rel)
        {
            Heap::Free(_v.data);
            _rel = false;         
        }
        
# ifdef NNT_USER_SPACE

        if (vt == VT_REFOBJ)
        {
            if (_v.refobj)
                _v.refobj->drop();
        }

# endif
        
# ifdef NNT_OBJC

        if (vt == VT_ID)
        {
            [_v.idobj release];
        }

# endif
     
        vt = VT_UNKNOWN;
        Heap::Fill(&_v, sizeof(_v), 0);
    }
    
    operator bool () const
    {
        return _v.b;
    }
    
    operator bool& ()
    {
        return _v.b;
    }
    
    variant_t& operator = (bool v)
    {
        return set(v);
    }
    
    variant_t& set (bool v)
    {
        clear();
        vt = VT_BOOLEAN;
        _v.b = v;
        return *this;
    }
    
    operator signed int () const
    {
        return _v.si;
    }
    
    operator signed int & ()
    {
        return _v.si;
    }
    
    variant_t& operator = (signed int v)
    {
        return set(v);
    }
    
    variant_t& set (signed int v)
    {
        clear();
        vt = VT_SIGNEDINT;
        _v.si = v;
        return *this;
    }
    
    operator unsigned int () const
    {
        return _v.ui;
    }
    
    operator unsigned int & ()
    {
        return _v.ui;
    }
    
    variant_t& operator = (unsigned int v)
    {
        return set(v);
    }
    
    variant_t& set (unsigned int v)
    {
        clear();
        vt = VT_UNSIGNEDINT;
        _v.ui = v;
        return *this;
    }
    
    operator signed char () const
    {
        return _v.sc;
    }
    
    operator signed char & ()
    {
        return _v.sc;
    }
    
    variant_t& operator = (signed char v)
    {
        return set(v);
    }
    
    variant_t& set (signed char v)
    {
        clear();
        vt = VT_SIGNEDCHAR;
        _v.sc = v;
        return *this;
    }
    
    operator unsigned char () const
    {
        return _v.uc;
    }
    
    operator unsigned char & ()
    {
        return _v.uc;
    }
    
    variant_t& operator = (unsigned char v)
    {
        return set(v);
    }
    
    variant_t& set (unsigned char v)
    {
        clear();
        vt = VT_UNSIGNEDCHAR;
        _v.uc = v;
        return *this;
    }
    
    operator signed short () const
    {
        return _v.ss;
    }
    
    operator signed short & ()
    {
        return _v.ss;
    }
    
    variant_t& operator = (signed short v)
    {
        return set(v);
    }
    
    variant_t& set (signed short v)
    {
        clear();
        vt = VT_SIGNEDSHORT;
        _v.ss = v;
        return *this;
    }
    
    operator unsigned short () const
    {
        return _v.us;
    }
    
    operator unsigned short & ()
    {
        return _v.us;
    }
    
    variant_t& operator = (unsigned short v)
    {
        return set(v);
    }
    
    variant_t& set (unsigned short v)
    {
        clear();
        vt = VT_UNSIGNEDSHORT;
        _v.us = v;
        return *this;
    }
    
    operator signed long () const
    {
        return _v.sl;
    }
    
    operator signed long & ()
    {
        return _v.sl;
    }
    
    variant_t& operator = (signed long v)
    {
        return set(v);
    }
    
    variant_t& set (signed long v)
    {
        clear();
        vt = VT_SIGNEDLONG;
        _v.sl = v;
        return *this;
    }
    
    operator unsigned long () const
    {
        return _v.ul;
    }
    
    operator unsigned long & ()
    {
        return _v.ul;
    }
    
    variant_t& operator = (unsigned long v)
    {
        return set(v);
    }
    
    variant_t& set (unsigned long v)
    {
        clear();
        vt = VT_UNSIGNEDLONG;
        _v.ul = v;
        return *this;
    }

# ifdef NNT_HAS_FLOAT
    
    operator float () const
    {
        return _v.f;
    }
    
    operator float & ()
    {
        return _v.f;
    }
    
    variant_t& operator = (float v)
    {
        return set(v);
    }
    
    variant_t& set (float v)
    {
        clear();
        vt = VT_FLOAT;
        _v.f = v;
        return *this;
    }
    
    operator double () const
    {
        return _v.d;
    }
    
    operator double & ()
    {
        return _v.d;
    }
    
    variant_t& operator = (double v)
    {
        return set(v);
    }
    
    variant_t& set (double v)
    {
        clear();
        vt = VT_DOUBLE;
        _v.d = v;
        return *this;
    }

# endif

# ifdef NNT_USER_SPACE
    
    operator RefObject* () const
    {
        return (RefObject*)_v.refobj;
    }
    
    operator RefObject const* () const
    {
        return _v.refobj;
    }
    
    variant_t& operator = (RefObject const* v)
    {
        return set(v);
    }
    
    variant_t& set (RefObject const* v)
    {
        clear();
        vt = VT_REFOBJ;
        if (v)
            v->grab();
        if (_v.refobj)
            _v.refobj->drop();
        _v.refobj = v;
        return *this;
    }

# endif
    
# ifdef NNT_OBJC
    
    operator id () const
    {
        return _v.idobj;
    }
    
    variant_t& operator = (id v)
    {
        return set(v);
    }
    
    variant_t& set (id v)
    {
        clear();
        vt = VT_ID;
        [v retain];
        [_v.idobj release];
        _v.idobj = v;
        return *this;
    }
    
    variant_t& operator = (NSObject* v)
    {
        return set(v);
    }
    
    variant_t& set (NSObject* v)
    {
        clear();
        vt = VT_ID;
        [v retain];
        [_v.idobj release];
        _v.idobj = v;
        return *this;
    }
    
# endif
    
    variant_t& operator = (void const* ptr)
    {
        return set(ptr);
    }
    
    variant_t& set (void const* ptr)
    {
        clear();
        vt = VT_POINTER;
        _v.ptr = (void*)ptr;
        return *this;
    }
        
    operator void* () const
    {
        return (void*)_v.ptr;
    }
    
    operator char const* () const
    {
        return _v.ssr;
    }
    
    operator core::string () const;
    
# ifdef NNT_USER_SPACE

    variant_t& operator = (core::string const& str)
    {
        set_str(str.c_str(), core::copy, str.length());
        return *this;
    }
    
    void set(char const* str)
    {
        set_str(str, core::copy);
    }
    
    void set(uchar const* str)
    {
        set_str((char const*)str, core::copy);
    }
    
    void set(char str[])
    {
        set_str(str, core::copy);
    }
    
    variant_t& operator = (char const* str)
    {
        set(str);
        return *this;
    }
    
    variant_t& operator = (uchar const* str)
    {
        set(str);
        return *this;
    }
    
    variant_t& operator = (char str[])
    {
        set(str);
        return *this;
    }
    
    void set_str(char const* str, core::_bool_copy cpy, usize len = -1)
    {
        clear();
        
        _rel = core::copy == cpy;
        _sz = (len == -1) ? strlen(str) : len;
        if (cpy == core::copy)
        {
            if (_sz)
            {
                _v.ssr = (char const*)Heap::Alloc(_sz);
                Heap::Copy((void*)_v.ssr, str, _sz);
            }
        }
        else
        {
            _v.ssr = str;
        }
        
        vt = VT_PCHAR;
    }

# endif    

    void set_data(void const* data, usize len, core::_bool_copy cpy)
    {
        clear();
        
        _rel = core::copy == cpy;
        _sz = len;
        if (cpy == core::copy)
        {
            if (_sz)
            {
                _v.data = (void*)Heap::Alloc(_sz);
                Heap::Copy(_v.data, data, _sz);
            }
        }
        else
        {
            _v.data = (void*)data;
        }
        
        vt = VT_DATA;
    }
    
    void set(core::data const& da)
    {
        set_data(da.bytes(), da.length(), core::copy);
    }
    
    variant_t& operator = (core::data const& da)
    {
        set(da);
        return *this;
    }
    
    template <typename valT>
    variant_t& operator = (valT const& r)
    {
        ntl::const_pointer<valT> ptr(r);
        return set(&(*ptr));
    }
    
    operator core::data () const
    {
        return core::data((byte const*)_v.data, _sz);
    }
    
    usize size() const
    {
        return _sz;
    }
    
    void* address() const
    {
        return (void*)&_v;
    }
    
# ifdef NNT_USER_SPACE

    void stringize();

# endif
    
    // get value.
    int toint() const;

# ifdef NNT_HAS_FLOAT
    
    float tofloat() const;
    double todouble() const;

# endif
    
    static variant_t const& Null()
    {
        static const variant_t var;
        return var;
    }
    
protected:
    
    bool _rel;
    usize _sz;

};

# ifdef NNT_STL

template <typename StmT>
inline_impl StmT& operator << (StmT& stm, variant_t const* var)
{
    stm << *var;
    return stm;
}

template <typename StmT, typename VarT>
inline_impl StmT& operator << (StmT& stm, null_obj<VarT> const* var)
{
    if (var)
        stm << *(VarT const*)var;
    return stm;
}

template <typename StmT>
static StmT& operator << (StmT& stm, variant_t const& var)
{    
    switch (var.vt)
    {
        case variant_t::VT_UNKNOWN:
            break;
        case variant_t::VT_BOOLEAN:
            stm << (bool)var;
            break;
        case variant_t::VT_SIGNEDINT:
            stm << (signed int)var;
            break;
        case variant_t::VT_UNSIGNEDINT:
            stm << (unsigned int)var;
            break;
        case variant_t::VT_SIGNEDCHAR:
            stm << (signed char)var;
            break;
        case variant_t::VT_UNSIGNEDCHAR:
            stm << (unsigned int)var;
            break;
        case variant_t::VT_SIGNEDLONG:
            stm << (signed long)var;
            break;
        case variant_t::VT_UNSIGNEDLONG:
            stm << (unsigned long)var;
            break;
        case variant_t::VT_SIGNEDSHORT:
            stm << (signed short)var;
            break;
        case variant_t::VT_UNSIGNEDSHORT:
            stm << (unsigned short)var;
            break;
        case variant_t::VT_FLOAT:
            stm << (float)var;
            break;
        case variant_t::VT_DOUBLE:
            stm << (double)var;
            break;
        case variant_t::VT_PCHAR:
            stm << core::string((char const*)var, var.size());
            break;
        case variant_t::VT_DATA:
            stm << core::string((char const*)var, var.size());
            break;
        case variant_t::VT_ID:
        case variant_t::VT_REFOBJ:
        case variant_t::VT_POINTER:
            break;
    };

    return stm;
}

inline_impl void variant_t::stringize()
{
    core::stringstream ss;
    ss << *this;
    core::string str = ss.str();
    this->clear();
    this->set_str(str.c_str(), core::copy, str.length());
}

# endif

NNT_BEGIN_NS(ntl)

# ifdef NNT_USER_SPACE

static string tostr(variant_t const& var)
{
    core::stringstream ss;
    ss << var;
    return ss.str();
}

# endif

static int toint(variant_t const& var)
{
    int ret = 0;
    switch (var.vt)
        {
        default: break;
        case variant_t::VT_SIGNEDCHAR:
        case variant_t::VT_UNSIGNEDCHAR:
            ret = (int)(schar)var;
            break;
        case variant_t::VT_SIGNEDSHORT:
        case variant_t::VT_UNSIGNEDSHORT:
            ret = (int)(short)var;
            break;
        case variant_t::VT_SIGNEDINT:
        case variant_t::VT_UNSIGNEDINT:
            ret = (int)var;
            break;
        case variant_t::VT_SIGNEDLONG:
        case variant_t::VT_UNSIGNEDLONG:
            ret = (int)(long)var;
            break;
# ifdef NNT_HAS_FLOAT
        case variant_t::VT_FLOAT:
            ret = (int)(float)var;
            break;
        case variant_t::VT_DOUBLE:
            ret = (int)(double)var;
            break;
# endif
# ifdef NNT_USER_SPACE
        case variant_t::VT_PCHAR:
            ret = atoi((char const*)var);
            break;
# endif
    }
    return ret;
}

# ifdef NNT_HAS_FLOAT

static float tofloat(variant_t const& var)
{
    float ret = 0;
    switch (var.vt)
        {
        default: break;
        case variant_t::VT_SIGNEDCHAR:
        case variant_t::VT_UNSIGNEDCHAR:
            ret = (float)(schar)var;
            break;
        case variant_t::VT_SIGNEDSHORT:
        case variant_t::VT_UNSIGNEDSHORT:
            ret = (float)(short)var;
            break;
        case variant_t::VT_SIGNEDINT:
        case variant_t::VT_UNSIGNEDINT:
            ret = (float)(int)var;
            break;
        case variant_t::VT_SIGNEDLONG:
        case variant_t::VT_UNSIGNEDLONG:
            ret = (float)(long)var;
            break;
        case variant_t::VT_FLOAT:
            ret = (float)var;
            break;
        case variant_t::VT_DOUBLE:
            ret = (float)(double)var;
            break;
        case variant_t::VT_PCHAR:
            ret = (float)atof((char const*)var);
            break;
    }
    return ret;
}

static double todouble(variant_t const& var)
{
    double ret = 0;
    switch (var.vt)
        {
        default: break;
        case variant_t::VT_SIGNEDCHAR:
        case variant_t::VT_UNSIGNEDCHAR:
            ret = (double)(schar)var;
            break;
        case variant_t::VT_SIGNEDSHORT:
        case variant_t::VT_UNSIGNEDSHORT:
            ret = (double)(short)var;
            break;
        case variant_t::VT_SIGNEDINT:
        case variant_t::VT_UNSIGNEDINT:
            ret = (double)(int)var;
            break;
        case variant_t::VT_SIGNEDLONG:
        case variant_t::VT_UNSIGNEDLONG:
            ret = (double)(long)var;
            break;
        case variant_t::VT_FLOAT:
            ret = (double)(float)var;
            break;
        case variant_t::VT_DOUBLE:
            ret = (double)var;
            break;
        case variant_t::VT_PCHAR:
            ret = atof((char const*)var);
            break;
    }
    return ret;
}

# endif

template <>
inline_impl variant_t dup_cast<variant_t, string>(string const& str)
{
    return variant_t((char const*)str.c_str(), core::copy, str.length());
}

template <>
inline_impl variant_t dup_cast<variant_t, data>(data const& str)
{
    return variant_t((void*)str.bytes(), str.length(), core::copy);
}

NNT_END_NS

# ifdef NNT_USER_SPACE

inline_impl variant_t::operator core::string () const
{
    return core::tostr(*this);
}

# endif

inline_impl int variant_t::toint() const
{
    return core::toint(*this);
}

# ifdef NNT_HAS_FLOAT
    
inline_impl float variant_t::tofloat() const
{
    return core::tofloat(*this);
}

inline_impl double variant_t::todouble() const
{
    return core::todouble(*this);
}

# endif

NNT_END_HEADER_CXX

# endif

# endif
