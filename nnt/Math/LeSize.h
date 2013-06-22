
# ifndef __NNTMATH_SIZE_38D622A00CFB4338B8BFBE6C6D572EA4_H_INCLUDED
# define __NNTMATH_SIZE_38D622A00CFB4338B8BFBE6C6D572EA4_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

template <typename valT, uint dim>
class Size
{
public:
    
    typedef valT value_type;
 
    static const Size<valT, dim> Zero;
};

template <typename valT, uint dim>
const Size<valT, dim> Size<valT, dim>::Zero = Size<valT, dim>();

template <typename valT>
class Size <valT, 1>
: public Size <valT, 0>
{
    typedef Size <valT, 0> super;
    
public:
    
    typedef typename super::value_type value_type;
    
    Size(value_type const& _w = 0)
    : width(_w)
    {
        PASS;
    }
    
    value_type width;
  
    static const Size<valT, 1> Zero;
};

template <typename valT>
const Size<valT, 1> Size<valT, 1>::Zero = Size<valT, 1>();

template <typename valT>
class Size <valT, 2>
: public Size <valT, 1>
{
    typedef Size <valT, 1> super;
    
public:
    
    typedef typename super::value_type value_type;
    
    Size(value_type const& _w = 0, value_type const& _h = 0)
    : super(_w), height(_h)
    {
        PASS;
    }
    
    value_type height;
    
    static const Size<valT, 2> Zero;
};

template <typename valT>
const Size<valT, 2> Size<valT, 2>::Zero = Size<valT, 2>();

NNT_END_HEADER_CXX

# endif

# endif
