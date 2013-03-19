
# ifndef __NNT_UIKIT_ACTIVITYINDICATOR_BAR_EE909A3D33994A8E89EC103E4748019A_H_INCLUDED
# define __NNT_UIKIT_ACTIVITYINDICATOR_BAR_EE909A3D33994A8E89EC103E4748019A_H_INCLUDED

# import "UIView+NNT.h"
# import "UIActivityIndicatorView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UIActivityIndicatorBar);

@interface UIActivityIndicatorBar : NNTUIView {
    
    NNTDECL_PRIVATE(UIActivityIndicatorBar);
}

- (void)startAnimating;
- (void)stopAnimating;

@end

# ifdef NNT_CXX

_CXXVIEW_DECL(UIActivityIndicatorBar);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(activity)

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

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
