
# ifndef __WSI_SERVICE_ADMOB_5B2E9E51E9984F378A22D5D4EC7DE13C_H_INCLUDED
# define __WSI_SERVICE_ADMOB_5B2E9E51E9984F378A22D5D4EC7DE13C_H_INCLUDED

# import "UIView+WSI.h"
# import "UIViewController+WSI.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(GADBannerView);

@interface AdmobServiceView  : WSIUIView {
    GADBannerView* _banner;
}

@property (nonatomic, readonly) GADBannerView* banner;

@end

_CXXVIEW_DECL(AdmobServiceView);

WSIDECL_PRIVATE_HEAD(AdmobServiceController);

@interface AdmobServiceController : WSIUIViewController
<UIViewControllerRotation>
{
    NSString* _appid;
    
    WSIDECL_PRIVATE(AdmobServiceController);
}

@property (nonatomic, copy) NSString* appid;

@end

_CXXCONTROLLER_DECL(AdmobServiceController);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(ad)

class AdmobView
: public ui::View<AdmobView, _CXXVIEW(AdmobServiceView)>
{
    
    typedef ui::View<AdmobView, _CXXVIEW(AdmobServiceView)> super;
    
public:
    
    AdmobView();
    AdmobView(id, bool);
    
    void layout_subviews() {}
    
};

class AdmobController
: public ui::SimpleController<AdmobController, _CXXCONTROLLER(AdmobServiceController),
_CXXVIEW(AdmobServiceView), AdmobView>
{
public:
    
    AdmobController();
    
    void set_appid(ns::String const&);
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

# endif
