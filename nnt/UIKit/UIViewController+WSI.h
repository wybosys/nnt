
# ifndef __WSI_UIKIT_UIVIEWCONTROLLER_FA27AA61423841B1B5E70D2075DD4096_H_INCLUDED
# define __WSI_UIKIT_UIVIEWCONTROLLER_FA27AA61423841B1B5E70D2075DD4096_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN NSString *kTabBarController;
WSI_EXTERN NSString *kTabBarItem;

enum {
    UIOrientationPortraitEnable = UIInterfaceOrientationPortrait,
    UIOrientationPortraitUpsideDownEnable = UIInterfaceOrientationPortraitUpsideDown << 4,
    UIOrientationLandscapeLeftEnable = UIInterfaceOrientationLandscapeLeft << 8,
    UIOrientationLandscapeRightEnable = UIInterfaceOrientationLandscapeRight << 12, 
    
    UIOrientationPortraitEnableAll = UIOrientationPortraitEnable | UIOrientationPortraitUpsideDownEnable,
    UIOrientationLandscapeEnableAll = UIOrientationLandscapeLeftEnable | UIOrientationLandscapeRightEnable,
    UIOrientationEnableAll = UIOrientationPortraitEnableAll | UIOrientationLandscapeEnableAll,
};
typedef uint UIOrientationEnable;

WSI_EXTERN BOOL UIOrientationEnableCheck(UIOrientationEnable, UIInterfaceOrientation);

WSIDECL_EXTERN_CLASS(WSIUIViewController);

@interface UIViewController (WSI)

//! for some view controlelr as WSIUITabBarController to get icon name.
- (NSString*)icon;

//! add subcontrollers.
- (void)addSubController:(UIViewController*)ctlr;

//! remove from super controller.
- (void)removeFromSuperController;

//! for present.
- (void)presentModalViewControllerWithAnimated:(UIViewController*)ctlr;
- (void)presentModalViewControllerNoAnimated:(UIViewController*)ctlr;

//! dismiss presented view controller.
- (void)dismissPresentedViewController:(BOOL)animated;

@end

//! protocol for rotation.
@protocol UIViewControllerRotation <NSObject>

//! invoked while orientation changed.
- (void)viewController:(WSIUIViewController*)ctlr orientation:(UIInterfaceOrientation)orientation;

@end

WSIDECL_EXTERN_CLASS(UITheme);

//! protocol for theme.
@protocol UIViewControllerTheme < NSObject >

//! invoked while theme changed.
- (void)viewControllerTheme:(WSIUIViewController*)ctlr changeTheme:(UITheme*)theme;

@end

WSIDECL_EXTERN_CLASS(WSIUITabBarController);
WSIDECL_EXTERN_CLASS(WSIUITabBarItem);

@interface WSIUIViewControllerBase : UIViewController {
    WSIOBJECT_DECL;
    
    //! default is NO. Set YES while rotation's notice met.
    BOOL isNeedAdjustForRotation;
    
    //! image.
    UIImage *titleImage;
        
    //! class for view.
    Class classView;
    
    //! super controller.
    WSIUIViewController* superController;
    
    //! sub controllers.
    NSArray* subControllers;
    
    //! orientation set.
    UIOrientationEnable _orientationEnable;
    
    @private
    id _viewobj;
}

WSIOBJECT_PROP;

//! isappeared.
@property (nonatomic, assign) BOOL isAppeared;

//! need adjust for rotation.
@property (nonatomic, assign) BOOL isNeedAdjustForRotation;

//! image of title.
@property (nonatomic, retain) UIImage *titleImage;

//! navigation controller.
@property (nonatomic, assign) UINavigationController *navigationController;

//! tabbar controller.
@property (nonatomic, assign) UITabBarController *tabBarController;

//! orientation supported.
@property (nonatomic, assign) UIOrientationEnable orientationEnable;

//! class for instance its view.
@property (nonatomic, assign) Class classView;

//! super controller.
@property (nonatomic, assign, readonly) WSIUIViewController* superController;

//! sub controllers.
@property (nonatomic, readonly) NSArray* subControllers;

//! view is loading.
- (void)viewIsLoading;

//! view is unloading.
- (void)viewIsUnloading;

//! view is appearing.
- (void)viewIsAppearing:(BOOL)animated;

//! view is disappearing.
- (void)viewIsDisappearing:(BOOL)animated;

//! other.
- (void)dismissModalViewController;
- (void)dismissModalViewControllerAnimated;

//! add subcontrollers.
- (void)addSubController:(UIViewController*)ctlr;

//! remove from super controller.
- (void)removeFromSuperController;

@end

# define WSIDECL_VIEWCONTROLLER \
- (void)viewIsLoading; \
- (void)viewIsUnloading; \
- (void)viewIsAppearing:(BOOL)animated; \
- (void)viewIsDisappearing:(BOOL)animated; \
- (void)dismissModalViewController; \
- (void)dismissModalViewControllerAnimated;

# define WSIIMPL_VIEWCONTROLLER \
- (void)viewDidLoad { \
WSI_AUTORELEASEPOOL_BEGIN; \
[super viewDidLoad]; \
[self viewIsLoading]; \
WSI_AUTORELEASEPOOL_END; \
} \
- (void)viewDidUnload { \
[super viewDidUnload]; \
[self viewIsUnloading]; \
} \
- (void)viewDidAppear:(BOOL)animated { \
[super viewDidAppear:animated]; \
[self viewIsAppearing:animated]; \
} \
- (void)viewDidDisappear:(BOOL)animated {\
[super viewDidDisappear:animated]; \
[self viewIsDisappearing:animated]; \
} \
- (void)dismissModalViewController { \
[self dismissModalViewControllerAnimated:NO]; \
} \
- (void)dismissModalViewControllerAnimated { \
[self dismissModalViewControllerAnimated:YES]; \
}

@interface WSIUIViewControllerIB : WSIUIViewControllerBase {    

}

@end

@interface WSIUIViewController : WSIUIViewControllerBase

@property (nonatomic, readonly) WSIUIView *wsiview;

@end

WSIDECL_CATEGORY(UIViewController, WSI);

WSIDECL_EXTERN_CLASS(WSIUIWebView);

@interface WSIUIHtmlController : WSIUIViewController

@property (nonatomic, readonly) WSIUIWebView* htmlView;

@end

# pragma mark signals

//! view did appear.
WSI_EXTERN signal_t kSignalViewAppear;

//! view will appear.
WSI_EXTERN signal_t kSignalViewAppearing;

//! view did disappear.
WSI_EXTERN signal_t kSignalViewDisappear;

//! view will disappear.
WSI_EXTERN signal_t kSignalViewDisappearing;
 
//! orientation changed.
WSI_EXTERN signal_t kSignalOrientationChanged;

//! title did changed.
WSI_EXTERN signal_t kSignalTitleChanged;

//! dismiss.
WSI_EXTERN signal_t kSignalDismiss;

//! remote control event.
WSI_EXTERN signal_t kSignalRemoteControlEvent;

//! key for attach modal's parent controller.
WSI_EXTERN NSString* kViewControllerModalParentController;

# ifdef WSI_CXX

# define _CXXCONTROLLER(cls) _objc_cxx_##cls##_wrapper

# define _CXXCONTROLLER_DECL_BEGIN(cls) \
@interface _CXXCONTROLLER(cls) : cls <_cxx_uicontroller_wrapper> \
{ ::wsi::ui::IViewController* _cxxobj; }

# define _CXXCONTROLLER_DECL_END @end

# define _CXXCONTROLLER_DECL(cls) \
_CXXCONTROLLER_DECL_BEGIN(cls) \
_CXXCONTROLLER_DECL_END

# define _CXXCONTROLLER_IMPL_BEGIN(cls) \
@implementation _CXXCONTROLLER(cls) \
@synthesize _cxxobj; \
- (void)dealloc { \
if (_cxxobj) \
_cxxobj->destroy(); \
[super dealloc]; \
} \
- (void*)object { \
return _cxxobj->cxxobject(); \
} \
- (void)viewDidLoad { \
[super viewDidLoad]; \
if (_cxxobj) \
_cxxobj->view_loaded(); \
}

# define _CXXCONTROLLER_IMPL_END @end

# define _CXXCONTROLLER_IMPL(cls) \
_CXXCONTROLLER_IMPL_BEGIN(cls) \
_CXXCONTROLLER_IMPL_END

# else

# define _CXXCONTROLLER(cls)
# define _CXXCONTROLLER_DECL_BEGIN(cls)
# define _CXXCONTROLLER_DECL_END
# define _CXXCONTROLLER_DECL(cls)

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class NavigationController;

class IViewController
: public IObject
{
public:
    
    //! callback while viewDidLoaded.
    virtual void view_loaded() = 0;
    
    //! create view.
    virtual UIView* load_view() = 0;
    
    //! free view.
    virtual void free_view() = 0;
    
    //! orientation changed.
    virtual void orientation(UIInterfaceOrientation) = 0;
    
    //! change theme.
    virtual void theme(ui::Theme const&) = 0;
    
    //! get navigation.
    virtual NavigationController& navigation() = 0;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

WSI_BEGIN_HEADER_OBJC

@protocol _cxx_uicontroller_wrapper < NSObject >

@property (nonatomic, assign) ::wsi::ui::IViewController* _cxxobj;

@end

@interface _cxx_uiviewcontroller_wrapper : WSIUIViewController <
_cxx_uicontroller_wrapper,
UIViewControllerRotation,
UIViewControllerTheme
>
{
    ::wsi::ui::IViewController* _cxxobj;
}

@end

@interface _cxx_simplecontroller_wrapper : WSIUIViewController <_cxx_uicontroller_wrapper> {
    ::wsi::ui::IViewController* _cxxobj;
}

@end

WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(tpl)

template <typename implT>
class _Controller
: public implT
{
public:
    
    void set_transition(UIModalTransitionStyle style)
    {
        this->_self.modalTransitionStyle = style;
    }
    
    UIModalTransitionStyle transition_style() const
    {
        return this->_self.modalTransitionStyle;
    }
    
    void set_presentation(UIModalPresentationStyle style)
    {
        this->_self.modalPresentationStyle = style;
    }
    
    UIModalPresentationStyle presentation_style() const
    {
        return this->_self.modalPresentationStyle;
    }
    
    template <typename otherctlrT>
    void present(otherctlrT const& ctlr, bool animated = true, bool modal = true)
    {
        wtl::const_pointer<otherctlrT> ptr(ctlr);
        [this->_self presentModalViewController:*ptr animated:modal];
    }
    
    void dismiss(bool animated = true)
    {
        [this->_self dismissModalViewControllerAnimated:animated];
    }
    
    void dismiss_presented(bool animated = true)
    {
        [this->_self dismissPresentedViewController:animated];
    }
    
};

template <
typename implT,
typename ctlrT, // ns controller.
typename viewT, // ns view of controller.
typename cxxviewT = _NullView<viewT>, 
typename interT = IViewController
>
class SimpleController
:
public _Controller<Object<implT, ctlrT> >,
public interT
{    
    typedef Object<implT, ctlrT> super;
    typedef SimpleController<implT, ctlrT, viewT, cxxviewT, interT> self_type;
    WSIDECL_NOCOPY_EX(SimpleController, self_type);
    
public:
    
    typedef ctlrT controller_type;
    typedef empty_controller_type empty_type;
    typedef cxxviewT view_type;
    
    SimpleController()
    {
        ((implT*)this)->init();
        
        _iswrapper = [this->_self conformsToProtocol:@protocol(_cxx_uicontroller_wrapper)];

        if (_iswrapper)
        {
            id<_cxx_uicontroller_wrapper> obj = (id<_cxx_uicontroller_wrapper>)this->_self;
            obj._cxxobj = (implT*)this;
        }
    }
        
    explicit SimpleController(controller_type* ctlr)
    : _iswrapper(false)
    {
        this->_self = [ctlr retain];
    }
        
    ~SimpleController();
    
    //! get objc controller.
    /*operator controller_type* () const
    {
        return (controller_type*)this->_self;
    }
     */
    
    operator UIViewController* () const
    {
        return (UIViewController*)this->_self;
    }
    
    operator WSIUIViewController* () const
    {
        return (WSIUIViewController*)this->_self;
    }
    
    //! init.
    void init()
    {
        this->_self = [[controller_type alloc] init];
    }
             
    //! get view.
    view_type& view()
    {
        if (_view.get() == NULL)
        {
            _view.reset(
                        new view_type(
                                      (typename view_type::view_type*)this->_self.view,
                                      true
                                      )
                        );
        }
        return *_view;
    }
    
    virtual void free_view()
    {
        _view.reset(NULL);
    }
    
    //! get view.
    view_type const& view() const
    {
        return *_view;
    }
    
    //! set ori.
    void set_orientation(UIOrientationEnable val)
    {
        this->_self.orientationEnable = val;
    }
    
    //! set title.
    void set_title(ns::String const& str)
    {
        this->_self.title = str;
    }
    
    //! operator.
    implT* operator -> ()
    {
        return (implT*)this;
    }
    
    implT const* operator -> () const
    {
        return (implT*)this;
    }
    
    //! get navigation controller.
    virtual NavigationController& navigation();
    
    //! set navigation controller.
    void set_navigation(NavigationController const& navi);
    
    //! release self.
    virtual void drop()
    {
        super::drop();
    }
    
    //! destroy.
    virtual void destroy()
    {
        this->_self = nil;
        super::destroy();
    }
    
    //! get cxx class object.
    virtual void* cxxobject() const
    {
        return (implT*)this;
    }
    
    //! get objc class object.
    virtual id nsobject() const
    {
        return this->_self;
    }
    
    //! for loaded.
    virtual void view_loaded()
    {
        PASS;
    }
    
    virtual void orientation(UIInterfaceOrientation)
    {
        PASS;
    }
    
    virtual void theme(ui::Theme const&)
    {
        PASS;
    }
    
    void remove_fromsuper()
    {
        [this->_self.view removeFromSuperview];
    }
    
protected:
    
    virtual UIView* load_view()
    {
        return nil;
    }
    
    core::auto_ptr<view_type> _view;
    core::auto_ptr<NavigationController> _navi;
    bool _iswrapper;
    
};

template <typename implT, typename viewT, 
typename ctlrT = _cxx_uiviewcontroller_wrapper,
typename interT = IViewController
>
class Controller
: 
public _Controller<Object<implT, ctlrT> >,
public IViewController
{    
    typedef Object<implT, ctlrT> super;
    typedef Controller<implT, viewT, ctlrT, interT> self_type;
    WSIDECL_NOCOPY_EX(Controller, self_type);
    
public:    
    
    typedef ctlrT controller_type;
    typedef viewT view_type;
    typedef empty_controller_type empty_type;
    
    Controller()
    {
        ((implT*)this)->init();
        
        _iswrapper = [this->_self conformsToProtocol:@protocol(_cxx_uicontroller_wrapper)];
        
        if (_iswrapper)
        {
            id<_cxx_uicontroller_wrapper> obj = (id<_cxx_uicontroller_wrapper>)this->_self;            
            obj._cxxobj = (implT*)this;
        }
    }
    
    explicit Controller(ctlrT* ctlr)
    : _iswrapper(false)
    {
        this->_self = [ctlr retain];
    }
        
    ~Controller();    
    
    operator controller_type* () const
    {
        return (controller_type*)this->_self;
    }
    
    void init()
    {
        this->_self = [[controller_type alloc] init];
    }
        
    virtual UIView* load_view()
    {
        if (_view.get() == NULL)
        {
            _view.reset(
                        new view_type
                        );
        }
        return **_view;
    }
    
    virtual void free_view()
    {
        _view.reset(NULL);
    }
    
    view_type& view()
    {
        if (_view.get() == NULL)
        {
            [this->_self view];
            //_view = new view_type;
            //this->_self.view = *_view;
        }
        return *_view;
    }
    
    view_type const& view() const
    {
        return *_view;
    }
    
    virtual NavigationController& navigation();
    
    void set_navigation(NavigationController const& navi);
    
    template <typename subcontrollerT>
    void add_subcontroller(subcontrollerT const& ctlr,
                                  typename wtl::mixin_type<subcontrollerT>::type::controller_type const* = NULL)
    {
        wtl::const_pointer<subcontrollerT> ptr(ctlr);
        [this->_self addSubController:*ptr];
    }
    
    template <typename subcontrollerT>
    void remove_subcontroller(subcontrollerT const& ctlr,
                                     typename wtl::mixin_type<subcontrollerT>::type::controller_type const* = NULL)
    {
        wtl::const_pointer<subcontrollerT> ptr(ctlr);
        [*ptr removeFromSuperController];
    }
    
    void set_orientation(UIOrientationEnable val)
    {
        this->_self.orientationEnable = val;
    }
    
    void set_title(ns::String const& str)
    {
        this->_self.title = str;
    }
    
    ns::String title() const
    {
        return this->_self.title;
    }
    
    void set_title(Image const& img)
    {
        this->_self.tabBarItem.image = img;
    }
    
    Image title_image() const
    {
        return this->_self.tabBarItem.image;
    }
    
    virtual void drop()
    {
        if (this->_reference_count() == 1)
        {
            this->destroy();
        }
        else
        {
            super::drop();
        }
    }
    
    virtual void destroy()
    {
        this->_self = nil;
        super::destroy();
    }
    
    virtual void* cxxobject() const
    {
        return (implT*)this;
    }
    
    virtual id nsobject() const
    {
        return this->_self;
    }
    
    virtual void orientation(UIInterfaceOrientation ori)
    {
        // adjust self.
        if (UIInterfaceOrientationIsLandscape(ori))
            this->landscape();
        else
            this->portrait();
        
        // adjust view.
        // this->view().orientation(ori);
    }
    
    virtual void landscape()
    {
        PASS;
    }
    
    virtual void portrait()
    {
        PASS;
    }
    
    virtual void theme(ui::Theme const&)
    {
        PASS;
    }
    
    //! operator.
    implT* operator -> ()
    {
        return (implT*)this;
    }
    
    implT const* operator -> () const
    {
        return (implT*)this;
    }
    
protected:
    
    void _cxxwrapper_Destroy()
    {        
        // because controller is release, so must set zero to _self.
        this->_self = nil;
        
        // super.
        super::Destroy();
    }
        
protected:
    
    core::auto_ptr<viewT> _view;
    core::auto_ptr<NavigationController> _navi;
    bool _iswrapper;
    
};

template <typename controlT>
class Controllerize
: public Controller< Controllerize<controlT>, controlT>
{
    typedef Controllerize<controlT> self_type;
    
public:
    
    Controllerize()
    {
        PASS;
    }
    
    virtual ~Controllerize()
    {
        PASS;
    }
    
    virtual void view_loaded()
    {
        PASS;
    }
    
    controlT& control()
    {
        return this->view();
    }
    
    controlT* operator -> ()
    {
        return &this->view();
    }
    
    static self_type* New()
    {
        return new self_type;
    }
    
};

WSI_END_NS

using tpl::SimpleController;
using tpl::Controller;
using tpl::Controllerize;

WSI_END_NS 
WSI_END_HEADER_CXX

# include "UINavigationController+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

WSI_BEGIN_NS(tpl)

template <typename implT, typename viewT, typename ctlrT, typename interT>
inline_impl Controller<implT, viewT, ctlrT, interT>::~Controller()
{                      
    if (super::_needrelease == false)
        this->_self = nil;
    
    if (_iswrapper && this->_self)
    {
        id<_cxx_uicontroller_wrapper> obj = (id<_cxx_uicontroller_wrapper>)this->_self;
        obj._cxxobj = NULL;
    }
}

template <typename implT, typename ctlrT, typename viewT, typename cxxviewT, typename interT>
inline_impl SimpleController<implT, ctlrT, viewT, cxxviewT, interT>::~SimpleController()
{                
    if (super::_needrelease == false)
        this->_self = nil;
    
    if (_iswrapper && this->_self)
    {
        id<_cxx_uicontroller_wrapper> obj = (id<_cxx_uicontroller_wrapper>)this->_self;            
        obj._cxxobj = NULL;
    }
}        

template <typename implT, typename viewT, typename ctlrT, typename interT>
inline_impl NavigationController& Controller<implT, viewT, ctlrT, interT>::navigation()
{
    if (_navi.get() == NULL)
    {
        _navi.reset(
                    new NavigationController(this->_self.navigationController)
                    );
    }
    return *_navi;
}

template <typename implT, typename ctlrT, typename viewT, typename cxxviewT, typename interT>
inline_impl NavigationController& SimpleController<implT, ctlrT, viewT, cxxviewT, interT>::navigation()
{
    if (_navi.get() == NULL)
    {
        _navi.reset(
                    new NavigationController(this->_self.navigationController)
                    );
    }
    return *_navi;
}

template <typename implT, typename viewT, typename ctlrT, typename interT>
inline_impl void Controller<implT, viewT, ctlrT, interT>::set_navigation(NavigationController const& navi)
{
    this->_self.navigationController = (UINavigationController*)navi;
}

template <typename implT, typename ctlrT, typename viewT, typename cxxviewT, typename interT>
inline_impl void SimpleController<implT, ctlrT, viewT, cxxviewT, interT>::set_navigation(NavigationController const& navi)
{
    this->_self.navigationController = (UINavigationController*)navi;
}

class _WrapView
: public ui::View<_WrapView>
{
public:
    
    virtual void layout_subviews()
    {
        view.frame = bounds();
    }
    
    UIView* view;
};

template <typename ctlrT>
class WrapController
: public ui::Controller<WrapController<ctlrT>, _WrapView>
{
public:
    
    typedef ctlrT controlelr_type;
    
    WrapController()
    {
        PASS;
    }
    
    ~WrapController()
    {
        PASS;
    }
    
    virtual void view_loaded()
    {
        this->view().view = this->_ctlr.view();
        this->view().add_sub(this->_ctlr.view());
    }
    
    ctlrT& controller()
    {
        return this->_ctlr;
    }
    
    operator ctlrT& ()
    {
        return this->_ctlr;
    }
    
    ctlrT* operator -> ()
    {
        return &_ctlr;
    }
    
protected:
    
    ctlrT _ctlr;
    
};

WSI_END_NS

using tpl::WrapController;

// impl view's function.
template <typename implT, typename viewT, typename interT>
inline_impl void View<implT, viewT, interT>::add_sub(IViewController* ctlr)
{
    [(WSIUIView*)this->_self addSubController:ctlr->nsobject()];
}

class AnyController
: public SimpleController<AnyController, WSIUIViewController, WSIUIView>
{
    typedef SimpleController<AnyController, WSIUIViewController, WSIUIView> super;
    
public:
    
    AnyController()
    {
        PASS;
    }
    
    AnyController(IViewController* ctlr, bool anew = false)
    : super(nil)
    {
        set(ctlr);
        
        if (anew)
            [this->_self release];
    }
    
    AnyController(void* ctlr, bool anew = false)
    : super(nil)
    {
        set(ctlr);
        
        if (anew)
            [this->_self release];
    }
    
    void set(IViewController* ctlr)
    {
        // free.
        free_view();
        
        // set.
        _set(ctlr->nsobject());
    }
    
    void set(void* ctlr)
    {
        IViewController* obj = interface_cast(ctlr, IViewController);
        set(obj);
    }
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif
