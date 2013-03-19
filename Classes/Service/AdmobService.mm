
# import "Core.h"
# import "AdmobService.h"
# import <Admob/GADBannerView.h>
# import "App.h"

WSI_BEGIN_OBJC

# define DEFAULT_PUBLISHERID_IPHONE @"a1512c21815168e"
# define DEFAULT_PUBLISHERID_IPAD @"a1512c3119d6fa1"

WSI_EXTERN bool WSI_DEVICE_ISSIMULATOR;
WSI_EXTERN bool WSI_DEVICE_ISIPHONE;
WSI_EXTERN bool WSI_DEVICE_ISIPAD;

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

WSIDECL_PRIVATE_BEGIN(AdmobServiceController, WSIObject)
<GADBannerViewDelegate>

WSIDECL_PRIVATE_IMPL(AdmobServiceController)

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

WSIDECL_PRIVATE_END

@implementation AdmobServiceController

@synthesize appid = _appid;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(AdmobServiceController);
    
    if (WSI_DEVICE_ISIPHONE)
        self.appid = DEFAULT_PUBLISHERID_IPHONE;
    else
        self.appid = DEFAULT_PUBLISHERID_IPAD;
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    
    WSIDECL_PRIVATE_DEALLOC();
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
    
    view.banner.rootViewController = [WSIApplication shared].rootViewController;
    view.banner.delegate = d_ptr;
    view.banner.adUnitID = _appid;
    
    // load request.
    GADRequest* req = [GADRequest request];
    if (WSI_DEVICE_ISSIMULATOR) {
        req.testDevices = [NSArray arrayWithObject:GAD_SIMULATOR_ID];
    } else {
# ifdef WSI_DEBUG
        req.testDevices = [NSArray arrayWithObjects:@"784136f9b6bab4fe0e003f63a0b34f44", nil];
# endif
    }

    [view.banner loadRequest:req];
}

- (void)viewController:(WSIUIViewController*)ctlr orientation:(UIInterfaceOrientation)orientation {
    AdmobServiceView* view = (AdmobServiceView*)self.view;
    if (UIInterfaceOrientationIsLandscape(orientation))
        view.banner.adSize = kGADAdSizeSmartBannerLandscape;
    else
        view.banner.adSize = kGADAdSizeSmartBannerPortrait;
        
}

@end

_CXXVIEW_IMPL(AdmobServiceView);
_CXXCONTROLLER_IMPL(AdmobServiceController);

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(ad)

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

WSI_END_NS
WSI_END_NS
WSI_END_CXX
