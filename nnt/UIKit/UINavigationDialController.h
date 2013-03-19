
# ifndef __WSI_UIKIT_UIDIALNAVIGATIONCONTROLLER_52636679239241AEBC49667F5FA85F75_H_INCLUDED
# define __WSI_UIKIT_UIDIALNAVIGATIONCONTROLLER_52636679239241AEBC49667F5FA85F75_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UINavigationDialController);
WSIDECL_EXTERN_CLASS(UINavigationDialView);

@interface UINavigationDialController : WSIUIViewController {
    
    //! controllers navi by this controller.
    NSArray *itemControllers;
    
    //! selected controller.
    WSIUIViewController *selectedController;
    
    //! dialView.
    UINavigationDialView *dialView;
    
    WSIDECL_PRIVATE_EX(UINavigationDialController, d_ptr_dial);
}

@property (nonatomic, retain) NSArray *itemControllers;
@property (nonatomic, assign) WSIUIViewController *selectedController;
@property (nonatomic, readonly) UINavigationDialView *dialView;

//! clear all controllers.
- (void)clear;

//! select controller.
- (void)selectController:(WSIUIViewController*)ctlr animated:(BOOL)animated;

@end

extern NSString *kIdentifyDialItem;

WSI_END_HEADER_OBJC

# endif