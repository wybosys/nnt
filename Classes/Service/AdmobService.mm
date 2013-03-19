
# import "Core.h"
# import "AdmobService.h"
# import <Admob/GADBannerView.h>
# import "App.h"

NNT_BEGIN_OBJC

# define DEFAULT_PUBLISHERID_IPHONE @"a1512c21815168e"
# define DEFAULT_PUBLISHERID_IPAD @"a1512c3119d6fa1"

NNT_EXTERN bool NNT_DEVICE_ISSIMULATOR;
NNT_EXTERN bool NNT_DEVICE_ISIPHONE;
NNT_EXTERN bool NNT_DEVICE_ISIPAD;

@implementation AdmobServiceView

@synthesize banner = _banner;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.layer.masksToBounds = YES;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (GADBannerView*)banner {
    if (_banner == nil) {
        _banner = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];        
        [self addSubview:_banner];
        safe_release(_banner);
    }
    
    return _banner;
}

- (void)layoutSubviews {
    //_banner.frame = self.bounds;
}

@end

NNTDECL_PRIVATE_BEGIN(AdmobServiceController, NNTObject)
<GADBannerViewDelegate>

NNTDECL_PRIVATE_IMPL(AdmobServiceController)

- (void)adViewDidReceiveAd:(GADBannerView *)view {
    
}

- (void)adView:(GADBannerView *)view
didFailToReceiveAdWithError:(GADRequestError *)error {
    
}

- (void)adViewWillPresentScreen:(GADBannerView *)adView {
    
}

- (void)adViewWillDismissScreen:(GADBannerView *)adView {
    
}

- (void)adViewDidDismissScreen:(GADBannerView *)adView {
    
}

- (void)adViewWillLeaveApplication:(GADBannerView *)adView {
    
}

NNTDECL_PRIVATE_END

@implementation AdmobServiceController

@synthesize appid = _appid;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(AdmobServiceController);
    
    if (NNT_DEVICE_ISIPHONE)
        self.appid = DEFAULT_PUBLISHERID_IPHONE;
    else
        self.appid = DEFAULT_PUBLISHERID_IPAD;
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)loadView {
    AdmobServiceView* view = [[AdmobServiceView alloc] initWithZero];
    self.view = view;
    safe_release(view);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    AdmobServiceView* view = (AdmobServiceView*)self.view;
    
    view.banner.rootViewController = [NNTApplication shared].rootViewController;
    view.banner.delegate = d_ptr;
    view.banner.adUnitID = _appid;
    
    // load request.
    GADRequest* req = [GADRequest request];
    if (NNT_DEVICE_ISSIMULATOR) {
        req.testDevices = [NSArray arrayWithObject:GAD_SIMULATOR_ID];
    } else {
# ifdef NNT_DEBUG
        req.testDevices = [NSArray arrayWithObjects:@"784136f9b6bab4fe0e003f63a0b34f44", nil];
# endif
    }

    [view.banner loadRequest:req];
}

- (void)viewController:(NNTUIViewController*)ctlr orientation:(UIInterfaceOrientation)orientation {
    AdmobServiceView* view = (AdmobServiceView*)self.view;
    if (UIInterfaceOrientationIsLandscape(orientation))
        view.banner.adSize = kGADAdSizeSmartBannerLandscape;
    else
        view.banner.adSize = kGADAdSizeSmartBannerPortrait;
        
}

@end

_CXXVIEW_IMPL(AdmobServiceView);
_CXXCONTROLLER_IMPL(AdmobServiceController);

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(ad)

AdmobView::AdmobView()
{
    
}

AdmobView::AdmobView(id obj, bool remove)
: super(obj, remove)
{
    
}

AdmobController::AdmobController()
{
    
}

void AdmobController::set_appid(ns::String const& str)
{
    this->_self.appid = str;
}

NNT_END_NS
NNT_END_NS
NNT_END_CXX
