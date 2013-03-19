
# import "Core.h"
# import "UITabBarController+NNT.h"
# import "UITabBarView+NNT.h"

NNT_BEGIN_OBJC

NNT_EXTERN bool __need_manual_appear;

real kUITabBarHeight = 44;

@implementation UITabBarController (NNT)

@end

NNTIMPL_CATEGORY(UITabBarController, NNT);

@interface NNTUITabBarController ()

- (void)loadTabs;

@property (nonatomic, retain) UIImageView *selectedTab;

@end

@implementation NNTUITabBarController

@synthesize viewControllers, tabBar, selectedTab, selectedViewController, tabBarView, selectedIndex;

- (id)init {
    self = [super init];                
    
    tabBar = [[NNTUITabBar alloc] initWithFrame:CGRectMake(0, 0, 0, kUITabBarHeight)];    
    tabBar.delegate = self;            
    
    tabBarView = [[NNTUITabBarView alloc] initWithZero];
	tabBarView.backgroundColor = [UIColor clearColor];  
    tabBarView.tabBar = tabBar;   
    
    return self;
}

- (void)dealloc {
    zero_release(viewControllers);
    zero_release(tabBar);
    zero_release(tabBarView);
    
    [super dealloc];
}

- (void)loadView { 
	self.view = tabBarView;
}

- (void)viewDidLoad {        
    [super viewDidLoad];
}

- (void)tabBar:(NNTUITabBar *)aTabBar didSelectTabAtIndex:(NSInteger)index {
	UIViewController *vc = [self.viewControllers objectAtIndex:index];
	if (self.selectedViewController == vc) {
		if ([self.selectedViewController isKindOfClass:[UINavigationController class]]) {
			[(UINavigationController *)self.selectedViewController popToRootViewControllerAnimated:YES];
		}
	} else {
		self.selectedViewController = vc;
	}	
}

- (void)setSelectedViewController:(UIViewController *)vc {
    if (selectedViewController == vc)
        return;
    if (tabBarView == nil)
        return;
    
	UIViewController *oldVC = selectedViewController;
    selectedViewController = vc;
    
    if (__need_manual_appear) {
        [oldVC viewWillDisappear:NO];
        [selectedViewController viewWillAppear:NO];
    }
    
    self.tabBarView.contentView = vc.view;
    
    if (__need_manual_appear) {
        [oldVC viewDidDisappear:NO];
        [selectedViewController viewDidAppear:NO];
    }
    
    [self.tabBar setSelectedTab:[self.tabBar.tabs objectAtIndex:self.selectedIndex] animated:(oldVC != nil)];
    
    // set title.
    self.title = selectedViewController.title;
}

- (void)viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	[self.selectedViewController viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated {
	[super viewDidAppear:animated];
	[self.selectedViewController viewDidAppear:animated];
	visible = YES;
}

- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
	[self.selectedViewController viewWillDisappear:animated];	
}

- (void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
	[self.selectedViewController viewDidDisappear:animated];
	visible = NO;
}

- (NSUInteger)selectedIndex {
	return [self.viewControllers indexOfObject:self.selectedViewController];
}

- (void)setSelectedIndex:(NSUInteger)aSelectedIndex {
	if (self.viewControllers.count > aSelectedIndex)
		self.selectedViewController = [self.viewControllers objectAtIndex:aSelectedIndex];
}

NSString *kTabBarController = @"wsi::ui::TabBarController";
NSString *kTabBarItem = @"wsi::ui::TabBarItem";

- (void)loadTabs {
    if ([self.viewControllers count] == 0)
        return;
    
	NSMutableArray *tabs = [NSMutableArray arrayWithCapacity:self.viewControllers.count];
	for (UIViewController *vc in self.viewControllers) {        
        NNTUITabBarItem *item = [NNTUITabBarItem alloc];
        
        [vc attachSet:kTabBarController obj:self];
        [vc attachSet:kTabBarItem       obj:item];
        
        if (vc.tabBarItem.image) {
            item = [item initWithTitleImage:vc.tabBarItem.image];
        } else if ([[vc icon] isEqualToString:@""]) {
            item = [item initWithTitleImageName:[vc icon]];
        } else {
            item = [item init];
        }
        
        item.title = vc.tabBarItem.title;
        item.normalTitleStyle = tabBar.normalTitleStyle;
        item.selectedTitleStyle = tabBar.selectedTitleStyle;
        item.maskHighlightColor = tabBar.maskHighlightColor;
        item.maskNormalColor = tabBar.maskNormalColor;
        item.selectedColor = tabBar.itemSelectedColor;
        item.selectedEdgeShadow = tabBar.itemSelectedEdgeShadow;
        item.badgeStyle = tabBar.badgeStyle;
        item.badgeLineStyle = tabBar.badgeLineStyle;
        item.badgeColor = tabBar.badgeColor;
        item.enableGraphite = tabBar.enableGraphite;
        
		[tabs addObject:item];
        [item release];
	}
    
	self.tabBar.tabs = tabs;
    
    if (self.selectedIndex == NSNotFound)
        self.selectedIndex = 0;
    
	[self.tabBar setSelectedTab:[self.tabBar.tabs objectAtIndex:self.selectedIndex] animated:NO];
}

- (void)viewDidUnload {
	self.tabBar = nil;
	self.selectedTab = nil;
}

- (void)setViewControllers:(NSArray *)array {    
    [NSObject refobjSet:&viewControllers ref:array];
		
    if (viewControllers != nil) {
        [self loadTabs];
    }
	
	self.selectedIndex = 0;
}

/*
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    if (selectedViewController == nil)
        return [super shouldAutorotateToInterfaceOrientation:toInterfaceOrientation];
	return [self.selectedViewController shouldAutorotateToInterfaceOrientation:toInterfaceOrientation];
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
    [super willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
	[self.selectedViewController willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
}

- (void)willAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
    [super willAnimateFirstHalfOfRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
	[self.selectedViewController willAnimateFirstHalfOfRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation duration:(NSTimeInterval)duration {
    [super willAnimateRotationToInterfaceOrientation:interfaceOrientation duration:duration];
	[self.selectedViewController willAnimateRotationToInterfaceOrientation:interfaceOrientation duration:duration];
}

- (void)willAnimateSecondHalfOfRotationFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation duration:(NSTimeInterval)duration {
    [super willAnimateSecondHalfOfRotationFromInterfaceOrientation:fromInterfaceOrientation duration:duration];
	[self.selectedViewController willAnimateSecondHalfOfRotationFromInterfaceOrientation:fromInterfaceOrientation duration:duration];
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];
	[self.selectedViewController didRotateFromInterfaceOrientation:fromInterfaceOrientation];
}
 */

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ui)

void TabBarController::update()
{
    this->_self.viewControllers = _ctlrs;
}

NNT_END_NS
NNT_END_CXX
