
# ifndef __WSI_UIKIT_ACTIVITYINDICATOR_BAR_EE909A3D33994A8E89EC103E4748019A_H_INCLUDED
# define __WSI_UIKIT_ACTIVITYINDICATOR_BAR_EE909A3D33994A8E89EC103E4748019A_H_INCLUDED

# import "UIView+WSI.h"
# import "UIActivityIndicatorView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIActivityIndicatorBar);

@interface UIActivityIndicatorBar : WSIUIView {
    
    WSIDECL_PRIVATE(UIActivityIndicatorBar);
}

- (void)startAnimating;
- (void)stopAnimating;

@end

# ifdef WSI_CXX

_CXXVIEW_DECL(UIActivityIndicatorBar);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(activity)

class Bar
: public View<Bar, _CXXVIEW(UIActivityIndicatorBar), IIndicator>
{
public:
    
    Bar()
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
