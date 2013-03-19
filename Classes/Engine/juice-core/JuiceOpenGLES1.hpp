
# ifndef __JUICE_OPENGLES_1_C5E2DB33F84B4C95B955C86A46828204_H_INCLUDED
# define __JUICE_OPENGLES_1_C5E2DB33F84B4C95B955C86A46828204_H_INCLUDED

# include "./JuiceOpenGLPCDriver.hpp"

JUICE_BEGIN

template <typename implT, typename typesT, typename archT>
class _opengles1x_Driver
: public _openglpc_Driver<implT, typesT, archT>
{
    typedef _openglpc_Driver<implT, typesT, archT> super;
    
public:
    
    enum { GLES_VERSION = 1 };
    
    typedef typename super::context_type context_type;
    typedef typename super::vectorcomp_type vectorcomp_type;
    typedef typename super::vertex_type vertex_type;
    typedef typename super::index_type index_type;
    typedef typename super::color_type color_type;
    typedef typename super::colorcomp_type colorcomp_type;
    typedef typename super::matrix_type matrix_type;    
        
};

JUICE_END

# endif