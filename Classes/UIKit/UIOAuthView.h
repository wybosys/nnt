
# ifndef __NNT_UIKIT_OAUTHVIEW_5ED8F98ADED541488D576F184D86BEF5_H_INCLUDED
# define __NNT_UIKIT_OAUTHVIEW_5ED8F98ADED541488D576F184D86BEF5_H_INCLUDED

# import "UIView+NNT.h"
# import "UIPopupDialog.h"
# import "UIWebView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UIOAuthView);

@interface UIOAuthContent : NNTUIView {
    
    NNTUILabel* _title;
    NNTUIWebView* _web;
    
    @public
    UIOAuthView* parent;
    
    @private
    NNTUIView* _back;
}

@property (nonatomic, readonly) NNTUILabel* title;
@property (nonatomic, readonly) NNTUIWebView* web;

@end

@interface UIOAuthView : UIPopupDialog {
    UIOAuthContent* _authContent;
}

@property (nonatomic, readonly) UIOAuthContent* authContent;
@property (nonatomic, readonly) NNTUIWebView* web;
@property (nonatomic, readonly) NNTUILabel* title;

- (void)loadRequest:(NSURLRequest *)request;
- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;

//! register filter.
- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal target:(NSObject*)target type:(UIWebViewFilterType)type;
- (UIWebViewFilter*)registerFilter:(NSString*)filter signal:(signal_t)signal type:(UIWebViewFilterType)type;
- (UIWebViewFilter*)registerFilter:(NSString*)filter type:(UIWebViewFilterType)type;

@end

NNT_EXTERN signal_t kSignalLoadFinish;
NNT_EXTERN signal_t kSignalLoadError;

NNT_END_HEADER_OBJC

# endif