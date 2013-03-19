
# ifndef __WSI_UIKIT_ACTIVITYINDICATOR_WAVE_1E7A00621D2647F490F10B72B2283131_H_INCLUDED
# define __WSI_UIKIT_ACTIVITYINDICATOR_WAVE_1E7A00621D2647F490F10B72B2283131_H_INCLUDED

# import "UIActivityIndicatorView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIActivityIndicatorWave);

@interface UIActivityIndicatorWave : WSIUIView {
    WSIDECL_PRIVATE(UIActivityIndicatorWave);
}

- (void)startAnimating;
- (void)stopAnimating;

@end

# ifdef WSI_CXX

_CXXVIEW_DECL(UIActivityIndicatorWave);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(activity)

class Wave
: public View<Wave, _CXXVIEW(UIActivityIndicatorWave), IIndicator>
{
public:
    
    Wave()
    {
        PASS;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
    virtual void start()
    {
        [this->_self startAnimating];
    }
    
    virtual void stop()
    {
        [this->_self stopAnimating];
    }
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
