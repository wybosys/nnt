
# ifndef __NNT_UIKIT_UITABBARCONTROLLER_843841753F1846E086583B105D53B868_H_INCLUDED
# define __NNT_UIKIT_UITABBARCONTROLLER_843841753F1846E086583B105D53B868_H_INCLUDED

# import "UITabBarView+NNT.h"
# import "UIViewController+NNT.h"
# import "UITabBar+NNT.h"

NNT_BEGIN_HEADER_OBJC

extern NSString *kTabBarController;
extern NSString *kTabBarItem;

@interface UITabBarController (NNT)

@end

NNTDECL_CATEGORY(UITabBarController, NNT);
NNTDECL_EXTERN_CLASS(NNTUITabBar);
NNTDECL_EXTERN_CLASS(NNTUITabBarView);

@interface NNTUITabBarController : NNTUIViewController <NNTUITabBarDelegate> {

    //! controllers.
    NSArray *viewControllers;
    
    //! selected view controller.
	UIViewController *selectedViewController;
    
    //! tabBar.
	NNTUITabBar *tabBar;
    
    //! tabBarView.
	NNTUITabBarView *tabBarView;
    
    //! visible.
	BOOL visible;
    
    //! selectedIndex.
    NSUInteger selectedIndex; 
}

@property (nonatomic, retain) NSArray *viewControllers;
@property (nonatomic, retain) NNTUITabBar *tabBar;
@property (nonatomic, assign) UIViewController *selectedViewController;
@property (nonatomic, readonly) NNTUITabBarView *tabBarView;
@property (nonatomic, assign) NSUInteger selectedIndex;

- (id)init;

@end

NNT_EXTERN real kUITabBarHeight;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIViewController+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class TabBarController
: public SimpleController<TabBarController, NNTUITabBarController, NNTUITabBarView>
{
    
public:
    
    TabBarController()
    : _tabbar(NULL),
    _view(NULL)
    {
        PASS;
    }
    
    ~TabBarController()
    {
        safe_delete(_tabbar);
        safe_delete(_view);
    }
    
    template <typename ctlrT>
    void add(ctlrT const& ctlr)
    {
        ntl::const_pointer<ctlrT> ptr(ctlr);
        _ctlrs.add(*ptr);
    }
    
    void update();
    
    TabBar& tabbar()
    {
        if (_tabbar == NULL)
            _tabbar = new TabBar(this->_self.tabBar);
        return *_tabbar;
    }
    
    TabBarView& view()
    {
        if (_view == NULL)
            _view = new TabBarView(this->_self.tabBarView);
        return *_view;        
    }
    
protected:
    ns::MutableArray _ctlrs;
    TabBar* _tabbar;
    TabBarView* _view;
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif