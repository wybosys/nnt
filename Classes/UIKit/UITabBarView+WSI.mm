
# import "Core.h"
# import "UITabBarView+WSI.h"
# import "UITabBar+WSI.h"

WSI_BEGIN_OBJC

@implementation WSIUITabBarView

@synthesize tabBar, contentView, tabBarPosition;
@dynamic tabBarHeight;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor blackColor];
    //self.autoresizesSubviews = NO;
    tabBarPosition = UITabBarPositionBottom;
    
    return self;
}

- (void)setTabBar:(WSIUITabBar *)aTabBar {
	[tabBar removeFromSuperview];
	[tabBar release];
	tabBar = aTabBar;
	[self addSubview:tabBar];
}

- (void)setContentView:(UIView *)aContentView {
	[contentView removeFromSuperview];
	contentView = aContentView;
    
    CGRect f = CGRectMake(0, 0, self.bounds.size.width, self.bounds.size.height);
    
    if (self.tabBar.hidden == NO) {
        f.size.height -= self.tabBar.bounds.size.height;
    }
    
	contentView.frame = f;
    
	[self addSubview:contentView];
	[self sendSubviewToBack:contentView];
    
    [self setNeedsLayout];
}

- (void)layoutSubviews {
    CGRect rc_content = self.bounds;
    CGRect rc_tabbar = self.bounds;
    CGRect oldrc_tabbar = self.tabBar.frame;
    
    switch (tabBarPosition)
    {
        default: break;
        case UITabBarPositionTop: {            
            if (self.tabBar.hidden == NO) {
                rc_content.size.height -= oldrc_tabbar.size.height;
                rc_content.origin.y += oldrc_tabbar.size.height;
                rc_tabbar.size.height = oldrc_tabbar.size.height;
            } else {
                rc_tabbar = oldrc_tabbar;
            }
        } break;
        case UITabBarPositionBottom: {
            if (self.tabBar.hidden == NO) {
                rc_content.size.height -= oldrc_tabbar.size.height;
                rc_tabbar.size.height = oldrc_tabbar.size.height;
                rc_tabbar.origin.y = rc_content.size.height;
            } else {
                rc_tabbar = oldrc_tabbar;
            }
        } break;
    }
    
    self.tabBar.frame = rc_tabbar;
    self.contentView.frame = rc_content;
}

- (real)tabBarHeight {
    return self.tabBar.frame.size.height;
}

- (void)setTabBarHeight:(real)val {
    CGRect rc = self.tabBar.frame;
    rc.size.height = val;
    self.tabBar.frame = rc;
    [self setNeedsLayout];
}

@end

WSI_END_OBJC