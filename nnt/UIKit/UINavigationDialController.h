
# ifndef __NNT_UIKIT_UIDIALNAVIGATIONCONTROLLER_52636679239241AEBC49667F5FA85F75_H_INCLUDED
# define __NNT_UIKIT_UIDIALNAVIGATIONCONTROLLER_52636679239241AEBC49667F5FA85F75_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UINavigationDialController);
NNTDECL_EXTERN_CLASS(UINavigationDialView);

@interface UINavigationDialController : NNTUIViewController {
    
    //! controllers navi by this controller.
    NSArray *itemControllers;
    
    //! selected controller.
    NNTUIViewController *selectedController;
    
    //! dialView.
    UINavigationDialView *dialView;
    
    NNTDECL_PRIVATE_EX(UINavigationDialController, d_ptr_dial);
}

@property (nonatomic, retain) NSArray *itemControllers;
@property (nonatomic, assign) NNTUIViewController *selectedController;
@property (nonatomic, readonly) UINavigationDialView *dialView;

//! clear all controllers.
- (void)clear;

//! select controller.
- (void)selectController:(NNTUIViewController*)ctlr animated:(BOOL)animated;

@end

extern NSString *kIdentifyDialItem;

NNT_END_HEADER_OBJC

# endif