
# ifndef __WSI_FOUNDATION_39D46F10E5F5418D9885D956E3331BDD_H_INCLUDED
# define __WSI_FOUNDATION_39D46F10E5F5418D9885D956E3331BDD_H_INCLUDED

# include "Core/Core.h"

# ifndef WSI_NOLIB

# ifdef WSI_OBJC
#   import "UIKit/UIKit+WSI.h"
# endif

# ifdef WSI_CROSS_PLATFORM
#   include "UIKit/UIKit+Cross.h"
# endif

# endif

# if !defined(LIBWSI)

#   ifdef WSI_CXX
#     define WSIAPP_BEGIN namespace wsiapp {
#     define WSIAPP_END   }
#     define WSICAPP_BEGIN extern "C" {
#     define WSICAPP_END }
#   else
#     define WSIAPP_BEGIN
#     define WSIAPP_END
#     define WSICAPP_BEGIN
#     define WSICAPP_END
#   endif

# ifdef WSI_OBJC
#   define WSIAPP_BEGIN_OBJC
#   define WSIAPP_END_OBJC
# endif

# ifdef WSI_CXX

WSIAPP_BEGIN

WSI_USINGCXXNAMESPACE;

WSIAPP_END

# endif

# endif

# endif
