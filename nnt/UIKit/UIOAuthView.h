
# ifndef __WSI_UIKIT_OAUTHVIEW_5ED8F98ADED541488D576F184D86BEF5_H_INCLUDED
# define __WSI_UIKIT_OAUTHVIEW_5ED8F98ADED541488D576F184D86BEF5_H_INCLUDED

# import "UIView+WSI.h"
# import "UIPopupDialog.h"
# import "UIWebView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIOAuthView);

@interface UIOAuthContent : WSIUIView {
    
    WSIUILabel* _title;
    WSIUIWebView* _web;
    
    @public
    UIOAuthView* parent;
    
    @private
    WSIUIView* _back;
}

@property (nonatomic, readonly) WSIUILabel* title;
@property (nonatomic, readonly) WSIUIWebView* web;

@end

@interface UIOAuthView : UIPopupDialog {
    UIOAuthContent* _authContent;
}

@property (nonatomic, readonly) UIOAuthContent* authContent;
@property (nonatomic, readonly) WSIUIWebView* web;
@property (nonatomic, readonly) WSIUILabel* title;

- (void)loadRequest:(NSURLRequest *)request;
- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;

//! register filter.
- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal target:(NSObject*)target type:(UIWebViewFilterType)type;
- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal type:(UIWebViewFilterType)type;
- (UIWebViewFilter*)registerFilter:(NSString*)filter type:(UIWebViewFilterType)type;

@end

WSI_EXTERN signal_t kSignalLoadFinish;
WSI_EXTERN signal_t kSignalLoadError;

WSI_END_HEADER_OBJC

# endif