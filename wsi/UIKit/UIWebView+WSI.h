
# ifndef __WSI_UIKIT_WEBVIEW_61152C4AE05A4CDD81DBFCC04A1D8967_H_INCLUDED
# define __WSI_UIKIT_WEBVIEW_61152C4AE05A4CDD81DBFCC04A1D8967_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface UIWebView (WSI)

//! load html in local domain.
- (void)loadHTMLStringLocal:(NSString *)string;

//! load html in remote domain.
- (void)loadHTMLStringRemote:(NSString *)string;

@end

enum {
    UIWebViewFilterTypeStartLoad,
    UIWebViewFilterTypeError,
    UIWebViewFilterTypeLoaded,
};

typedef uint UIWebViewFilterType;

@interface UIWebViewFilter : NSObject {
    //! filter, in regex.
    NSString* filter;
    
    //! singal. default same to filter.
    signal_t signal;
    
    //! should start load, default is YES.
    BOOL shouldStartLoad;
    
    //! target object.
    NSObject* target;
}

@property (nonatomic, readonly, copy) NSString* filter;
@property (nonatomic, readonly, copy) signal_t signal;
@property (nonatomic, assign) BOOL shouldStartLoad;
@property (nonatomic, readonly, assign) NSObject* target;

//! init filter.
- (id)initWithFilter:(NSString*)filter signal:(signal_t)signal;

@end

@interface WSIUIWebView : WSIUIView <UIWebViewDelegate> {    
    //! additional javascript while 
    NSMutableArray* additionalJavascript;
    
    //! block link, default is NO.
    BOOL blockLink;
    
    @protected
    
    //! webview.
    UIWebView* _webView;
    
    // other.
    BOOL _isEnableCallback;
    
    @private
    NSMutableArray* _filtersStartLoad;
    NSMutableArray* _filtersError;
    NSMutableArray* _filtersLoaded;
}

//! additional javascript.
@property (nonatomic, retain) NSMutableArray* additionalJavascript;

//! content.
@property (nonatomic, readonly) NSString* content;

//! other.
@property (nonatomic, assign) BOOL blockLink;

//! load html string.
- (void)loadHTMLStringLocal:(NSString *)string;

//! load jquery support. default is NO.
- (void)enableJQuery;

//! enable callback support. default is NO.
- (void)enableCallback;

//! register filter.
- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal target:(NSObject*)target type:(UIWebViewFilterType)type;
- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal type:(UIWebViewFilterType)type;
- (UIWebViewFilter*)registerFilter:(NSString*)filter type:(UIWebViewFilterType)type;

//! redirect.
- (void)loadRequest:(NSURLRequest *)request;
- (void)loadHTMLString:(NSString *)string baseURL:(NSURL *)baseURL;
- (void)loadData:(NSData *)data MIMEType:(NSString *)MIMEType textEncodingName:(NSString *)textEncodingName baseURL:(NSURL *)baseURL;

- (void)reload;
- (void)stopLoading;

- (void)goBack;
- (void)goForward;

- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;

@property (nonatomic) BOOL scalesPageToFit;
@property (nonatomic, readonly) UIScrollView* scrollView;
@property (nonatomic, assign) id<UIWebViewDelegate> delegate;
@property (nonatomic, assign) UIDataDetectorTypes dataDetectorTypes;

@end

WSIDECL_CATEGORY(UIWebView, WSI);

//! signal while finish load.
WSI_EXTERN signal_t kSignalLoadFinish;

//! signal while meet a error.
WSI_EXTERN signal_t kSignalLoadError;

//! signal while link is clicked.
WSI_EXTERN signal_t kSignalLinkClicked;

//! signal while meet a callback.
WSI_EXTERN signal_t kSignalWebCallback;

//! signal while meet a action.
WSI_EXTERN signal_t kSignalWebAction;

# ifdef WSI_CXX

_CXXVIEW_DECL(WSIUIWebView);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class IWebView
: public IView
{
    
};

class WebView
: public View<WebView, 
_CXXVIEW(WSIUIWebView),
IWebView
>
{
    
    typedef  View<WebView, 
    _CXXVIEW(WSIUIWebView),
    IWebView
    > super;
    
public:
    
    WebView()
    {
        PASS;
    }
    
    explicit WebView(UIWebView* view, bool needremove = true)
    : super((view_type*)view, needremove)
    {
        PASS;
    }    
    
    void load(ns::URLRequest const& req)
    {
        [this->_self loadRequest:req];
    }
    
    void load(ns::String const& str)
    {
        [this->_self loadHTMLStringLocal:str];
    }
    
    void load(ns::String const& str, ns::URL const& domain)
    {
        [this->_self loadHTMLString:str baseURL:domain];
    }
    
    void load(ns::URL const& url, ns::URL const& domain)
    {
        load(ns::String(ns::Data(url)), domain);
    }
    
    void disable_link(bool val)
    {
        this->_self.blockLink = val;
    }
    
    void layout_subviews() {}
    
    NSString* run(ns::String const& script)
    {
        return [this->_self stringByEvaluatingJavaScriptFromString:script];
    }
    
    void reload()
    {
        [this->_self reload];
    }
    
    void stop()
    {
        [this->_self stopLoading];
    }
    
    void go_back()
    {
        [this->_self goBack];
    }
    
    void go_forward()
    {
        [this->_self goForward];
    }
    
    void enable_jquery()
    {
        [this->_self enableJQuery];
    }
    
    void enable_callback()
    {
        [this->_self enableCallback];
    }
    
    void set_fit(bool val)
    {
        this->_self.scalesPageToFit = val;
    }
    
    bool is_fit() const
    {
        return this->_self.scalesPageToFit;
    }
    
    void set_detector(UIDataDetectorTypes dt)
    {
        this->_self.dataDetectorTypes = dt;
    }
    
    UIDataDetectorTypes detector_types() const
    {
        return this->_self.dataDetectorTypes;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif