
# ifndef __NNT_FOUNDATION_HASH_3ebf721c1e6e41eeb6e27708cb7e1cdb_H_INCLUDED
# define __NNT_FOUNDATION_HASH_3ebf721c1e6e41eeb6e27708cb7e1cdb_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

template <typename valT, typename retT>
struct hash
{
    retT operator ()(valT const& val)
    {
        return val;
    }

    static const hash obj;
};

template <typename valT, typename retT>
const hash<valT, retT> hash<valT, retT>::obj;

NNT_END_NS
NNT_END_HEADER_CXX

# endif
