
# ifndef __WSI_UIKIT_FALLFLOWCONTROLLER_0B98003C80464796B3B4ADED0862F566_H_INCLUDED
# define __WSI_UIKIT_FALLFLOWCONTROLLER_0B98003C80464796B3B4ADED0862F566_H_INCLUDED

# import "UIFallFlow.h"
# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIFallFlowController : WSIUIViewController

@end

_CXXCONTROLLER_DECL(UIFallFlowController);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class FallFlowController
: public SimpleController<FallFlowController, _CXXCONTROLLER(UIFallFlowController),
_CXXVIEW(UIFallFlow), FallFlow
>
{
public:
    
    FallFlowController()
    {
        PASS;
    }
    
    void view_loaded()
    {
        PASS;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
