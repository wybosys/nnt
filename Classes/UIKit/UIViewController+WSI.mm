
# import "Core.h"
# import "UIViewController+WSI.h"
# import "WSIUIObject.h"
# import "UIScreen+WSI.h"
# import "UIWebView+WSI.h"
# import "UIView+WSI.h"
# import "DTrace.prv.h"

WSI_BEGIN_OBJC

// for solve the difference of [UIViewController view(Did|Should)(Appear|Disappear) bewteen SDKS.
// if is true, WSI will call (appear|disappear) manual.
WSI_EXTERN bool __need_manual_appear;

// support multi-tasks.
WSI_EXTERN bool WSI_SUPPORT_MULTITASKS;

// some signals.
signal_t kSignalViewAppear = @"::wsi::ui::view::appear";
signal_t kSignalViewAppearing = @"::wsi::ui::view::appearing";
signal_t kSignalViewDisappear = @"::wsi::ui::view::disappear";
signal_t kSignalViewDisappearing = @"::wsi::ui::view::disappearing";
signal_t kSignalTitleChanged = @"::wsi::ui::title::changed";
signal_t kSignalDismiss = @"::wsi::ui::dismiss";

// object.
NSString* kViewControllerModalParentController = @"::wsi::ui::viewcontroller::modal::controller::parent";

WSIIMPL_CATEGORY(UIViewController, WSI);

@interface WSIUIViewControllerBase ()

@property (nonatomic, assign) WSIUIViewController* superController;

@end

@implementation UIViewController (WSI)

- (NSString*)icon {
    return @"";
}

- (void)addSubController:(UIViewController*)ctlr {    
    WSIUIViewControllerBase* wsictlr = nil;
    if ([ctlr isKindOfClass:[WSIUIViewControllerBase class]]) {
        wsictlr = (WSIUIViewControllerBase*)ctlr;
    }
    
    if (wsictlr) {
        if (wsictlr.superController)
            return;
        wsictlr.superController = (WSIUIViewController*)self;
        if (wsictlr.isAppeared)
            [ctlr viewWillAppear:NO];
    } else {
        [ctlr viewWillAppear:NO];
    }
    
    [self.view addSubview:ctlr.view];
    
    if (wsictlr) {
        if (wsictlr.isAppeared)
            [ctlr viewDidAppear:NO];
    } else {
        [ctlr viewDidAppear:NO];
    }
}

- (void)removeFromSuperController {
    if (__need_manual_appear) {
        [self viewWillDisappear:NO];        
    }
    
    [self.view removeFromSuperview];
    
    if (__need_manual_appear) {
        [self viewDidDisappear:NO];
    }
}

- (void)presentModalViewControllerWithAnimated:(UIViewController*)ctlr {    
    [self presentModalViewController:ctlr animated:YES];
}

- (void)presentModalViewControllerNoAnimated:(UIViewController*)ctlr {
    [self presentModalViewController:ctlr animated:NO];
}

- (void)dismissPresentedViewController:(BOOL)animated {
    UIViewController* ctlr = NULL;
    
    if ([self respondsToSelector:@selector(modalViewController)])
        ctlr = [self performSelector:@selector(modalViewController)];
    else if ([self respondsToSelector:@selector(presentedViewController)])
        ctlr = [self performSelector:@selector(presentedViewController)];
    
    [ctlr dismissModalViewControllerAnimated:animated];
}

@end

@protocol WSIUIViewOrientation <NSObject>

- (void)setOrientation:(UIDeviceOrientation)orient;

@end

@implementation WSIUIViewControllerBase

@synthesize isNeedAdjustForRotation;
@synthesize titleImage;
@synthesize navigationController;
@synthesize tabBarController;
@synthesize orientationEnable = _orientationEnable;
@synthesize classView;
@synthesize superController, subControllers;
@synthesize isAppeared;

WSIOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super init];
    
    isAppeared = NO;
    isNeedAdjustForRotation = NO;
    
    // bind to global object for signal.
    WSIUIObject* ui_obj = [WSIUIObject shared];
    
    if ([self conformsToProtocol:@protocol(UIViewControllerRotation)]) { 
        [ui_obj connect:kSignalOrientationChanged sel:@selector(__act_device_rotated) obj:self];
    } else {
        [ui_obj connect:kSignalOrientationChanged sel:@selector(__act_device_rotated_pure) obj:self];
    }
    
    if ([self conformsToProtocol:@protocol(UIViewControllerTheme)]) {
        [ui_obj connect:kSignalThemeChanged sel:@selector(__act_theme_changed:) obj:self];
    }
    
    // init orient.
    _orientationEnable = UIOrientationPortraitEnable;
    
    DTRACE_VIEWCOUNTROLLER_COUNTER_INC;
    return self;
}

- (void)dealloc {
    zero_release(titleImage);
    zero_release(subControllers);
    
    [[WSIUIObject shared] disconnect:self];
    
    WSIOBJECT_DEALLOC;
    
    DTRACE_VIEWCOUNTROLLER_COUNTER_DESC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalViewAppear);
    WSIEVENT_SIGNAL(kSignalViewAppearing);
    WSIEVENT_SIGNAL(kSignalViewDisappear);
    WSIEVENT_SIGNAL(kSignalViewDisappearing);
    WSIEVENT_SIGNAL(kSignalOrientationChanged);
    WSIEVENT_SIGNAL(kSignalTitleChanged);
    WSIEVENT_SIGNAL(kSignalDeviceShaked);
    WSIEVENT_SIGNAL(kSignalRemoteControlEvent);
}

- (void)setTitle:(NSString *)str {
    if ([self.title isEqualToString:str]) {
        return;
    }
    
    [super setTitle:str];
    
    [self emit:kSignalTitleChanged result:str];
}

- (void)__act_device_rotated {
    if ([self conformsToProtocol:@protocol(UIViewControllerRotation)] == NO)
        return;
    
    id<UIViewControllerRotation> obj = (id<UIViewControllerRotation>)self;
    isNeedAdjustForRotation = YES;
    
    uint orient = [UIScreen orientation];
    
    if (orient == UIDeviceOrientationUnknown)
        return;
    
    WSI_AUTORELEASEPOOL_BEGIN;
        
    // announce as step: 1, controller; 2, view;
    if ([obj respondsToSelector:@selector(viewController:orientation:)]) {
        [obj viewController:(WSIUIViewController*)self orientation:(UIInterfaceOrientation)orient];
    }
    
    if ([_viewobj respondsToSelector:@selector(setOrientation:)]) {
        id<WSIUIViewOrientation> obj = (id<WSIUIViewOrientation>)self.view;
        [obj setOrientation:(UIDeviceOrientation)orient];
    }        
    
    NSNumber *ori = [NSNumber numberWithInt:orient];
    [self emit:kSignalOrientationChanged result:ori];
    
    WSI_AUTORELEASEPOOL_END;
}

- (void)__act_device_rotated_pure {
    isNeedAdjustForRotation = YES;
    uint orient = [UIDevice currentDevice].orientation;
    
    if (orient == UIDeviceOrientationUnknown)
        return;
    
    NSNumber *ori = [NSNumber numberWithInt:orient];
    [self emit:kSignalOrientationChanged result:ori];
}

- (void)__act_theme_changed:(WSIEventObj*)evt {
    id<UIViewControllerTheme> obj = (id<UIViewControllerTheme>)self;    
    [obj viewControllerTheme:(WSIUIViewController*)self changeTheme:(UITheme*)evt.result];
    
    if ([self.view conformsToProtocol:@protocol(UIViewTheme)]) {
        id<UIViewTheme> obj = (id<UIViewTheme>)self.view;
        [obj viewTheme:self.view changeTheme:(UITheme*)evt.result];
    }
}

- (UINavigationController*)navigationController {
    UINavigationController *navi = [super navigationController];
    if (navi == nil) {
        navi = navigationController;
    }
    
# ifdef WSI_DEBUG
    
    if (navi == nil) {
        //dthrow([NSException exceptionWithName:@"::wsi::null_exception"
        //                               reason:@"navigation controller is nil"
        //                             userInfo:nil]);
        ::wsi::ns::String str = @"The ";
        str += NSStringFromClass([self class]);
        str += @" object's navigation controller is NULL!";
        trace_msg(str);
    }
    
# endif
    
    return navi;
}

- (UITabBarController*)tabBarController {
    UITabBarController* tabbar = [super tabBarController];
    if (tabbar == nil) {
        tabbar = tabBarController;
    }
    if (tabbar == nil) {
        tabbar = [self attachFind:kTabBarController];
    }
    if (tabbar == nil) {
        
        dthrow([NSException exceptionWithName:@"::wsi::null_exception"
                                       reason:@"tabbar controller is nil" 
                                     userInfo:nil]);
        
    }
    return tabbar;
}

- (void)loadView {
    if (classView == nil) {
        WSIUIView *view = [[WSIUIView alloc] initWithZero];
        self.view = view;
        [view release];
    }
    else {
        UIView* view = [[classView alloc] initWithZero];
        self.view = view;
        [view release];
    }        
}

- (void)addSubController:(UIViewController*)ctlr {        
    if ([ctlr isKindOfClass:[WSIUIViewControllerBase class]]) {
        if (((WSIUIViewControllerBase*)ctlr).superController)
            return;
        if (subControllers && 
            [subControllers indexOfObject:ctlr] != NSNotFound)
            return;
        ((WSIUIViewControllerBase*)ctlr).superController = (WSIUIViewController*)self;
    }        
    
    if ([ctlr isKindOfClass:[UINavigationController class]]) {
        ctlr.view.frame = CGRectZero;
    }
    
    if (__need_manual_appear) {
        [ctlr viewWillAppear:NO];        
    }
    
    // add controller's view.
    [self.view addSubview:ctlr.view];
    
    // add sub.
    if (subControllers == nil)
        subControllers = [[NSMutableArray alloc] init];
    [(NSMutableArray*)subControllers addObject:ctlr];
    
    if (__need_manual_appear) {
        [ctlr viewDidAppear:NO];
    }
}

- (void)removeFromSuperController {
    if (subControllers && 
        [subControllers indexOfObject:self] != NSNotFound)
        return;
    
    [self retain];
        
    if (__need_manual_appear) {
        [self viewWillDisappear:NO];
    }
    
    if ([superController isKindOfClass:[WSIUIViewControllerBase class]]) {
        [self.view removeFromSuperview];
        [(NSMutableArray*)((WSIUIViewControllerBase*)superController).subControllers removeObject:self];
    } else if ([self.view.superview isKindOfClass:[WSIUIView class]]) {
        [(WSIUIView*)self.view.superview removeSubController:self];
    } else {
        [self.view removeFromSuperview];
    }
    
    if (__need_manual_appear) {
        [self viewDidDisappear:NO];
    }
    
    superController = nil;
    
    [self release];
}

# pragma mark common

- (void)viewWillAppear:(BOOL)animated {
    //trace_msg(@"view will appear.");
    
    if (isAppeared)
        return;
    
    // call child.
    for (UIViewController* each in subControllers)
        [each viewWillAppear:animated];
    
    // call super.
    [super viewWillAppear:animated];
    
    // signal.
    [self emit:kSignalViewAppearing];
}

- (void)viewDidAppear:(BOOL)animated {
    //trace_msg(@"view did appeared");
    
    if (isAppeared)
        return;
    isAppeared = YES;
    
    // redirect.
    [self viewIsAppearing:animated];
    
    // subcontroller.
    for (UIViewController* each in subControllers)
        [each viewDidAppear:animated];
    
    // subcontroller of view.
    UIView* view = self.view;
    if ([view isKindOfClass:[WSIUIView class]]) {
        WSIUIView* wsiview = (WSIUIView*)view;
        for (UIViewController* each in wsiview.subControllers)
            [each viewDidAppear:animated];
    }
    
    // call super.
    [super viewDidAppear:animated];
    
    // signal.
    [self emit:kSignalViewAppear];
    
    // wait for remote event.
    if (WSI_SUPPORT_MULTITASKS) {
        if ([self find_signal:kSignalRemoteControlEvent].count) {
            [[UIApplication sharedApplication] beginReceivingRemoteControlEvents];
            [self becomeFirstResponder];
        }
    }
}

- (void)viewIsAppearing:(BOOL)animated {
    PASS;
}

- (void)viewWillDisappear:(BOOL)animated {
    //trace_msg(@"view will disappear");
    
    if (!isAppeared)
        return;
    
    // subcontroller.
    for (UIViewController* each in subControllers)
        [each viewWillDisappear:animated];
    
    // subcontroller of view.
    UIView* view = self.view;
    if ([view isKindOfClass:[WSIUIView class]]) {
        WSIUIView* wsiview = (WSIUIView*)view;
        for (UIViewController* each in wsiview.subControllers)
            [each viewWillDisappear:animated];
    }
    
    // call super
    [super viewWillDisappear:animated];
    
    // emit signal.
    [self emit:kSignalViewDisappearing];
    
    // cancel wait for remote event.
    if (WSI_SUPPORT_MULTITASKS) {
        if ([self find_signal:kSignalRemoteControlEvent].count) {
            [[UIApplication sharedApplication] endReceivingRemoteControlEvents];
            [self resignFirstResponder];
        }
    }
}

- (void)viewDidDisappear:(BOOL)animated {
    //trace_msg(@"view did disappeared");
    
    if (!isAppeared)
        return;
    isAppeared = NO;
    
    // redirect.
    [self viewIsDisappearing:animated];
    
    // subcontroller.
    for (UIViewController* each in subControllers)
        [each viewDidDisappear:animated];
    
    // subcontroller of view.
    UIView* view = self.view;
    if ([view isKindOfClass:[WSIUIView class]]) {
        WSIUIView* wsiview = (WSIUIView*)view;
        for (UIViewController* each in wsiview.subControllers)
            [each viewDidDisappear:animated];
    }
    
    // call super.
    [super viewDidDisappear:animated];
    
    // signal.
    [self emit:kSignalViewDisappear];
}

- (void)viewIsDisappearing:(BOOL)animated {
    PASS;
}

- (void)viewDidLoad {
    WSI_AUTORELEASEPOOL_BEGIN;
    
    // set view object for attach view without init a view.
    _viewobj = self.view;
    
    // super.
    [super viewDidLoad];    
    
    // call wsi loading routine.
    //[self viewIsLoading];
    [self performSelectorOnMainThread:@selector(viewIsLoading) withObject:nil waitUntilDone:YES];
    
    // check orient.
    if (isNeedAdjustForRotation == NO) {
        if ([self conformsToProtocol:@protocol(UIViewControllerRotation)])
            [self performSelector:@selector(__act_device_rotated)];
        else
            [self performSelector:@selector(__act_device_rotated_pure)];
    }
    
    WSI_AUTORELEASEPOOL_END;
}
     
- (void)viewIsLoading {
    PASS;
}

- (void)viewDidUnload {
    // did unload.
    [super viewDidUnload];
    
    // free view.
    self.view = nil;
    
    // is unloading.
    [self viewIsUnloading];
}

- (void)viewIsUnloading {
    PASS;
}

- (void)dismissModalViewController {
    [self dismissModalViewControllerAnimated:NO];
}

- (void)dismissModalViewControllerAnimated {
    [self dismissModalViewControllerAnimated:YES];
}

- (void)didReceiveMemoryWarning {
    PASS;
}

# pragma mark rotation.

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    BOOL ret = UIOrientationEnableCheck(_orientationEnable, toInterfaceOrientation);
    return ret;
}

# pragma mark motion

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    if (motion == UIEventSubtypeMotionShake) {
        [self emit:kSignalDeviceShaked];
        [[WSIUIObject shared] emit:kSignalDeviceShaked result:self];
    }
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    PASS;
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
    PASS;
}

# pragma mark remove control event

- (void)remoteControlReceivedWithEvent:(UIEvent *)event {
    [self emit:kSignalRemoteControlEvent result:event];
    [[WSIUIObject shared] emit:kSignalRemoteControlEvent result:event];
}

- (BOOL)canBecomeFirstResponder {
    WSISignal* signal = [self find_signal:kSignalDeviceShaked];
    if (signal.count)
        return YES;
    
    if (WSI_SUPPORT_MULTITASKS) {
        signal = [self find_signal:kSignalRemoteControlEvent];
        if (signal.count)
            return YES;
    }
    
    return NO;
}

# pragma mark modal

- (void)presentModalViewController:(UIViewController *)modalViewController animated:(BOOL)animated {
    // if support attach mech, the bind self.
    if (modalViewController.supportAttach) {
        [modalViewController attachSet:kViewControllerModalParentController obj:self];
    }
    
    // present.
    [super presentModalViewController:modalViewController animated:animated];
}

@end

BOOL UIOrientationEnableCheck(UIOrientationEnable orientationEnable, UIInterfaceOrientation toInterfaceOrientation) {
    BOOL ret = YES;
    switch (toInterfaceOrientation) {
        case UIInterfaceOrientationPortrait:
            ret = MASK_CHECK(UIOrientationPortraitEnable, orientationEnable);
            break;
        case UIInterfaceOrientationPortraitUpsideDown:
            ret = MASK_CHECK(UIOrientationPortraitUpsideDownEnable, orientationEnable);
            break;
        case UIInterfaceOrientationLandscapeLeft:
            ret = MASK_CHECK(UIOrientationLandscapeLeftEnable, orientationEnable);
            break;
        case UIInterfaceOrientationLandscapeRight:
            ret = MASK_CHECK(UIOrientationLandscapeRightEnable, orientationEnable);
            break;
    }
    return ret;
}

@implementation WSIUIViewControllerIB

@end

@implementation WSIUIViewController

@dynamic wsiview;

- (WSIUIView*)wsiview {
    UIView *view = self.view;
# ifdef WSI_VERBOSE_VERBOSE
    if ([view isKindOfClass:[WSIUIView class]]) {        
        trace_msg(@"attention: this view is not a WSIUIView!");
    }
# endif
    return (WSIUIView *)view;
}

@end

@implementation WSIUIHtmlController

@dynamic htmlView;

- (void)loadView {    
    WSIUIWebView* web = [[WSIUIWebView alloc] initWithZero];
    self.view = web;
    [web release];
    
    web.scrollView.bounces = NO;
    web.scrollView.bouncesZoom = NO;
    web.dataDetectorTypes = UIDataDetectorTypeNone;
}

- (WSIUIWebView*)htmlView {
    return (WSIUIWebView*)self.view;
}

@end

@implementation _cxx_uiviewcontroller_wrapper

@synthesize _cxxobj;

- (void)dealloc {
    if (_cxxobj)
        _cxxobj->destroy();
    [super dealloc];
}

- (void)loadView {
    UIView* view = _cxxobj->load_view();
    if (view == nil)
    {
        [super loadView];
        return;
    }
    
    self.view = view;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if (_cxxobj)
        _cxxobj->view_loaded();
}

- (void)viewDidUnload {
    [super viewDidUnload];
    
    if (_cxxobj)
        _cxxobj->free_view();
}

- (void*)object {
    return _cxxobj->cxxobject();
}

- (void)viewController:(WSIUIViewController*)ctlr orientation:(UIInterfaceOrientation)orientation {
    _cxxobj->orientation(orientation);
}

- (void)viewControllerTheme:(WSIUIViewController *)ctlr changeTheme:(UITheme *)theme {
    _cxxobj->theme(::wsi::ui::Theme(theme));
}

@end

@implementation _cxx_simplecontroller_wrapper

@synthesize _cxxobj;

- (void)dealloc {
    if (_cxxobj)
        _cxxobj->destroy();
    [super dealloc];
}

- (void*)object {
    return _cxxobj->cxxobject();
}

@end

WSI_END_OBJC
