
# ifndef __NNT_TL_MEMORY_a17e3a7230e54d4e9290f9f1bf9a6d0c_H_INCLUDED
# define __NNT_TL_MEMORY_a17e3a7230e54d4e9290f9f1bf9a6d0c_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

class Void
{
public:

    template <typename valT>
    static void* pointer(valT const& obj)
    {
        return (void*)&obj;
    }

    template <typename valT>
    static void* pointer(valT const* obj)
    {
        return (void*)obj;
    }

};

template <typename valT>
class Common
{
public:

    typedef valT value_type;

    template <typename desT, typename srcT>
    static void Copy(desT& des, srcT const& src, usize sz = sizeof(value_type))
    {
        void* pdes = Void::pointer(des);
        void* psrc = Void::pointer(src);

# ifdef NNT_USER_SPACE
# else
# ifdef NNT_MSVC
        ::RtlCopyMemory(pdes, psrc, sz);
# endif
# endif
    }

    template <typename desT, typename srcT>
    static void Move(desT& des, srcT const& src, usize sz = sizeof(value_type))
    {
        void* pdes = Void::pointer(des);
        void* psrc = Void::pointer(src);

# ifdef NNT_USER_SPACE
# else
# ifdef NNT_MSVC
        ::RtlMoveMemory(pdes, psrc, sz);
# endif
# endif
    }

    template <typename desT>
    static void Fill(desT& des, ubyte da = 0, usize sz = sizeof(value_type))
    {
        void* pdes = Void::pointer(des);

# ifdef NNT_USER_SPACE
# else
# ifdef NNT_MSVC
        ::RtlFillMemory(pdes, sz, da);
# endif
# endif
    }

    template <typename desT, typename srcT>
    static bool Equal(desT const& des, srcT const& src, usize sz = sizeof(value_type))
    {
        void* pdes = Void::pointer(des);
        void* psrc = Void::pointer(src);

# ifdef NNT_USER_SPACE
# else
# ifdef NNT_MSVC
        return 0 != ::RtlCompareMemory(pdes, psrc, sz);
# endif
# endif
    }

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif
