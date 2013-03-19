
# import "WSIFoundation.h"

// core.
# define {Name}_HEADER_BEGIN_OBJC WSI_HEADER_BEGIN_OBJC
# define {Name}_HEADER_END_OBJC   WSI_HEADER_END_OBJC
# define {Name}_BEGIN_OBJC        WSI_BEGIN_OBJC
# define {Name}_END_OBJC          WSI_END_OBJC
# define {Name}_HEADER_BEGIN_CXX  WSI_HEADER_BEGIN_CXX
# define {Name}_HEADER_END_CXX    WSI_HEADER_END_CXX

// uikit.
typedef WSIUIView {Name}UIView;
typedef WSIUIViewController {Name}UIViewController;

// cxx.
# ifdef WSI_CXX
# define {name} wsi
namespace {name} {}
# endif