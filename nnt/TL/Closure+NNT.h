
# ifndef __NNTWTL_CLOSURE_F9091CB3213E40D196B67C6FA949FB86_H_INCLUDED
# define __NNTWTL_CLOSURE_F9091CB3213E40D196B67C6FA949FB86_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

# ifdef NNT_CLANG

# pragma GCC diagnostic ignored "-Wlocal-type-template-args"

# endif

template <typename impT>
struct sc
{
    static const impT imp;
};

template <typename impT>
const impT sc<impT>::imp = impT();

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
