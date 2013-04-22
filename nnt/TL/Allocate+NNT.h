
# ifndef __NNT_TL_ALLOCATE_c14a9fb41a694a47a67874bad371520f_H_INCLUDED
# define __NNT_TL_ALLOCATE_c14a9fb41a694a47a67874bad371520f_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)
NNT_BEGIN_NS(alloc)

# ifdef NNT_USER_SPACE

# else // kernel space.

template <typename valT>
class Heap
{
public:

    typedef valT value_type;

    static value_type* New()
    {
# ifdef NNT_MSVC
        return (value_type*)::ExAllocatePoolWithTag(PagedPool, sizeof(value_type), (LONG)"ntla");
# endif
    }

    static void Delete(void* ptr)
    {
# ifdef NNT_MSVC
        ::ExFreePoolWithTag(ptr, (LONG)"ntla");
# endif
    }

};

# ifdef NNT_MSVC

// global new & delete operators.

static void* __cdecl operator new(size_t sz, POOL_TYPE pt = PagedPool)
{
    return ::ExAllocatePoolWithTag(pt, sz, (LONG)"cxxn");
}

static void __cdecl operator delete(void* ptr)
{
    ::ExFreePoolWithTag(ptr, (LONG)"cxxn");
}

# endif

# endif // user space.

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif
