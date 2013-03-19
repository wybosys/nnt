
# ifndef __BBTABBAR_F8ED6AA888284382BF7C6ED2E9172AF8_H_INCLUDED
# define __BBTABBAR_F8ED6AA888284382BF7C6ED2E9172AF8_H_INCLUDED

# import "BBTab.h"
# import "BBTabItem.h"


WSI_BEGIN_HEADER_OBJC


NNTDECL_EXTERN_CLASS(BBTab);
NNTDECL_EXTERN_CLASS(BBTabItem);


@protocol BBTabBarDelegate <NSObject>

- (void)tabBar:(BBTabBar *)tabBar tabSelected:(NSInteger)selectedIndex;

@end

@interface BBTabBar : UIView {
    NSString       *_tabStyle;
    
    NSInteger      _selectedTabIndex;
    NSArray        *_tabItems;
    NSMutableArray *_tabViews;
    
    id<BBTabBarDelegate> _delegate;
}

@property (nonatomic, copy)   NSString        *tabStyle;
@property (nonatomic, assign) BBTabItem       *selectedTabItem;
@property (nonatomic, assign) BBTab           *selectedTabView;
@property (nonatomic)         NSInteger        selectedTabIndex;

@property (nonatomic, copy)    NSArray        *tabItems;
@property (nonatomic, readonly)NSMutableArray *tabViews;

@property (nonatomic, assign) id<BBTabBarDelegate> delegate;


- (id)initWithFrame:(CGRect)frame;
- (void)tabTouchedUp:(BBTab *)tab;

- (void)showTabAtIndex:(NSInteger)tabIndex;
- (void)hideTabAtIndex:(NSInteger)tabIndex;

@end

WSI_END_HEADER_OBJC

# endif