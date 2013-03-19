
# ifndef __NNT_UIKIT_NSWINDOWCONTROLLER_D136458CA3364439944BBF6B5BFF5FCC_H_INCLUDED
# define __NNT_UIKIT_NSWINDOWCONTROLLER_D136458CA3364439944BBF6B5BFF5FCC_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTNSViewController);

@interface NNTNSWindowControllerBase : NSWindowController {    
    
    //! content view controller.
    NNTNSViewController* contentViewController;
    
    NNTOBJECT_DECL;
    
    @private
    NSWindow* __window;
}

NNTOBJECT_PROP;

@property (nonatomic, retain) NNTNSViewController* contentViewController;

//! other.
- (void)windowIsLoading;

@end

@interface NNTNSWindowController : NNTNSWindowControllerBase

@end

NNT_END_HEADER_OBJC

# endif

# endif