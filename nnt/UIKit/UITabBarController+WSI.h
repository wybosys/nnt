
# ifndef __WSI_UIKIT_UITABBARCONTROLLER_843841753F1846E086583B105D53B868_H_INCLUDED
# define __WSI_UIKIT_UITABBARCONTROLLER_843841753F1846E086583B105D53B868_H_INCLUDED

# import "UITabBarView+WSI.h"
# import "UIViewController+WSI.h"
# import "UITabBar+WSI.h"

WSI_BEGIN_HEADER_OBJC

extern NSString *kTabBarController;
extern NSString *kTabBarItem;

@interface UITabBarController (WSI)

@end

WSIDECL_CATEGORY(UITabBarController, WSI);
WSIDECL_EXTERN_CLASS(WSIUITabBar);
WSIDECL_EXTERN_CLASS(WSIUITabBarView);

@interface WSIUITabBarController : WSIUIViewController <WSIUITabBarDelegate> {

    //! controllers.
    NSArray *viewControllers;
    
    //! selected view controller.
	UIViewController *selectedViewController;
    
    //! tabBar.
	WSIUITabBar *tabBar;
    
    //! tabBarView.
	WSIUITabBarView *tabBarView;
    
    //! visible.
	BOOL visible;
    
    //! selectedIndex.
    NSUInteger selectedIndex; 
}

@property (nonatomic, retain) NSArray *viewControllers;
@property (nonatomic, retain) WSIUITabBar *tabBar;
@property (nonatomic, assign) UIViewController *selectedViewController;
@property (nonatomic, readonly) WSIUITabBarView *tabBarView;
@property (nonatomic, assign) NSUInteger selectedIndex;

- (id)init;

@end

WSI_EXTERN real kUITabBarHeight;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "UIViewController+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class TabBarController
: public SimpleController<TabBarController, WSIUITabBarController, WSIUITabBarView>
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
        wtl::const_pointer<ctlrT> ptr(ctlr);
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif