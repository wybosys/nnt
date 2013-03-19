
# ifndef __WSI_UIKIT_FALLFLOW_86AFF3BA7DA6422BB988D39F966866E4_H_INCLUDED
# define __WSI_UIKIT_FALLFLOW_86AFF3BA7DA6422BB988D39F966866E4_H_INCLUDED

# import "UIControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIFallFlow : WSIUIView

@end

_CXXVIEW_DECL(UIFallFlow);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
