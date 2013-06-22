
# ifndef __NNT_UIKIT_TABBARCONTAINER_386756BAC78F4B2897780506508B8CC3_H_INCLUDED
# define __NNT_UIKIT_TABBARCONTAINER_386756BAC78F4B2897780506508B8CC3_H_INCLUDED

# import "UIViewController+NNT.h"
# import "UITabBar+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UITabBarContainerController : NNTUIViewController <NNTUITabBarDelegate> {
    
    //! controllers.
    NSArray *viewControllers;
    
    //! selected view controller.
	UIViewController *selectedViewController;
    
    //! tabBar.
	NNTUITabBar *tabBar;
        
    //! selectedIndex.
    NSUInteger selectedIndex;
    
}

@property (nonatomic, retain) NSArray *viewControllers;
@property (nonatomic, retain) NNTUITabBar *tabBar;
@property (nonatomic, retain) UIViewController *selectedViewController;
@property (nonatomic, assign) NSUInteger selectedIndex;

- (id)init;

@end

NNT_END_HEADER_OBJC

# endif