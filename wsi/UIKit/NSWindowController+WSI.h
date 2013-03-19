
# ifndef __WSI_UIKIT_NSWINDOWCONTROLLER_D136458CA3364439944BBF6B5BFF5FCC_H_INCLUDED
# define __WSI_UIKIT_NSWINDOWCONTROLLER_D136458CA3364439944BBF6B5BFF5FCC_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSINSViewController);

@interface WSINSWindowControllerBase : NSWindowController {    
    
    //! content view controller.
    WSINSViewController* contentViewController;
    
    WSIOBJECT_DECL;
    
    @private
    NSWindow* __window;
}

WSIOBJECT_PROP;

@property (nonatomic, retain) WSINSViewController* contentViewController;

//! other.
- (void)windowIsLoading;

@end

@interface WSINSWindowController : WSINSWindowControllerBase

@end

WSI_END_HEADER_OBJC

# endif

# endif