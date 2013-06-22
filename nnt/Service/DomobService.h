
# ifndef __NNT_SERVICE_DOMOBSERVICE_4EFA737C08B24B8D8FAC7CD038C4A7E0_H_INCLUDED
# define __NNT_SERVICE_DOMOBSERVICE_4EFA737C08B24B8D8FAC7CD038C4A7E0_H_INCLUDED

# import "UIView+NNT.h"
# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(DMAdView);

@interface DomobServiceView : NNTUIView {
    
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

NNTDECL_PRIVATE_HEAD(DomobServiceController);

@interface DomobServiceController : NNTUIViewController
<UIViewControllerRotation>
{
    
    NSString* _appid;
    
    NNTDECL_PRIVATE(DomobServiceController);
}

@property (nonatomic, copy) NSString* appid;

@end

_CXXCONTROLLER_DECL(DomobServiceController);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(ad)

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

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
