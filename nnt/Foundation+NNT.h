
# ifndef __NNT_FOUNDATION_39D46F10E5F5418D9885D956E3331BDD_H_INCLUDED
# define __NNT_FOUNDATION_39D46F10E5F5418D9885D956E3331BDD_H_INCLUDED

# include "Core/Core.h"

# ifndef NNT_NOLIB

# ifdef NNT_USER_SPACE

# ifdef NNT_OBJC
#   import "UIKit/UIKit+NNT.h"
# endif

# ifdef NNT_CROSS_PLATFORM
#   include "UIKit/UIKit+Cross.h"
# endif

# endif

# endif

# if !defined(LIBNNT)

#   ifdef NNT_CXX
#     define NNTAPP_BEGIN namespace nntapp {
#     define NNTAPP_END   }
#     define NNTCAPP_BEGIN extern "C" {
#     define NNTCAPP_END }
#   else
#     define NNTAPP_BEGIN
#     define NNTAPP_END
#     define NNTCAPP_BEGIN
#     define NNTCAPP_END
#   endif

# ifdef NNT_OBJC
#   define NNTAPP_BEGIN_OBJC
#   define NNTAPP_END_OBJC
# endif

# ifdef NNT_CXX

NNTAPP_BEGIN

NNT_USINGCXXNAMESPACE;

NNTAPP_END

# endif

# endif

# endif
