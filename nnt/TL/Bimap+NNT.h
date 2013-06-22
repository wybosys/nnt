
# ifndef __NNT_WTL_BIMAP_D86F6786F5364E4B82343DF93A1F6243_H_INCLUDED
# define __NNT_WTL_BIMAP_D86F6786F5364E4B82343DF93A1F6243_H_INCLUDED

# ifdef NNT_CXX

# include <boost/bimap.hpp>

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

using ::boost::bimap;

NNT_END_NS
NNT_END_HEADER_CXX

# ifndef isinf
# if defined( __GNUC__ ) && 0 == __FINITE_MATH_ONLY__
#define isinf(x)	\
(	sizeof (x) == sizeof(float )	?	__inline_isinff((float)(x))	\
:	sizeof (x) == sizeof(double)	?	__inline_isinfd((double)(x))	\
:	__inline_isinf ((long double)(x)))
# else
#define isinf(x)	\
(	sizeof (x) == sizeof(float )	?	__isinff((float)(x))	\
:	sizeof (x) == sizeof(double)	?	__isinfd((double)(x))	\
:	__isinf ((long double)(x)))
# endif
# endif

# endif

# endif
