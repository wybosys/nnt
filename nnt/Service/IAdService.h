
# ifndef __NNT_SERVICE_IAD_6064499B0ADF4310AC3285C7FCB1FFE2_H_INCLUDED
# define __NNT_SERVICE_IAD_6064499B0ADF4310AC3285C7FCB1FFE2_H_INCLUDED

# import "UIView+NNT.h"
# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(ADBannerView);

@interface IAdServiceView : NNTUIView {
    ADBannerView* _banner;
}

@property (nonatomic, readonly) ADBannerView* banner;

@end

_CXXVIEW_DECL(IAdServiceView);

NNTDECL_PRIVATE_HEAD(IAdServiceController);

@interface IAdServiceController : NNTUIViewController
<UIViewControllerRotation>
{
    NNTDECL_PRIVATE(IAdServiceController);
}

@end

_CXXCONTROLLER_DECL(IAdServiceController);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(ad)

class iAdView
: public ui::View<iAdView, _CXXVIEW(IAdServiceView)>
{
    typedef ui::View<iAdView, _CXXVIEW(IAdServiceView)> super;
    
public:
    
    iAdView();
    iAdView(id, bool);
    ~iAdView();
    
    void layout_subviews();
    
};

class iAdController
: public ui::SimpleController<iAdController, _CXXCONTROLLER(IAdServiceController), _CXXVIEW(IAdServiceView), iAdView>
{
public:
    
    iAdController();
    ~iAdController();
    
    void view_loaded();
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
