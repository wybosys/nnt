
# ifndef __BBTAB_C629B6A8BAB74B65B0A8F295A82018C3_H_INCLUDED
# define __BBTAB_C629B6A8BAB74B65B0A8F295A82018C3_H_INCLUDED

# import "BBTabBar.h"
# import "BBTabItem.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(BBTabBar);
WSIDECL_EXTERN_CLASS(BBTabItem);

@interface BBTab : WSIUIButton {
    BBTabItem   *_tabItem;
}

@property  (nonatomic, retain) BBTabItem *tabItem;

- (id)initWithItem:(BBTabItem *)item tabBar:(BBTabBar *)tabBar;

@end

WSI_END_HEADER_OBJC

# endif