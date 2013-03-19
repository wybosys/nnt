
# ifndef __NNT_UIKIT_UIDESKTOP_EBB4619514D14923B7C9ADA1BE96F3C9_H_INCLUDED
# define __NNT_UIKIT_UIDESKTOP_EBB4619514D14923B7C9ADA1BE96F3C9_H_INCLUDED

# import "UIWindow+NNT.h"
# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(QzEffect);

@interface NNTUIDesktop : NNTUIView {
    
    //! content frame.
    CGRect _contentFrame;
    CGRect _preferredContentFrame;
    
    //! enable auto close. default is NO. animated default is YES.
    BOOL _enableAutoClose, _enableAutoCloseAnimated;
    
    //! show effect, quit effect.
    QzEffect *_effectShow, *_effectClose;
    
}

@property (nonatomic, readonly) CGRect contentFrame;
@property (nonatomic, assign) CGRect preferredContentFrame;
@property (nonatomic, assign) BOOL enableAutoClose, enableAutoCloseAnimated;
@property (nonatomic, retain) QzEffect *effectShow, *effectClose;

+ (NNTUIDesktop*)desktop;

//! show desktop with animated.
- (void)show:(BOOL)animated;

//! show desktop.
- (void)show;

//! close desktop with animated.
- (void)close:(BOOL)animated;

//! close desktop.
- (void)close;

//! hit test content.
- (BOOL)hitTestInContent:(CGPoint)pt;

//! content views.
- (NSArray*)contentViews;

@end

NNT_EXTERN signal_t kSignalClosed;
NNT_EXTERN signal_t kSignalShown;

# ifdef NNT_CXX

_CXXVIEW_DECL(NNTUIDesktop);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class IDesktop
: public IView
{
public:
    
    virtual ns::Array contents() const = 0;
    
};

class Desktop
: public View<Desktop, _CXXVIEW(NNTUIDesktop), IDesktop>
{
public:
    
    Desktop()
    {
        PASS;
    }
    
    ~Desktop()
    {
        PASS;
    }
        
    void show()
    {
        [this->_self show];
    }
    
    void show(bool animated)
    {
        [this->_self show:animated];
    }
    
    void close()
    {
        [this->_self close];
    }
    
    void close(bool animated)
    {
        [this->_self close:animated];
    }
    
    virtual ns::Array contents() const
    {
        return this->_self.subviews;
    }
    
    void layout_subviews()
    {
        PASS;
    }
    
    void set_autoclose(bool val, bool animated = ui::animate)
    {
        this->_self.enableAutoClose = val;
        this->_self.enableAutoCloseAnimated = animated;
    }
    
    bool autoclose() const
    {
        return this->_self.enableAutoClose;
    }
    
    template <typename effT>
    void set_close(effT const& eff)
    {
        ntl::const_pointer<effT> ptr(eff);
        this->_self.effectClose = *ptr;
    }
    
    template <typename effT>
    void set_show(effT const& eff)
    {
        ntl::const_pointer<effT> ptr(eff);
        this->_self.effectShow = *ptr;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
