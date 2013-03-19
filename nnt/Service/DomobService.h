
# ifndef __WSI_SERVICE_DOMOBSERVICE_4EFA737C08B24B8D8FAC7CD038C4A7E0_H_INCLUDED
# define __WSI_SERVICE_DOMOBSERVICE_4EFA737C08B24B8D8FAC7CD038C4A7E0_H_INCLUDED

# import "UIView+WSI.h"
# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(DMAdView);

@interface DomobServiceView : WSIUIView {
    
    DMAdView* _banner;
    NSString* _appid;
    CGSize _size;

}

@property (nonatomic, readonly) DMAdView* banner;
@property (nonatomic, copy) NSString* appid;
@property (nonatomic, assign) CGSize size;

- (void)loadAd;

@end

_CXXVIEW_DECL(DomobServiceView);

WSIDECL_PRIVATE_HEAD(DomobServiceController);

@interface DomobServiceController : WSIUIViewController
<UIViewControllerRotation>
{
    
    NSString* _appid;
    
    WSIDECL_PRIVATE(DomobServiceController);
}

@property (nonatomic, copy) NSString* appid;

@end

_CXXCONTROLLER_DECL(DomobServiceController);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(ad)

class DomobView
: public ui::View<DomobView, _CXXVIEW(DomobServiceView)>
{
    
    typedef ui::View<DomobView, _CXXVIEW(DomobServiceView)> super;
    
public:
    
    DomobView();
    DomobView(id, bool);
    void layout_subviews() {}
    
};

class DomobController
: public ui::SimpleController<DomobController, _CXXCONTROLLER(DomobServiceController), _CXXVIEW(DomobServiceView), DomobView>
{
public:
    
    DomobController();
    
    void set_appid(ns::String const&);
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
