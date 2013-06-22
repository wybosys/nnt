
# ifndef __NNTUI_AIRPLAYBUTTON_DA0A8D73B8844FCD88D389DC3B571D98_H_INCLUDED
# define __NNTUI_AIRPLAYBUTTON_DA0A8D73B8844FCD88D389DC3B571D98_H_INCLUDED

# import "UIControl+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(MPVolumeView);

@interface UIAirplayButton : NNTUIControl {
    
    MPVolumeView* _volume;
    
}

+ (BOOL)IsSupported;

@end

_CXXCONTROL_DECL(UIAirplayButton);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class AirplayButton
: public Control<AirplayButton, _CXXCONTROL(UIAirplayButton)>
{
public:
    
    AirplayButton()
    {
        PASS;
    }
    
    ~AirplayButton()
    {
        PASS;
    }
    
    static bool IsSupported()
    {
        return [UIAirplayButton IsSupported];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
