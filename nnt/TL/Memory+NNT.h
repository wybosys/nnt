
# ifndef __NNT_TL_MEMORY_a17e3a7230e54d4e9290f9f1bf9a6d0c_H_INCLUDED
# define __NNT_TL_MEMORY_a17e3a7230e54d4e9290f9f1bf9a6d0c_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

template <typename osT = os_type, typename spaceT = space_type>
class Memory
{
public:

    static void Copy(void* des, void const* src, usize len);
    static void Move(void* des, void const* src, usize len);
    static void Fill(void* des, usize len, int data);
    static bool Equal(void const* des, void const* src, usize len);

};

template <typename osT, typename spaceT>
class Pointer
{
public:

    template <typename valT>
    static void* Pvoid(valT const& obj)
    {
        return (void*)&obj;
    }

    template <typename valT>
    static void* Pvoid(valT const* obj)
    {
        return (void*)obj;
    }

    static void* Offset(void const* ptr, usize offset)
    {
        return (void*)(((byte*)ptr) + offset);
    }

};

# ifdef NNT_USER_SPACE

template <typename osT>
class Memory <osT, space_user>
    : public Pointer <osT, space_user>
{
public:

    static void Copy(void* des, void const* src, usize len)
    {
        memcpy(des, src, len);
    }

    static void Move(void* des, void const* src, usize len)
    {
        memmove(des, src, len);
    }

    static void Fill(void* des, usize len, int data)
    {
        memset(des, data, len);
    }

    static bool Equal(void const* des, void const* src, usize len)
    {
        return memcmp(des, src, len) == 0;
    }

};

# endif

# ifdef NNT_MSVC

template <>
class Memory <os_windows, space_kernel>
    : public Pointer <os_windows, space_kernel>
{
public:

    static void Copy(void* des, void const* src, usize len)
    {
        ::RtlCopyMemory(des, src, len);
    }

    static void Move(void* des, void const* src, usize len)
    {
        ::RtlMoveMemory(des, src, len);
    }

    static void Fill(void* des, usize len, int data)
    {
        ::RtlFillMemory(des, len, data);
    }

    static bool Equal(void const* des, void const* src, usize len)
    {
        return ::RtlCompareMemory(des, src, len) != 0;
    }

};

# endif

# ifdef NNT_BSD

template <>
class Memory <os_bsd, space_kernel>
    : public Pointer <os_bsd, space_kernel>
{
 public:

    static void Copy(void* des, void const* src, usize len)
    {
        memcpy(des, src, len);
    }

    static void Move(void* des, void const* src, usize len)
    {
        memmove(des, src, len);
    }

    static void Fill(void* des, usize len, int data)
    {
        memset(des, data, len);
    }

    static bool Equal(void const* des, void const* src, usize len)
    {
        return memcmp(des, src, len) == 0;
    }

};

# endif

# ifdef NNT_LINUX

template <>
class Memory <os_linux, space_kernel>
{
public:

    static void Copy(void* des, void const* src, usize len)
    {
        memcpy(des, src, len);
    }

    static void Move(void* des, void const* src, usize len)
    {
        memmove(des, src, len);
    }

    static void Fill(void* des, usize len, int data)
    {
        memset(des, data, len);
    }

    static bool Equal(void const* des, void const* src, usize len)
    {
        return memcmp(des, src, len) == 0;
    }
    
};

# endif

template <typename osT>
class Memory <osT, space_gpu>
{
public:
    
    static void Copy(void* des, void const* src, usize len)
    {
        MUSTIMPLEMENT;
    }
    
    static void Move(void* des, void const* src, usize len)
    {
        MUSTIMPLEMENT;
    }
    
    static void Fill(void* des, usize len, int data)
    {
        MUSTIMPLEMENT;
    }
    
    static bool Equal(void const* des, void const* src, usize len)
    {
        MUSTIMPLEMENT;
        return false;
    }
    
};

template <typename objT>
inline size_t size_of(objT const&)
{
    return sizeof(objT);
}

template <typename objT>
inline size_t size_of(objT const*)
{
    return sizeof(objT);
}

template <typename objT>
inline void zero(objT& obj)
{
    Memory<>::Fill(&obj, sizeof(objT), 0);
}

template <typename objT>
inline void zero(objT* obj)
{
    Memory<>::Fill(obj, sizeof(objT), 0);
}

# ifdef NNT_HAS_FLOAT

template <uint BLOCK=1024>
class MemoryPresention
{
public:
        
    template <typename T>
    static T K(T const& v)
    {
        static const float _1_K = 1.f / BLOCK;
        return (T)(_1_K * v);
    }
        
    template <typename T>
    static T M(T const& v)
    {
        static const float _1_M = 1.f / BLOCK / BLOCK;
        return (T)(_1_M * v);
    }    
    
    template <typename T>
    static T G(T const& v)
    {
        static const float _1_G = 1.f / BLOCK / BLOCK / BLOCK;
        return (T)(_1_G * v);
    }    
    
    template <typename V>
    static V T(V const& v)
    {
        static const float _1_T = 1.f / BLOCK / BLOCK / BLOCK / BLOCK;
        return (T)(_1_T * v);
    }    
    
    template <typename T>
    static T P(T const& v)
    {
        static const float _1_P = 1.f / BLOCK / BLOCK / BLOCK / BLOCK / BLOCK;
        return (T)(_1_P * v);
    }
    
};

# endif

NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif
