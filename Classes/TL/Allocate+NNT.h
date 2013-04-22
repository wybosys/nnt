
# ifndef __NNT_CORE_ALLOCATE_c14a9fb41a694a47a67874bad371520f_H_INCLUDED
# define __NNT_CORE_ALLOCATE_c14a9fb41a694a47a67874bad371520f_H_INCLUDED

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
        return (value_type*)::ExAllocatePoolWithTag(value_type, sizeof(value_type), (LONG)"ntla");
# endif
    }

    static void Delete(void* ptr)
    {
# ifdef NNT_MSVC
        ::ExFreePoolWithTag(ptr, (LONG)"ntla");
# endif
    }

};

# endif // user space.

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif
