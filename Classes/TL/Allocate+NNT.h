
# ifndef __NNT_TL_ALLOCATE_c14a9fb41a694a47a67874bad371520f_H_INCLUDED
# define __NNT_TL_ALLOCATE_c14a9fb41a694a47a67874bad371520f_H_INCLUDED

# ifdef NNT_CXX

# include "Memory+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(alloc)

template <typename valT, typename osT = os_type, typename spaceT = space_type>
class Heap
{
public:

    typedef valT value_type;

    //! create n size object.
    static value_type* Create(usize);

    //! alloc n * size memory.
    static value_type* Alloc(usize);

    //! free objects.
    static void Free(void*);

};

template <typename valT, typename osT, typename spaceT>
class HeapMemory
{
public:

    typedef valT value_type;
    typedef Memory<osT, spaceT> Memory;

    static void Copy(void* des, void const* src, usize count)
    {
        Memory::Copy(des, src, count * sizeof(value_type));
    }

    static void Move(void* des, void const* src, usize count)
    {
        Memory::Move(des, src, count * sizeof(value_type));
    }

    static void Fill(void* des, usize count, ubyte da)
    {
        Memory::Fill(des, count * sizeof(value_type), da);
    }

    static void* Offset(void* des, usize count)
    {
        return (void*)(((byte*)des) + count * sizeof(value_type));
    }

    static usize Length(usize count)
    {
        return count * sizeof(value_type);
    }

    static usize Count(usize length)
    {
        return length / sizeof(value_type);
    }

};

# ifdef NNT_USER_SPACE

template <typename valT, typename osT>
class Heap <valT, osT, space_user>
    : public HeapMemory<valT, osT, space_user>
{
public:

    typedef valT value_type;

    static value_type* Create(usize count = 1)
    {
        return (value_type*)malloc(count * sizeof(value_type));
    }

    static value_type* Alloc(usize size)
    {
        return (value_type*)malloc(size);
    }

    static void Free(void* ptr)
    {
        return free(ptr);
    }

};

# endif

template <typename valT>
class Heap <valT, os_mach, space_kernel>
{

};

# ifdef NNT_MSVC

template <typename valT>
class Heap <valT, os_windows, space_kernel>
    : public HeapMemory< valT, os_windows, space_kernel>
{
public:

    typedef valT value_type;

    static value_type* Create(usize count = 1)
    {
        return (value_type*)::ExAllocatePoolWithTag(PagedPool, count * sizeof(value_type), (LONG)"ntla");
    }

    static value_type* Alloc(usize size)
    {
        return (value_type*)::ExAllocatePoolWithTag(PagedPool, size, (LONG)"ntla");
    }

    static void Free(void* ptr)
    {
        ::ExFreePoolWithTag(ptr, (LONG)"ntla");
    }

};

# endif

# ifdef NNT_BSD

NNT_BEGIN_HEADER_C
MALLOC_DECLARE(NNT_MP_NTLA);
NNT_END_HEADER_C

template <typename valT>
class Heap <valT, os_bsd, space_kernel>
    : public HeapMemory <valT, os_bsd, space_kernel>
{
 public:

    typedef valT value_type;

    static value_type* Create(usize count = 1)
    {
        return (value_type*)malloc(count * sizeof(value_type), NNT_MP_NTLA, M_NOWAIT); 
    }

    static value_type* Alloc(usize size)
    {
        
    }

    static void Free(void* ptr)
    {
        
    }
    
};

# endif

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# ifdef NNT_KERNEL_SPACE

# ifdef NNT_MSVC

static void* operator new(size_t sz)
{
    return ::ExAllocatePoolWithTag(PagedPool, sz, (LONG)"cxxn");
}

static void* operator new(size_t sz, POOL_TYPE pt)
{
    return ::ExAllocatePoolWithTag(pt, sz, (LONG)"cxxn");
}

static void operator delete(void* ptr)
{
    ::ExFreePoolWithTag(ptr, (LONG)"cxxn");
}

# else

inline void* operator new(size_t sz)
{
    NNT_USINGNAMESPACE;
    typedef ntl::alloc::Heap<byte> heap;
    return heap::Create(sz);
}

inline void operator delete(void* ptr)
{
    NNT_USINGNAMESPACE;
    typedef ntl::alloc::Heap<byte> heap;
    heap::Free(ptr);
}

# endif

# endif // kernel space

# endif // cxx

# endif
