
# ifndef __WSI_UIKIT_TABBARCONTAINER_386756BAC78F4B2897780506508B8CC3_H_INCLUDED
# define __WSI_UIKIT_TABBARCONTAINER_386756BAC78F4B2897780506508B8CC3_H_INCLUDED

# import "UIViewController+WSI.h"
# import "UITabBar+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UITabBarContainerController : WSIUIViewController <WSIUITabBarDelegate> {
    
    //! controllers.
    NSArray *viewControllers;
    
    //! selected view controller.
	UIViewController *selectedViewController;
    
    //! tabBar.
	WSIUITabBar *tabBar;
        
    //! selectedIndex.
    NSUInteger selectedIndex;
    
}

@property (nonatomic, retain) NSArray *viewControllers;
@property (nonatomic, retain) WSIUITabBar *tabBar;
@property (nonatomic, retain) UIViewController *selectedViewController;
@property (nonatomic, assign) NSUInteger selectedIndex;

- (id)init;

@end

WSI_END_HEADER_OBJC

# endif