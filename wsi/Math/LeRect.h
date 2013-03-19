
# ifndef __WSIMATH_RECT_3C9DDCE11A7945C1847C65404F42C911_H_INCLUDED
# define __WSIMATH_RECT_3C9DDCE11A7945C1847C65404F42C911_H_INCLUDED

# include "LePoint.h"
# include "LeSize.h"

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

template <typename valT, int dim,
typename pointT = Point<valT, dim>,
typename sizeT = Size<valT, dim>
>
class Rect
{
public:
    
    typedef valT value_type;
    typedef pointT point_type;
    typedef sizeT size_type;
    
    Rect(point_type const& _or = point_type::Zero,
         size_type const& _sz = size_type::Zero)
    : origin(_or), size(_sz)
    {
        PASS;
    }
  
    point_type origin;
    size_type size;
    
};

WSI_END_HEADER_CXX

# endif

# endif
