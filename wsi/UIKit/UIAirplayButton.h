
# ifndef __WSIUI_AIRPLAYBUTTON_DA0A8D73B8844FCD88D389DC3B571D98_H_INCLUDED
# define __WSIUI_AIRPLAYBUTTON_DA0A8D73B8844FCD88D389DC3B571D98_H_INCLUDED

# import "UIControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(MPVolumeView);

@interface UIAirplayButton : WSIUIControl {
    
    MPVolumeView* _volume;
    
}

+ (BOOL)IsSupported;

@end

_CXXCONTROL_DECL(UIAirplayButton);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
