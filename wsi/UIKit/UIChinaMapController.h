 
# ifndef __WSI_UIKIT_CHINAMAP_CDE291C70E8B45169B1401908088F011_H_INCLUDED
# define __WSI_UIKIT_CHINAMAP_CDE291C70E8B45169B1401908088F011_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIChinaMapController : WSIUIViewController

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_OBJC

_CXXCONTROLLER_DECL(UIChinaMapController);

WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class ChinaMapController
: public SimpleController<ChinaMapController, 
_CXXCONTROLLER(UIChinaMapController),
WSIUIView
>
{
public:
    
    ChinaMapController()
    {
        PASS;
    }

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
