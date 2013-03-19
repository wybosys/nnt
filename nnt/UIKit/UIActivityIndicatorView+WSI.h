
# ifndef __WSI_UIKIT_ACTIVITYINDICATORVIEW_E434FD59E15348F8A9DE512446B14E23_H_INCLUDED
# define __WSI_UIKIT_ACTIVITYINDICATORVIEW_E434FD59E15348F8A9DE512446B14E23_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCAActivityIndicator);

@interface WSIUIActivityIndicatorView : WSIUIView {
    
    //! show percent ring. default is NO.
    BOOL showProgressRing;
    
    //! activity indicator. alloc while used. default is nil.
    WCAActivityIndicator* indicatorActivity;
    
    //! progress value.
    real progressValue;
    
    //! progress max.
    real progressMax;
    
    //! activity.
    UIActivityIndicatorView* activityView;
}

@property (nonatomic, assign) real progressValue, progressMax;
@property (nonatomic, assign) BOOL showProgressRing;
@property (nonatomic, retain) WCAActivityIndicator* indicatorActivity;
@property (nonatomic, readonly) UIActivityIndicatorView* activityView;

- (id)initWithFrame:(CGRect)frame;
- (id)initWithFrame:(CGRect)frame activityIndicatorStyle:(UIActivityIndicatorViewStyle)style;
- (id)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style;

- (void)startAnimating;
- (void)stopAnimating;

@end

# ifdef WSI_CXX

_CXXVIEW_DECL(WSIUIActivityIndicatorView);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(activity)

class IIndicator
: public IView
{
public:
    
    virtual void start() = 0;
    virtual void stop() = 0;
    
};

class Ring
: public View<Ring, _CXXVIEW(WSIUIActivityIndicatorView), IIndicator>
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

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif