
# import "Core.h"
# import "DomobService.h"
# import <Domob/DMAdView.h>
# import "App.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

# define DEFAULT_PUBLISHERID @"56OJzX3IuNaWsF8Apk"

NNT_EXTERN bool NNT_DEVICE_ISIPAD;

@implementation DomobServiceView

@synthesize banner = _banner;
@synthesize appid = _appid;
@synthesize size = _size;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.layer.masksToBounds = YES;
    
    return self;
}

- (void)dealloc {
    _banner.delegate = nil;
    
    safe_release(_appid);
    
    [super dealloc];
}

- (void)setAppid:(NSString *)appid {
    if ([appid isEqualToString:_appid])
        return;
    
    if (appid == nil)
        return;
    
    [NSObject refobjCopy:&_appid ref:appid];
    
    [self renew];
}

- (void)setSize:(CGSize)size {
    if (CGSizeEqualToSize(size, _size))
        return;
    
    if (CGSizeEqualToSize(size, CGSizeZero))
        return;
    
    _size = size;
    
    [self renew];
}

- (void)renew {
    if (_appid == nil ||
        CGSizeEqualToSize(_size, CGSizeZero))
        return;
    
    id delegate = _banner.delegate;
    id rootController = _banner.rootViewController;
    
    // renew banner.
    if (_banner) {
        _banner.delegate = nil;
        [_banner removeFromSuperview];
    }
    
    _banner = [[DMAdView alloc] initWithPublisherId:_appid size:_size];
    _banner.delegate = delegate;
    _banner.rootViewController = rootController;
    [self addSubview:_banner];
    safe_release(_banner);
}

- (void)loadAd {
    [_banner loadAd];
}

- (void)layoutSubviews {
    //_banner.frame = self.bounds;
    [_banner moveToCenter:cg::Rect(self.bounds).center()];
}

@end

NNTDECL_PRIVATE_BEGIN(DomobServiceController, NSObject)
<DMAdViewDelegate>

NNTDECL_PRIVATE_IMPL(DomobServiceController)

- (void)dmAdViewSuccessToLoadAd:(DMAdView *)adView {
    
}

- (void)dmAdViewFailToLoadAd:(DMAdView *)adView withError:(NSError *)error {
    
}

- (void)dmWillPresentModalViewFromAd:(DMAdView *)adView {
    
}

- (void)dmDidDismissModalViewFromAd:(DMAdView *)adView {
    
}

- (void)dmApplicationWillEnterBackgroundFromAd:(DMAdView *)adView {
    
}

NNTDECL_PRIVATE_END

@implementation DomobServiceController

@synthesize appid = _appid;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(DomobServiceController);
    
    self.appid = DEFAULT_PUBLISHERID;
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)loadView {
    DomobServiceView* view = [[DomobServiceView alloc] initWithZero];
    self.view = view;
    safe_release(view);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    DomobServiceView* view = (DomobServiceView*)self.view;
    view.appid = _appid;
    view.banner.delegate = d_ptr;
    view.banner.rootViewController = [NNTApplication shared].rootViewController;
    
    [view loadAd];
}

- (void)viewController:(NNTUIViewController*)ctlr orientation:(UIInterfaceOrientation)orientation {
    DomobServiceView* view = (DomobServiceView*)self.view;
    
    if (UIInterfaceOrientationIsLandscape(orientation)) {
        if (NNT_DEVICE_ISIPAD) {
            view.size = DOMOB_AD_SIZE_728x90;
        } else {
            view.size = DOMOB_AD_SIZE_320x50;
        }
    } else {
        if (NNT_DEVICE_ISIPAD) {
            view.size = DOMOB_AD_SIZE_488x80;
        } else {
            view.size = DOMOB_AD_SIZE_320x50;
        }
    }
    
    [view loadAd];
}

@end

_CXXVIEW_IMPL(DomobServiceView);
_CXXCONTROLLER_IMPL(DomobServiceController);

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(ad)

DomobView::DomobView()
{
    
}

DomobView::DomobView(id obj, bool remove)
: super(obj, remove)
{
    
}

DomobController::DomobController()
{
    
}

void DomobController::set_appid(ns::String const& str)
{
    this->_self.appid = str;
}

NNT_END_NS
NNT_END_NS
NNT_END_CXX
