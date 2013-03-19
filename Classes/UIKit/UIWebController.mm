
# import "Core.h"
# import "UIWebController.h"

NNT_BEGIN_OBJC

@implementation UIWebController

@synthesize url;

- (void)dealloc {
    zero_release(url);
    [super dealloc];
}

- (void)loadView {
    NNTUIWebView* view = [[NNTUIWebView alloc] initWithZero];
    self.view = view;
    safe_release(view);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // load url.
    if (url) {
        [self.webView loadRequest:[NSURLRequest requestWithURL:url]];
    }
}

- (NNTUIWebView*)webView {
    return (NNTUIWebView*)self.view;
}

@end

@interface UINaviWebController ()

@property (nonatomic, retain) NNTUINavigationController* webNavigation;
@property (nonatomic, retain) UIWebController* webController;

@end

@interface UINaviWebView : NNTUIView

@property (nonatomic, assign) NNTUINavigationController* navi;

@end

@implementation UINaviWebView

@synthesize navi;

- (void)layoutSubviews {
    navi.view.frame = self.bounds;
}

@end

@implementation UINaviWebController

@synthesize webNavigation, webController;

- (id)init {
    self = [super init];
    
    webController = [[UIWebController alloc] init];
    webNavigation = [[NNTUINavigationController alloc] initWithRootViewController:webController];
    
    return self;
}

- (void)dealloc {
    zero_release(webNavigation);
    zero_release(webController);
    [super dealloc];
}

- (void)loadView {
    UINaviWebView* view = [[UINaviWebView alloc] initWithZero];
    self.view = view;
    safe_release(view);
    
    view.navi = webNavigation;
    [view addSubview:webNavigation.view];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // disable inner open.
    webController.webView.blockLink = YES;
    
    // connect signal.
    [webController.webView connect:kSignalLinkClicked sel:@selector(__act_click_link:) obj:self];
}

- (void)__act_click_link:(NNTEventObj*)evt {
    NSURL* url = (NSURL*)evt.result;
    
    UIWebController* ctlr = [[UIWebController alloc] init];
    ctlr.title = webNavigation.visibleViewController.title;
    ctlr.url = url;
    [webNavigation pushViewController:ctlr animated:YES];
    safe_release(ctlr);
}

@end

NNT_END_OBJC
