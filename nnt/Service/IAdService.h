
# ifndef __WSI_SERVICE_IAD_6064499B0ADF4310AC3285C7FCB1FFE2_H_INCLUDED
# define __WSI_SERVICE_IAD_6064499B0ADF4310AC3285C7FCB1FFE2_H_INCLUDED

# import "UIView+WSI.h"
# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(ADBannerView);

@interface IAdServiceView : WSIUIView {
    ADBannerView* _banner;
}

@property (nonatomic, readonly) ADBannerView* banner;

@end

_CXXVIEW_DECL(IAdServiceView);

WSIDECL_PRIVATE_HEAD(IAdServiceController);

@interface IAdServiceController : WSIUIViewController
<UIViewControllerRotation>
{
    WSIDECL_PRIVATE(IAdServiceController);
}

@end

_CXXCONTROLLER_DECL(IAdServiceController);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(ad)

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

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
