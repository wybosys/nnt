
# ifndef __NNT_UIKIT_ACTIVITYINDICATOR_WAVE_1E7A00621D2647F490F10B72B2283131_H_INCLUDED
# define __NNT_UIKIT_ACTIVITYINDICATOR_WAVE_1E7A00621D2647F490F10B72B2283131_H_INCLUDED

# import "UIActivityIndicatorView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UIActivityIndicatorWave);

@interface UIActivityIndicatorWave : NNTUIView {
    NNTDECL_PRIVATE(UIActivityIndicatorWave);
}

- (void)startAnimating;
- (void)stopAnimating;

@end

# ifdef NNT_CXX

_CXXVIEW_DECL(UIActivityIndicatorWave);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(activity)

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

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
