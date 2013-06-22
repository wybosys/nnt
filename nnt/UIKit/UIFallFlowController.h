
# ifndef __NNT_UIKIT_FALLFLOWCONTROLLER_0B98003C80464796B3B4ADED0862F566_H_INCLUDED
# define __NNT_UIKIT_FALLFLOWCONTROLLER_0B98003C80464796B3B4ADED0862F566_H_INCLUDED

# import "UIFallFlow.h"
# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIFallFlowController : NNTUIViewController

@end

_CXXCONTROLLER_DECL(UIFallFlowController);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
