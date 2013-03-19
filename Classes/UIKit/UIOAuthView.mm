
# import "Core.h"
# import "UIOAuthView.h"
# import "NSHttpCache.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

@implementation UIOAuthContent

@synthesize title = _title, web = _web;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    // back.
    _back = [[WSIUIView alloc] initWithZero];
    _back.backgroundColor = [UIColor blackColor];
    //_back.layer.opacity = .4f;
    //_back.layer.cornerRadius = 10;
    //_back.layer.masksToBounds = YES;
    _back.layer.shadowOpacity = 3;
    //_back.layer.borderColor = [UIColor redColor].CGColor;
    //_back.layer.borderWidth = 2;
    
    [self addSubview:_back];
    safe_release(_back);
    
    // title.
    _title = [[WSIUILabel alloc] initWithZero];
    _title.textColor = [UIColor whiteColor];
    [self addSubview:_title];
    safe_release(_title);
    
    // web.
    _web = [[WSIUIWebView alloc] initWithZero];
    //web.scalesPageToFit = YES;
    _web.layer.cornerRadius = 10;
    _web.layer.masksToBounds = YES;
    [self addSubview:_web];
    safe_release(_web);

    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
}

- (void)layoutSubviews {
    CGRectLayoutVBox lyt(self.bounds, 20);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)7;
    
    _title.frame = lyt << lnr;
    _web.frame = lyt << lnr;
    
    // set title.
    real sz = [_title fitableFontSize];
    _title.font = [UIFont italicSystemFontOfSize:sz];
    
    // set background.
    _back.frame = CGRectDeflateCenter(self.bounds, 10, 10);
    
    // move close button.
    if (parent.showClose) {
        CGPoint pt = CGRectRightTop2(_back.frame);
        pt.y += 5;
        [parent.buttonClose moveToCenter:pt];
    }
}

@end

@implementation UIOAuthView

@dynamic web, title;
@synthesize authContent = _authContent;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.padding = CGPaddingMake(0, 0, .05f, .05f);
    
    _authContent = [[UIOAuthContent alloc] initWithFrame:CGRectZero];
    _authContent->parent = self;
    self.content = _authContent;
    safe_release(_authContent);
    
    [self.web connect:kSignalLoadFinish sig:kSignalLoadFinish obj:self];
    [self.web connect:kSignalLoadError sig:kSignalLoadError obj:self];
    
    self.backgroundColor = [UIColor clearColor];
    self.layer.shadowOpacity = 0;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalLoadFinish)
WSIEVENT_SIGNAL(kSignalLoadError)
WSIEVENT_END

- (WSIUIWebView*)web {
    return _authContent.web;
}

- (WSIUILabel*)title {
    return _authContent.title;
}

- (void)loadRequest:(NSURLRequest *)request {
    [NSHttpCache clearAllCookies];
    [NSHttpCache clearAllResponses];
    
    NSMutableURLRequest* mut = [[NSMutableURLRequest alloc] initWithURL:request.URL];
    [mut setCachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData];
    
    [self.web loadRequest:mut];
    
    safe_release(mut);
}

- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script {
    return [self.web stringByEvaluatingJavaScriptFromString:script];
}

- (void)close {
    //web.delegate = nil;
    [super close];
}

- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal target:(NSObject*)target type:(UIWebViewFilterType)type {
    return [self.web registerFilter:filter signal:signal target:target type:type];
}

- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal type:(UIWebViewFilterType)type {
    return [self registerFilter:filter signal:signal target:self type:type];
}

- (UIWebViewFilter*)registerFilter:(NSString*)filter type:(UIWebViewFilterType)type {
    return [self registerFilter:filter signal:nil type:type];
}

@end

WSI_END_OBJC
