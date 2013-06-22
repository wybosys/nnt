 
# ifndef __NNT_UIKIT_CHINAMAP_CDE291C70E8B45169B1401908088F011_H_INCLUDED
# define __NNT_UIKIT_CHINAMAP_CDE291C70E8B45169B1401908088F011_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIChinaMapController : NNTUIViewController

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_OBJC

_CXXCONTROLLER_DECL(UIChinaMapController);

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class ChinaMapController
: public SimpleController<ChinaMapController, 
_CXXCONTROLLER(UIChinaMapController),
NNTUIView
>
{
public:
    
    ChinaMapController()
    {
        PASS;
    }

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
