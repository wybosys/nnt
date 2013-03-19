
# ifndef __WSI_UIKIT_UITABBARVIEW_C8BC0A5B30EF46BEA8B7E5F70561D85B_H_INCLUDED
# define __WSI_UIKIT_UITABBARVIEW_C8BC0A5B30EF46BEA8B7E5F70561D85B_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

enum {
    UITabBarPositionBottom,
    UITabBarPositionTop,
    //UITabBarPositionLeft,
    //UITabBarPositionRight
};
typedef uint UITabBarPosition;

WSIDECL_EXTERN_CLASS(WSIUITabBar);

@interface WSIUITabBarView : WSIUIView {
    
    //! content view.
    UIView *contentView;
    
    //! tab bar.
	WSIUITabBar *tabBar;
    
    //! position of tab bar, default is UITabBarPositionBottom.
    UITabBarPosition tabBarPosition;
    
    //! tabbar's height.
    real tabBarHeight;
}

@property (nonatomic, assign) UIView *contentView;
@property (nonatomic, assign) WSIUITabBar *tabBar;
@property (nonatomic, assign) UITabBarPosition tabBarPosition;
@property (nonatomic, assign) real tabBarHeight;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class TabBarView
: public View<TabBarView, WSIUITabBarView>
{
    typedef View<TabBarView, WSIUITabBarView> super;
    
public:
    
    TabBarView(WSIUITabBarView* view)
    : super(view)
    {
        PASS;
    }
    
    void set_tabbar_height(real val)
    {
        this->_self.tabBarHeight = val;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif