
# ifndef __NNT_UIKIT_ACTIVITYINDICATORVIEW_E434FD59E15348F8A9DE512446B14E23_H_INCLUDED
# define __NNT_UIKIT_ACTIVITYINDICATORVIEW_E434FD59E15348F8A9DE512446B14E23_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgActivityIndicator);

@interface NNTUIActivityIndicatorView : NNTUIView {
    
    //! show percent ring. default is NO.
    BOOL showProgressRing;
    
    //! activity indicator. alloc while used. default is nil.
    NgActivityIndicator* indicatorActivity;
    
    //! progress value.
    real progressValue;
    
    //! progress max.
    real progressMax;
    
    //! activity.
    UIActivityIndicatorView* activityView;
}

@property (nonatomic, assign) real progressValue, progressMax;
@property (nonatomic, assign) BOOL showProgressRing;
@property (nonatomic, retain) NgActivityIndicator* indicatorActivity;
@property (nonatomic, readonly) UIActivityIndicatorView* activityView;

- (id)initWithFrame:(CGRect)frame;
- (id)initWithFrame:(CGRect)frame activityIndicatorStyle:(UIActivityIndicatorViewStyle)style;
- (id)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style;

- (void)startAnimating;
- (void)stopAnimating;

@end

# ifdef NNT_CXX

_CXXVIEW_DECL(NNTUIActivityIndicatorView);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(activity)

class IIndicator
: public IView
{
public:
    
    virtual void start() = 0;
    virtual void stop() = 0;
    
};

class Ring
: public View<Ring, _CXXVIEW(NNTUIActivityIndicatorView), IIndicator>
{
public:
    
    Ring()
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