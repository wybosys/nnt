
# ifndef __WSI_BOOST_E946138AFCE74F1B99B00D5A38672EC2_H_INCLUDED
# define __WSI_BOOST_E946138AFCE74F1B99B00D5A38672EC2_H_INCLUDED

# ifdef none
#   undef none
# endif

# ifdef is
#   undef is
# endif

# ifdef if_
#   undef if_
# endif

# ifdef cons
#   undef cons
# endif

# ifdef nil
#   undef nil
# endif

# ifdef true_
#   undef true_
# endif

# ifdef false_
#   undef false_
# endif

# ifdef else_
#   undef else_
# endif

# ifdef then_
#   undef then_
# endif

# ifdef while_
#   undef while_
# endif

# ifndef BOOST_EXCEPTION_DISABLE
#   define BOOST_EXCEPTION_DISABLE 1
# endif

# if defined(WSI_CC_GCC) || defined(WSI_CC_CLANG) || defined(WSI_CC_LLVM)
#   pragma GCC diagnostic ignored "-Wconversion"
#   pragma GCC diagnostic ignored "-Wparentheses"
# endif

# endif