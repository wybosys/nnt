
# import "Core.h"
# import "iAdService.h"
# import <iAd/iAd.h>
# import "App.h"

WSI_BEGIN_OBJC

@implementation IAdServiceView

@synthesize banner = _banner;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.layer.masksToBounds = YES;
    self.backgroundColor = [UIColor whiteColor];
    
    _banner = [[ADBannerView alloc] initWithZero];
    [self addSubview:_banner];
    safe_release(_banner);
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    _banner.frame = self.bounds;
}

@end

WSIDECL_PRIVATE_BEGIN(IAdServiceController, NSObject)
<ADBannerViewDelegate>

WSIDECL_PRIVATE_IMPL(IAdServiceController)

# pragma mark banner delegate

- (void)bannerViewWillLoadAd:(ADBannerView *)banner {
    
}

- (void)bannerViewDidLoadAd:(ADBannerView *)banner {
    
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error {
    
}

- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave {
    return YES;
}

- (void)bannerViewActionDidFinish:(ADBannerView *)banner {
    
}

WSIDECL_PRIVATE_END

@implementation IAdServiceController

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(IAdServiceController);    
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)loadView {
    IAdServiceView* view = [[IAdServiceView alloc] initWithZero];
    self.view = view;
    safe_release(view);
    
    view.banner.delegate = d_ptr;
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewController:(WSIUIViewController*)ctlr orientation:(UIInterfaceOrientation)orientation {
    IAdServiceView* view = (IAdServiceView*)self.view;
    if (UIInterfaceOrientationIsLandscape(orientation))
        view.banner.currentContentSizeIdentifier = ADBannerContentSizeIdentifierLandscape;
    else
        view.banner.currentContentSizeIdentifier = ADBannerContentSizeIdentifierPortrait;
}

@end

_CXXVIEW_IMPL(IAdServiceView);
_CXXCONTROLLER_IMPL(IAdServiceController);

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(ad)

iAdView::iAdView()
{
    
}

iAdView::iAdView(id obj, bool removed)
: super(obj, removed)
{
    
}

iAdView::~iAdView()
{
    
}

void iAdView::layout_subviews()
{
    
}

iAdController::iAdController()
{
    
}

iAdController::~iAdController()
{
    
}

void iAdController::view_loaded()
{
    
}

WSI_END_NS
WSI_END_NS
WSI_END_CXX
