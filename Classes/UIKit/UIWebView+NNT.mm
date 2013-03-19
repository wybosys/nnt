
# import "Core.h"
# import "UIWebView+NNT.h"
# import "../3rd/jquery.h"

NNT_BEGIN_OBJC

signal_t kSignalLoadFinish = @"::nnt::ui::load::finish";
signal_t kSignalLoadError = @"::nnt::ui::load::error";
signal_t kSignalLinkClicked = @"::nnt::ui::link::clicked";
signal_t kSignalWebCallback = @"::nnt::ui::web::callback";
signal_t kSignalWebAction = @"::nnt::ui::web::action";

@implementation UIWebView (NNT)

- (void)loadHTMLStringLocal:(NSString *)string {
    [self loadHTMLString:string baseURL:[NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]]];
}

- (void)loadHTMLStringRemote:(NSString *)string {
    [self loadHTMLString:string baseURL:nil];
}

@end

@interface UIWebViewFilter ()

@property (nonatomic, assign) NSObject* target;

@end

@implementation UIWebViewFilter

@synthesize filter, signal, shouldStartLoad, target;

- (id)initWithFilter:(NSString *)__filter signal:(NSString *)__signal {
    self = [super init];
    
    filter = [__filter copy];
    signal = [(__signal ? __signal : __filter) copy];
    self.shouldStartLoad = YES;
    
    return self;
}

- (void)dealloc {
    zero_release(filter);
    zero_release(signal);
    
    [super dealloc];
}

@end

@implementation NNTUIWebView

@synthesize additionalJavascript;
@dynamic content;
@synthesize blockLink;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _webView = [[UIWebView alloc] initWithZero];
    _webView.delegate = self;
    [self addSubview:_webView];
    safe_release(_webView);
    
    blockLink = NO;
    _isEnableCallback = NO;
    
    return self;
}

- (void)dealloc {
    zero_release(additionalJavascript);
    zero_release(_filtersStartLoad);
    zero_release(_filtersError);
    zero_release(_filtersLoaded);
    
    _webView.delegate = nil;
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (NSString*)content {
    return [self stringByEvaluatingJavaScriptFromString:@"document.body.innerHTML"];
}

- (void)layoutSubviews {
    _webView.frame = self.bounds;
}

- (void)loadHTMLStringLocal:(NSString *)string {
    [self loadHTMLString:string baseURL:[NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]]];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalLoadFinish)
NNTEVENT_SIGNAL(kSignalLoadError)
NNTEVENT_SIGNAL(kSignalLinkClicked)
NNTEVENT_SIGNAL(kSignalWebCallback)
NNTEVENT_SIGNAL(kSignalWebAction)
NNTEVENT_END

- (NSMutableArray*)additionalJavascript {
    NNT_SYNCHRONIZED(self)
    if (additionalJavascript == nil) {
        additionalJavascript = [[NSMutableArray alloc] initWithCapacity:4];
    }
    NNT_SYNCHRONIZED_END
    return additionalJavascript;
}

- (void)enableJQuery {
    [self.additionalJavascript addObject:jquery_str];
}

- (void)enableCallback {
    static NSString* jsnnt_cb = @"var nnt = new function(){this.action = function(name){ window.location = 'nnt:///ui/html/action/' + name;};return this;}";

    _isEnableCallback = YES;
    [self.additionalJavascript addObject:jsnnt_cb];
    
    // register callback.
    UIWebViewFilter* filter = [self registerFilter:@"nnt:///ui/html/action/\\S+" signal:kSignalWebCallback target:self type:UIWebViewFilterTypeStartLoad];
    filter.shouldStartLoad = NO;
    [self connect:kSignalWebCallback sel:@selector(__act_callback:)];
}

- (void)__act_callback:(NNTEventObj*)evt {
    NSString* full = (NSString*)evt.result;
    NSArray * res = [full captureComponentsMatchedByRegex:@"nnt:///ui/html/action/(\\S+)"];
    if (res) {
        NSString* act = [res objectAtIndex:1];
        [self emit:kSignalWebAction result:act];
    }
}

- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal target:(NSObject*)target type:(UIWebViewFilterType)type {
    UIWebViewFilter* obj = [[UIWebViewFilter alloc] initWithFilter:filter  signal:signal];
    
    switch (type) {
        case UIWebViewFilterTypeStartLoad: {
            if (_filtersStartLoad == nil)
                _filtersStartLoad = [[NSMutableArray alloc] initWithCapacity:4];
            [_filtersStartLoad addObject:obj];
        } break;
        case UIWebViewFilterTypeError: {
            if (_filtersError == nil)
                _filtersError = [[NSMutableArray alloc] initWithCapacity:4];
            [_filtersError addObject:obj];
        } break;
        case UIWebViewFilterTypeLoaded: {
            if (_filtersLoaded == nil)
                _filtersLoaded = [[NSMutableArray alloc] initWithCapacity:4];
            [_filtersLoaded addObject:obj];
        } break;
    }   
    
    if ([obj retainCount] > 1) {
        if ([target hasSignal:obj.signal] == NO) {            
            [target register_signal:obj.signal];
        }
        
        obj.target = target;
    }
    
    safe_release(obj);                
    return obj;
}

- (UIWebViewFilter*)registerFilter:(NSString *)filter signal:(signal_t)signal type:(UIWebViewFilterType)type {
    return [self registerFilter:filter signal:signal target:self type:type];
}

- (UIWebViewFilter*)registerFilter:(NSString*)filter type:(UIWebViewFilterType)type {
    return [self registerFilter:filter signal:nil type:type];
}

# pragma mark delegate.

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
    NSString* url = [request.URL absoluteString];
    trace_fmt(@"load: %@.", url);
    
    BOOL ret = YES;
    // use filter.
    for (UIWebViewFilter* filter in _filtersStartLoad) {
        if ([url matchedByRegex:filter.filter full:NO]) {
            [filter.target emit:filter.signal result:url];
            ret &= filter.shouldStartLoad;
        }
    }
    
    // get other process.
    switch (navigationType) {
        case UIWebViewNavigationTypeLinkClicked: {
            [self emit:kSignalLinkClicked result:request.URL];
            ret = !self.blockLink;
        } break;
        case UIWebViewNavigationTypeFormSubmitted:
        case UIWebViewNavigationTypeBackForward:
        case UIWebViewNavigationTypeReload:
        case UIWebViewNavigationTypeFormResubmitted:
        case UIWebViewNavigationTypeOther: {
            PASS;
        } break;
    }
    
    return ret;
}

- (void)webViewDidStartLoad:(UIWebView *)webView {
    PASS;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {
    if (additionalJavascript) {
# ifdef NNT_DEBUG
        for (NSString* each in additionalJavascript) {
            NSString* result = [self stringByEvaluatingJavaScriptFromString:each];
            trace_msg(result);
        }
# else
        for (NSString* each in additionalJavascript) {
            [self stringByEvaluatingJavaScriptFromString:each];
        }
# endif
    }
    
    // use filter.
    if ([_filtersLoaded count]) {
        NSString* cnt = self.content;
        for (UIWebViewFilter* filter in _filtersLoaded) {
            if ([cnt matchedByRegex:filter.filter full:NO]) {
                [filter.target emit:filter.signal result:cnt];
            }
        }
    }
    
    // envent
    [self emit:kSignalLoadFinish];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
    if (error.code == 101) {
        NSString* failing = [error.userInfo valueForKey:@"NSErrorFailingURLStringKey" null:nil];        
        [self emit:kSignalLoadError result:failing];
        
        // use filter.
        for (UIWebViewFilter* filter in _filtersError) {
            if ([failing matchedByRegex:filter.filter full:NO]) {
                [filter.target emit:filter.signal result:failing];
            }
        }
    }
}

# pragma mark redirect.

- (void)loadRequest:(NSURLRequest *)request {
    [_webView loadRequest:request];
}

- (void)loadHTMLString:(NSString *)string baseURL:(NSURL *)baseURL {
    [_webView loadHTMLString:string baseURL:baseURL];
}

- (void)loadData:(NSData *)data MIMEType:(NSString *)MIMEType textEncodingName:(NSString *)textEncodingName baseURL:(NSURL *)baseURL {
    [_webView loadData:data MIMEType:MIMEType textEncodingName:textEncodingName baseURL:baseURL];
}

- (void)reload {
    [_webView reload];
}

- (void)stopLoading {
    [_webView stopLoading];
}

- (void)goBack {
    [_webView goBack];
}

- (void)goForward {
    [_webView goForward];
}

- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script {
    return [_webView stringByEvaluatingJavaScriptFromString:script];
}

@dynamic scalesPageToFit, delegate;
@dynamic scrollView;
@dynamic dataDetectorTypes;

- (void)setScalesPageToFit:(BOOL)val {
    _webView.scalesPageToFit = val;
}

- (BOOL)scalesPageToFit {
    return _webView.scalesPageToFit;
}

- (void)setDelegate:(id<UIWebViewDelegate>)obj {
    _webView.delegate = obj;
}

- (id<UIWebViewDelegate>)delegate {
    return _webView.delegate;
}

- (UIScrollView*)scrollView {
    if ([_webView respondsToSelector:@selector(scrollView)])
        return [_webView performSelector:@selector(scrollView)];
    return nil;
}

- (void)setDataDetectorTypes:(UIDataDetectorTypes)type {
    _webView.dataDetectorTypes = type;
}

- (UIDataDetectorTypes)dataDetectorTypes {
    return _webView.dataDetectorTypes;
}

@end

NNTIMPL_CATEGORY(UIWebView, NNT);

_CXXVIEW_IMPL_BEGIN(NNTUIWebView)

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
    BOOL ret = [super webView:webView shouldStartLoadWithRequest:request navigationType:navigationType];
    return ret;
}

_CXXVIEW_IMPL_END

NNT_END_OBJC
