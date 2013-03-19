
# import "Core.h"
# import "UINavigationController+NNT.h"
# import "UIView+NNT.h"
# import "CoreGraphic+NNT.h"
# import "UIViewController+NNT.h"
# import "UIButton+NNT.h"
# import "UIBarButtonItem+NNT.h"
# import "UITabBarController+NNT.h"
# import "UITabBar+NNT.h"
# import "App.h"
# import "UIGesture+NNT.h"

NNT_BEGIN_OBJC

@implementation UINavigationController (NNT)

- (NSUInteger)indexOfViewController:(UIViewController *)ctlr {
    return [self.viewControllers indexOfObject:ctlr];
}

- (UIViewController*)viewControllerAtIndex:(NSUInteger)idx {
    return [self.viewControllers objectAtIndex:idx];
}

- (UIViewController*)preViewController:(UIViewController *)ctlr {
    NSUInteger idx = [self indexOfViewController:ctlr];
    if (idx == NSNotFound)
        return nil;
    if (idx != 0)
        return [self viewControllerAtIndex:idx - 1];
    return nil;
}

- (UIViewController*)nextViewController:(UIViewController *)ctlr {
    NSUInteger idx = [self indexOfViewController:ctlr];
    if (idx == NSNotFound)
        return nil;
    if (idx + 1 == [self countOfViewControllers])
        return nil;
    return [self viewControllerAtIndex:idx + 1];
}

- (NSUInteger)countOfViewControllers {
    return [self.viewControllers count];
}

- (void)addTopRightItems:(NSArray*)items {
    UINavigationItem* top = self.navigationBar.topItem;
    if ([top respondsToSelector:@selector(rightBarButtonItems)]) {
        NSArray* arr = [items reverse];
        top.rightBarButtonItems = arr;
        return;
    }        
    
    NNTUIView* viewitem = [[NNTUIView alloc] initWithZero];
    uint height = self.navigationBar.bounds.size.height * .7f;
    CGPoint pt = CGPointZero;
    for (UIBarButtonItem* each in items) {
        if (each.image) {
            CGSize sz_img = each.image.size;
            CGRect fm = CGRectMake(pt.x + 5, pt.y, sz_img.width + 10, height);
            
            UIClearButton* btn = [[UIClearButton alloc] initWithZero];
            btn.backgroundFill = [WCGFill fillWithImage:[WCGImage imageWithCGImage:each.image.CGImage]];
            btn.frame = fm;
            [viewitem addSubview:btn];
            [btn connect:kSignalButtonClicked sig:kSignalButtonClicked obj:each];
            [btn storeSet:@"item" obj:each];
            [btn release];
            
            pt.x += fm.size.width + 5;
        } else if (each.customView) {
            UIView* view = each.customView;
            
            CGSize sz_img = view.frame.size;
            CGRect fm = CGRectMake(pt.x + 5, pt.y, sz_img.width + 10, height);            
            view.frame = fm;
            [viewitem addSubview:view];
            [view connect:kSignalButtonClicked sig:kSignalButtonClicked obj:each];
            [view storeSet:@"item" obj:each];
            
            pt.x += fm.size.width + 5;
        } else {
            UIBevelButton* btn = [[UIBevelButton alloc] initWithZero];
            btn.text = each.title;
            btn.titleLabel.font = [UIFont boldSystemFontOfSize:12.5];
            
            CGSize sz_img = [btn textSize];
            CGRect fm = CGRectMake(pt.x + 5, pt.y, sz_img.width + 10, height);
            btn.frame = fm;
            [viewitem addSubview:btn];
            [btn connect:kSignalButtonClicked sig:kSignalButtonClicked obj:each];
            [btn storeSet:@"item" obj:each];
            [btn release];
            
            pt.x += fm.size.width + 5;
        }
    }
    
    viewitem.frame = CGRectMakeWH(pt.x, height);
    UIBarButtonItem* rightitem = [[UIBarButtonItem alloc] initWithCustomView:viewitem];
    self.navigationBar.topItem.rightBarButtonItem = rightitem;
    [viewitem release];
    [rightitem release];
}

- (void)addTopLeftItems:(NSArray*)items {
    UINavigationItem* top = self.navigationBar.topItem;
    if ([top respondsToSelector:@selector(leftBarButtonItems)]) {
        NSArray* arr = [items reverse];
        top.leftBarButtonItems = arr;
        return;
    }
    
    NNTUIView* viewitem = [[NNTUIView alloc] initWithZero];
    uint height = 36;
    CGPoint pt = CGPointZero;
    for (UIBarButtonItem* each in items) {
        if (each.image) {
            CGSize sz_img = each.image.size;
            CGRect fm = CGRectMake(pt.x + 5, pt.y, sz_img.width + 10, height);
            
            UIClearButton* btn = [[UIClearButton alloc] initWithZero];
            btn.backgroundFill = [WCGFill fillWithImage:[WCGImage imageWithCGImage:each.image.CGImage]];
            btn.frame = fm;
            [viewitem addSubview:btn];
            [btn connect:kSignalButtonClicked sig:kSignalButtonClicked obj:each];
            [btn storeSet:@"item" obj:each];
            [btn release];
            
            pt.x += fm.size.width + 5;
        } else if (each.customView) {
            UIView* view = each.customView;
            
            CGSize sz_img = view.frame.size;
            CGRect fm = CGRectMake(pt.x + 5, pt.y, sz_img.width + 10, height);
            view.frame = fm;
            [viewitem addSubview:view];
            [view connect:kSignalButtonClicked sig:kSignalButtonClicked obj:each];
            [view storeSet:@"item" obj:each];
            
            pt.x += fm.size.width + 5;
        }
    }
    
    viewitem.frame = CGRectMakeWH(pt.x, height);
    UIBarButtonItem* rightitem = [[UIBarButtonItem alloc] initWithCustomView:viewitem];
    self.navigationBar.topItem.leftBarButtonItem = rightitem;
    [viewitem release];
    [rightitem release];
}

@end

NNTIMPL_CATEGORY(UINavigationController, NNT);

@interface NNTUINavigationControllerBase ()

- (void)syncOtherControler;

@end

@interface appear_thd : NSObject

@property (nonatomic, retain) UIViewController *appear;
@property (nonatomic, assign) bool animated;

@end

@implementation appear_thd

@synthesize appear, animated;

- (void)dealloc {
    [appear release];
    [super dealloc];
}

@end

@implementation NNTUINavigationControllerBase

@synthesize showHomeBack = _showHomeBack, homeBack = _homeBack, titleHomeBack = _titleHomeBack, navigationBarHiddenByController = _navigationBarHiddenByController;
@dynamic rootViewController;
@synthesize titleImage = _titleImage, orientationEnable = _orientationEnable;
@synthesize topbarBackgroundFill = _topbarBackgroundFill;

NNTOBJECT_IMPL;

- (id)initWithRootViewController:(NNTUIViewController *)__rootViewController {
    self = [super initWithRootViewController:__rootViewController];
    
    self.navigationBarHiddenByController = NO;
    self.orientationEnable = 0;
    
    // avoid the battery bar.
    self.view.frame = CGRectZero;
    
    return self;
}

- (id)init {
    self = [super init];        
    
    self.navigationBarHiddenByController = NO;
    self.orientationEnable = 0;
    
    // avoid the battery bar. 
    self.view.frame = CGRectZero;        
    
    return self;
}

- (void)dealloc {
    zero_release(_homeBack);
    zero_release(_titleImage);
    zero_release(_topbarBackgroundFill);
    
    [super dealloc];
}

- (NNTUIViewController*)rootViewController {
    return self.viewControllers.first;
}

NNTIMPL_VIEWCONTROLLER;

- (void)viewIsLoading {
    PASS;
}

- (void)viewIsUnloading {
    PASS;
}

- (void)viewIsAppearing:(BOOL)animated {
    PASS;
}

- (void)viewIsDisappearing:(BOOL)animated {
    PASS;
}

- (void)__thd_appear_switch:(appear_thd*)parm {
    [parm.appear viewDidAppear:parm.animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    if (_orientationEnable == 0) {
        BOOL sup = [super shouldAutorotateToInterfaceOrientation:interfaceOrientation];
        return sup;
    }
    return UIOrientationEnableCheck(_orientationEnable, interfaceOrientation);
}

- (void)pushViewController:(NNTUIViewController *)viewController animated:(BOOL)animated {
    // is is equal to current.
    if (viewController == self.visibleViewController)
        return;
    
    // if is wsi controller, assign navigation controller.
    if ([viewController isKindOfClass:[NNTUIViewController class]])
        viewController.navigationController = self;
    
    // if not auto appearing. create view.
    //if (__need_manual_appear)
    // force load view.
    [viewController view];
    
    // get old.
    UIViewController* old_select = [self.visibleViewController retain];
    
    // prepare for appear.
    {
        [old_select viewWillDisappear:animated];
        [viewController viewWillAppear:animated];
    }
    
    // push.
    [super pushViewController:viewController animated:animated];
    
    // appear.
    {
        [old_select viewDidDisappear:animated];
        
        if (__need_manual_appear) {
            appear_thd* parm = [[appear_thd alloc] init];
            parm.appear = viewController;
            parm.animated = animated;
            [self performSelectorOnMainThread:@selector(__thd_appear_switch:) withObject:parm waitUntilDone:NO];
            [parm release];
        }
    }
    zero_release(old_select);
    
    // process home back show.
    if (_showHomeBack) {
        [self showHomeBack:YES animated:animated];
    }
            
    // update.
    [self syncOtherControler];
    
    // bind event.
    if ([viewController hasSignal:kSignalTitleChanged]) {
        [viewController connect:kSignalTitleChanged sel:@selector(__act_ctlrtitle_changed:) obj:self];
    }
}

- (void)__act_ctlrtitle_changed:(NNTEventObj*)evt {
    NSString* title = (NSString*)evt.result;
    self.navigationBar.topItem.title = title;
}

- (UIViewController*)popViewControllerAnimated:(BOOL)animated {
    if (self.rootViewController == self.visibleViewController)
        return nil;
    
    UIViewController *old_select = [self.visibleViewController retain];
    
    UIViewController *pre_select = [self preViewController:old_select];
        
    // prepear.
    {
        [old_select viewWillDisappear:animated];
        [pre_select viewWillAppear:animated];
    }
    
    UIViewController *ret = [super popViewControllerAnimated:animated];
    
    // appear.
    {
        [old_select viewDidDisappear:animated];
        
        if (__need_manual_appear) {
            appear_thd* parm = [[appear_thd alloc] init];
            parm.appear = pre_select;
            parm.animated = animated;
            [self performSelectorOnMainThread:@selector(__thd_appear_switch:) withObject:parm waitUntilDone:NO];
            [parm release];
        }
    }
    zero_release(old_select);
    
    if (_showHomeBack) {
        [self showHomeBack:NO animated:animated];
    }
        
    [self syncOtherControler];
    
    return ret;
}

- (NSArray*)popToViewController:(NNTUIViewController *)viewController animated:(BOOL)animated {
    if (viewController == self.visibleViewController)
        return nil;
    
    UIViewController *old_select = [self.visibleViewController retain];
    
    // prepare.
    {
        [old_select viewWillDisappear:animated];
        [viewController viewWillAppear:animated];
    }
    
    NSArray *ret = [super popToViewController:viewController animated:animated];
    
    // appear.
    {
        [old_select viewDidDisappear:animated];
        
        if (__need_manual_appear) {
            appear_thd* parm = [[appear_thd alloc] init];
            parm.appear = viewController;
            parm.animated = animated;
            [self performSelectorOnMainThread:@selector(__thd_appear_switch:) withObject:parm waitUntilDone:NO];
            [parm release];
        }
    }
    zero_release(old_select);
    
    if (_showHomeBack) {
        [self showHomeBack:NO animated:animated];
    }
    
    [self syncOtherControler];
    
    return ret;
}

- (NSArray*)popToRootViewControllerAnimated:(BOOL)animated {
    if (self.rootViewController == self.visibleViewController)
        return nil;
    
    UIViewController *old_select = [self.visibleViewController retain];
    
    // prepare.
    {
        [old_select viewWillDisappear:animated];
        [self.rootViewController viewWillAppear:animated];
    }
    
    NSArray *ret = [super popToRootViewControllerAnimated:animated];
    
    // appear.
    {
        [old_select viewDidDisappear:animated];
        
        if (__need_manual_appear) {
            appear_thd* parm = [[appear_thd alloc] init];
            parm.appear = self.rootViewController;
            parm.animated = animated;
            [self performSelectorOnMainThread:@selector(__thd_appear_switch:) withObject:parm waitUntilDone:NO];
            [parm release];
        }
    }
    zero_release(old_select);
    
    if (_showHomeBack) {
        for (NNTUIButton *button in self.homeBack) {
            [button removeFromSuperview];
        }
        safe_release(_homeBack);
    }
    
    [self syncOtherControler];
    
    return ret;
}

- (void)setShowHomeBack:(BOOL)showHomeBack {
    _showHomeBack = showHomeBack;
}

- (void)showHomeBack:(BOOL)vis animated:(BOOL)animated {
    //if (self.navigationBarHidden == YES)
    //    return;
    
    if (vis) {
        
        if (_homeBack == nil)
            _homeBack = [NSMutableArray new];
        NSMutableArray *btns = (NSMutableArray*)_homeBack;
        
        // invisible last.
        if ([btns count]) {
            NNTUIButton *button = [btns objectAtIndex:[btns count] - 1];
            button.hidden = YES;
        }
        
        if (_titleHomeBack == nil)
            _titleHomeBack = @"home";
                        
        NNTUIBarButtonItem *btn = [[NNTUIBarButtonItem alloc] initWithTitle:_titleHomeBack
                                                                      style:UIBarButtonItemStylePlain 
                                                                     target:self 
                                                                     action:@selector(act_backhome:)];
        NNTUIButton *button = (NNTUIButton*)btn.customView;
        [btns addObject:button];
        
        button.layer.opacity = 0.f;
        
        CGRect const rc = self.navigationBar.bounds;
        CGRect rc_btn;
        
        UIViewController *pre = [self preViewController:self.visibleViewController];
        NSString *pre_title = pre.navigationItem.title;
        UIFont *font = button.titleLabel.font;
        CGSize sz_pre = [pre_title sizeWithFont:font];
        rc_btn.origin.x = rc.origin.x + sz_pre.width + 120;
        rc_btn.origin.y = rc.origin.y + 5;
        rc_btn.size = button.frame.size;
        rc_btn.size.height += 6;
        
        button.frame = rc_btn;
        [self.navigationBar addSubview:button];
        [self.navigationBar sendSubviewToBack:button];
        [btn release];
        
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
        
        rc_btn.origin.x = rc.origin.x + sz_pre.width + 20;
        button.frame = rc_btn;
        button.layer.opacity = 1.f;
        
        [UIView commitAnimations];
        
    } else {
        NSMutableArray *btns = (NSMutableArray*)_homeBack;
        
        if (btns && [btns count]) {            
            NNTUIButton *button = [btns objectAtIndex:[btns count] - 1];
            [button removeFromSuperview];
            [btns removeObjectAtIndex:[_homeBack count] - 1];
        }
        
        // visible pre
        if ([btns count]) {
            NNTUIButton *button = [btns objectAtIndex:[btns count] - 1];        
            button.hidden = NO;
        }
                
    }
}

- (void)act_backhome:(id)sender {
    [self popToRootViewControllerAnimated:YES];
}

NSString* kNavigationControllerBarVisible = @"::wsi::ui::navigationcontroller::controller::bar::visible";

- (void)syncOtherControler {
    UIViewController *selected = self.visibleViewController;
    
    if (_navigationBarHiddenByController) {
        __gs_debug_attachstore_error_enable_set(NO);
        NSNumber *num = [selected attachFind:kNavigationControllerBarVisible];
        __gs_debug_attachstore_error_enable_set(YES);
        
        BOOL show = YES;
        if (num) {
            show = [num intValue] != 0;
        }
        self.navigationBarHidden = !show;        
    }
    
    NNTUITabBarController *tabBar = [self attachFind:kTabBarController];
    if (tabBar) {                
        CGRect rc = tabBar.tabBar.frame;
        if (selected.hidesBottomBarWhenPushed) { 
            
            [UIView beginAnimations:nil context:nil];        
            [UIView setAnimationDuration:.25f];
            [UIView setAnimationDelegate:self];
            [UIView setAnimationDidStopSelector:@selector(act_hide_tabbar:)];
            
            rc.origin.x -= rc.size.width;
            tabBar.tabBar.frame = rc; 
            
            [UIView commitAnimations];
            
        } else {
            if (tabBar.tabBar.hidden) {
                tabBar.tabBar.hidden = NO;                
                
                rc.origin.x += rc.size.width;                
                tabBar.tabBar.frame = rc; 
            }
        }
                                                              
        [tabBar.view setNeedsLayout];
    }
    
    // bar.
    [self.navigationBar updateTabBar];
}

- (void)act_hide_tabbar:(id)obj {
    UIViewController *selected = self.visibleViewController;
    NNTUITabBarController *tabBar = [self attachFind:kTabBarController];
    
    if (selected.hidesBottomBarWhenPushed) {
        tabBar.tabBar.hidden = YES;        
    } else {
        tabBar.tabBar.hidden = NO;
    }
    
    [tabBar.view setNeedsLayout];
}

- (void)setTopbarBackgroundFill:(WCGFill*)fill {
    if (_topbarBackgroundFill == fill)
        return;
    
    // set.
    [NSObject refobjSet:&_topbarBackgroundFill ref:fill];
    
    // add layer.
    UINavigationBar* bar = self.navigationBar;
        
    uint idx = 0;
    bool found = false;
    for (CALayer* each in bar.layer.sublayers) {
        if ([each isKindOfClass:[CANavigationBarFillLayer class]]) {
            found = true;
            break;
        }
        ++idx;
    }
    
    if (found == false) {
        CANavigationBarFillLayer* layer = [[CANavigationBarFillLayer alloc] init];
        layer.fill = fill;
        [bar.layer addSublayer:layer];
        [layer release];
    } else {
        CANavigationBarFillLayer* layer = (CANavigationBarFillLayer*)[bar.layer.sublayers objectAtIndex:idx];
        layer.fill = fill;
    }
    
    [bar updateTabBar];
}

@end

@implementation NNTUINavigationController

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (__need_manual_appear)
        [self.visibleViewController viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    if (__need_manual_appear)
        [self.visibleViewController viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    if (__need_manual_appear)
        [self.visibleViewController viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    if (__need_manual_appear)
        [self.visibleViewController viewDidDisappear:animated];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIView* view = self.view;
    
    // install gesture.
    NNTUISwipeGestureRecognizer* recognizer = [[NNTUISwipeGestureRecognizer alloc] init];
    recognizer.numberOfTouchesRequired = 1;
    recognizer.direction = UISwipeGestureRecognizerDirectionRight;
    [recognizer connect:kSignalGestureActive sel:@selector(_act_gesture_swipe_left) obj:self];
    [view addGestureRecognizer:recognizer];
    safe_release(recognizer);
}

- (void)_act_gesture_swipe_left {
    if (self.visibleViewController != self.rootViewController)
        [self popViewControllerAnimated:YES];
}

@end

_CXXCONTROLLER_IMPL(NNTUINavigationController);

NNT_END_OBJC
