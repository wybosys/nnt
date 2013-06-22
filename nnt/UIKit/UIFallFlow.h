
# ifndef __NNT_UIKIT_FALLFLOW_86AFF3BA7DA6422BB988D39F966866E4_H_INCLUDED
# define __NNT_UIKIT_FALLFLOW_86AFF3BA7DA6422BB988D39F966866E4_H_INCLUDED

# import "UIControl+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIFallFlow : NNTUIView

@end

_CXXVIEW_DECL(UIFallFlow);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class FallFlow
: public Control<FallFlow, _CXXVIEW(UIFallFlow)>
{
    typedef Control<FallFlow, _CXXVIEW(UIFallFlow)> super;
    
public:
    
    FallFlow()
    {
        PASS;
    }
    
    explicit FallFlow(control_type* type, bool needremove = true)
    : super(type, needremove)
    {
        PASS;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
