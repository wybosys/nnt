
# ifndef __NNT_UIKIT_UITABBARVIEW_C8BC0A5B30EF46BEA8B7E5F70561D85B_H_INCLUDED
# define __NNT_UIKIT_UITABBARVIEW_C8BC0A5B30EF46BEA8B7E5F70561D85B_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

enum {
    UITabBarPositionBottom,
    UITabBarPositionTop,
    //UITabBarPositionLeft,
    //UITabBarPositionRight
};
typedef uint UITabBarPosition;

NNTDECL_EXTERN_CLASS(NNTUITabBar);

@interface NNTUITabBarView : NNTUIView {
    
    //! content view.
    UIView *contentView;
    
    //! tab bar.
	NNTUITabBar *tabBar;
    
    //! position of tab bar, default is UITabBarPositionBottom.
    UITabBarPosition tabBarPosition;
    
    //! tabbar's height.
    real tabBarHeight;
}

@property (nonatomic, assign) UIView *contentView;
@property (nonatomic, assign) NNTUITabBar *tabBar;
@property (nonatomic, assign) UITabBarPosition tabBarPosition;
@property (nonatomic, assign) real tabBarHeight;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class TabBarView
: public View<TabBarView, NNTUITabBarView>
{
    typedef View<TabBarView, NNTUITabBarView> super;
    
public:
    
    TabBarView(NNTUITabBarView* view)
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif