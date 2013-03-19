
# import "Core.h"
# import "iAdService.h"
# import <iAd/iAd.h>
# import "App.h"

NNT_BEGIN_OBJC

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

NNTDECL_PRIVATE_BEGIN(IAdServiceController, NSObject)
<ADBannerViewDelegate>

NNTDECL_PRIVATE_IMPL(IAdServiceController)

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

NNTDECL_PRIVATE_END

@implementation IAdServiceController

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(IAdServiceController);    
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
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

- (void)viewController:(NNTUIViewController*)ctlr orientation:(UIInterfaceOrientation)orientation {
    IAdServiceView* view = (IAdServiceView*)self.view;
    if (UIInterfaceOrientationIsLandscape(orientation))
        view.banner.currentContentSizeIdentifier = ADBannerContentSizeIdentifierLandscape;
    else
        view.banner.currentContentSizeIdentifier = ADBannerContentSizeIdentifierPortrait;
}

@end

_CXXVIEW_IMPL(IAdServiceView);
_CXXCONTROLLER_IMPL(IAdServiceController);

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(ad)

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

NNT_END_NS
NNT_END_NS
NNT_END_CXX
