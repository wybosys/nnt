
# ifndef __WSIWTL_CLOSURE_F9091CB3213E40D196B67C6FA949FB86_H_INCLUDED
# define __WSIWTL_CLOSURE_F9091CB3213E40D196B67C6FA949FB86_H_INCLUDED

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(wtl)

# ifdef WSI_CLANG

# pragma GCC diagnostic ignored "-Wlocal-type-template-args"

# endif

template <typename impT>
struct sc
{
    static const impT imp;
};

template <typename impT>
const impT sc<impT>::imp = impT();

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
