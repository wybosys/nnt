
# ifndef __NNT_SERVICE_ADMOB_5B2E9E51E9984F378A22D5D4EC7DE13C_H_INCLUDED
# define __NNT_SERVICE_ADMOB_5B2E9E51E9984F378A22D5D4EC7DE13C_H_INCLUDED

# import "UIView+NNT.h"
# import "UIViewController+NNT.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(GADBannerView);

@interface AdmobServiceView  : NNTUIView {
    GADBannerView* _banner;
}

@property (nonatomic, readonly) GADBannerView* banner;

@end

_CXXVIEW_DECL(AdmobServiceView);

NNTDECL_PRIVATE_HEAD(AdmobServiceController);

@interface AdmobServiceController : NNTUIViewController
<UIViewControllerRotation>
{
    NSString* _appid;
    
    NNTDECL_PRIVATE(AdmobServiceController);
}

@property (nonatomic, copy) NSString* appid;

@end

_CXXCONTROLLER_DECL(AdmobServiceController);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(ad)

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

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif
