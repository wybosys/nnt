
# ifndef __NNT_UIKIT_UINAVIGATIONCONTROLLER_90D4370D6E834DB7B57C6CC065D6C8CE_H_INCLUDED
# define __NNT_UIKIT_UINAVIGATIONCONTROLLER_90D4370D6E834DB7B57C6CC065D6C8CE_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTUIViewController);

extern NSString* kNavigationControllerBarVisible;

@interface UINavigationController (NNT)

//! get index for controller.
- (NSUInteger)indexOfViewController:(UIViewController*)ctlr;

//! get controller at index.
- (UIViewController*)viewControllerAtIndex:(NSUInteger)idx;

//! get previous viewcontroller.
- (UIViewController*)preViewController:(UIViewController*)ctlr;

//! get next viewcontroller.
- (UIViewController*)nextViewController:(UIViewController*)ctlr;

//! count of viewcontrollers.
- (NSUInteger)countOfViewControllers;

//! add top items.
- (void)addTopRightItems:(NSArray*)items;
- (void)addTopLeftItems:(NSArray*)items;

@end

NNTDECL_CATEGORY(UINavigationController, NNT);

@interface NNTUINavigationControllerBase : UINavigationController {
    
    //! auto toggle home back. default is NO.
    BOOL _showHomeBack;
    
    //! home back button.
    NSArray *_homeBack;
    
    //! title of home back button.
    NSString *_titleHomeBack;
    
    //! title image.
    UIImage *_titleImage;
    
    //! auto control bar's hidden. default is NO.
    BOOL _navigationBarHiddenByController;
    
    //! tabbar's background fill
    NgFill* _topbarBackgroundFill;
    
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@property (nonatomic, assign) BOOL showHomeBack;
@property (nonatomic, assign, readonly) NSArray *homeBack;
@property (nonatomic, copy) NSString *titleHomeBack;
@property (nonatomic, assign) BOOL navigationBarHiddenByController;
@property (nonatomic, readonly) NNTUIViewController* rootViewController;
@property (nonatomic, retain) UIImage* titleImage;
@property (nonatomic, retain) NgFill* topbarBackgroundFill;

//! orientation supported.
@property (nonatomic, assign) UIOrientationEnable orientationEnable;

//! show home back button.
- (void)showHomeBack:(BOOL)vis animated:(BOOL)animated;

//! init.
- (id)initWithRootViewController:(NNTUIViewController *)rootViewController;

//! override.
- (void)pushViewController:(NNTUIViewController *)viewController animated:(BOOL)animated;
- (NSArray*)popToViewController:(NNTUIViewController *)viewController animated:(BOOL)animated;

NNTDECL_VIEWCONTROLLER;

@end

@interface NNTUINavigationController : NNTUINavigationControllerBase
@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIViewController+NNT.h"
# include "UINavigationBar+NNT.h"

NNT_BEGIN_HEADER_OBJC

_CXXCONTROLLER_DECL(NNTUINavigationController);

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

class NavigationController
: public SimpleController< NavigationController, 
_CXXCONTROLLER(NNTUINavigationController),
UIView
>
{
    typedef SimpleController<NavigationController, 
    _CXXCONTROLLER(NNTUINavigationController), 
    UIView
    > super;
    
public:
    
    NavigationController()
    : _bar(NULL)
    {
        PASS;
    };
        
    explicit NavigationController(NNTUIViewController* root)
    : _bar(NULL)
    {
        [this->_self pushViewController:root animated:NO];
    }
    
    explicit NavigationController(UINavigationController* navi)
    : super((_CXXCONTROLLER(NNTUINavigationController)*)navi),
    _bar(NULL)
    {
        // redurce reference count, for keep navigation controller as assign property.
        super::_release();
        super::_needrelease = false;
    }
        
    ~NavigationController()
    {        
        safe_delete(_bar);
    }
        
    template <typename controllerT>
    void push(controllerT const& ctlr, bool animated = true,
              typename ntl::mixin_type<controllerT>::type::controller_type const* = NULL)
    {
        ntl::const_pointer<controllerT> ptr(ctlr);
        [this->_self pushViewController:*ptr animated:animated];
    }
    
    void pop(bool animated = true)
    {
        [this->_self popViewControllerAnimated:animated];
    }
    
    NavigationBar& topbar() const
    {
        NavigationController* ctlr = const_cast<NavigationController*>(this);
        if (ctlr->_bar == NULL)
            ctlr->_bar = new NavigationBar(this->_self.navigationBar, ctlr);
        return *ctlr->_bar;
    }
    
protected:
    
    NavigationBar *_bar;
    
};

inline_impl void NavigationBar::set_visible(bool val)
{
    (**_ctlr).navigationBarHidden = !val;
}

inline_impl void NavigationBar::set_rightitems(ns::Array const& arr)
{
    [(**_ctlr) addTopRightItems:arr];
}

inline_impl void NavigationBar::set_leftitems(ns::Array const& arr)
{
    [(**_ctlr) addTopLeftItems:arr];
}

template <typename controllerT>
class Navigatilize
: public NavigationController
{
    typedef NavigationController super;
    typedef Navigatilize<controllerT> self_type;
    
public:
    
    typedef controllerT controller_type;
    
    Navigatilize()
    {
        _ctlr = new controllerT;
        super::push(_ctlr, false);
    }
    
    ~Navigatilize()
    {
        _ctlr->drop();
    }
    
    operator controllerT& ()
    {
        return *_ctlr;
    }
    
    controllerT* operator -> ()
    {
        return _ctlr;
    }
        
    static self_type* New()
    {
        return new self_type;
    }
    
    controller_type& root() const
    {
        return *(controller_type*)_ctlr;
    }
    
protected:
    
    controllerT* _ctlr;
    
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif