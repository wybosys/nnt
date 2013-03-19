
# import "Core.h"
# import "UITabBarContainerController.h"

WSI_BEGIN_OBJC

@interface UITabBarContainerController ()

- (void)loadTabs;

@property (nonatomic, retain) UIImageView *selectedTab;

@end

@implementation UITabBarContainerController

@synthesize viewControllers, tabBar, selectedTab, selectedViewController, selectedIndex;

- (id)init {
    self = [super init];
        
    tabBar = [[WSIUITabBar alloc] initWithZero];
    tabBar.delegate = self;
    
    return self;
}

- (void)dealloc {
    zero_release(viewControllers);
    zero_release(tabBar);
    zero_release(selectedViewController);
    
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalSelectChanged)
WSIEVENT_END

- (void)loadView {
    self.view = tabBar;
}

- (void)tabBar:(WSIUITabBar *)aTabBar didSelectTabAtIndex:(NSInteger)index {
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
	UIViewController *oldVC = selectedViewController;
	if (selectedViewController == vc)
        return;
    
    [selectedViewController release];
    selectedViewController = [vc retain];
    [oldVC viewWillDisappear:NO];
    [selectedViewController viewWillAppear:NO];
    [oldVC viewDidDisappear:NO];
    [selectedViewController viewDidAppear:NO];
    
    [self.tabBar setSelectedTab:[self.tabBar.tabs objectAtIndex:self.selectedIndex] animated:(oldVC != nil)];
    
    [self emit:kSignalSelectChanged result:[NSPair pairWith:vc second:oldVC]];                                            
}

- (void)viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
	[self.selectedViewController viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated {
	[super viewDidAppear:animated];
	[self.selectedViewController viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
	[self.selectedViewController viewWillDisappear:animated];	
}

- (void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
	[self.selectedViewController viewDidDisappear:animated];
}

- (NSUInteger)selectedIndex {
	return [self.viewControllers indexOfObject:self.selectedViewController];
}

- (void)setSelectedIndex:(NSUInteger)aSelectedIndex {
	if (self.viewControllers.count > aSelectedIndex)
		self.selectedViewController = [self.viewControllers objectAtIndex:aSelectedIndex];
}

- (void)loadTabs {
    if ([self.viewControllers count] == 0)
        return;
    
	NSMutableArray *tabs = [NSMutableArray arrayWithCapacity:self.viewControllers.count];
	for (UIViewController *vc in self.viewControllers) {
        WSIUITabBarItem *item = [WSIUITabBarItem alloc];
        
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
    
    //if (self.selectedIndex == NSNotFound)
    //    self.selectedIndex = 0;
    
	//[self.tabBar setSelectedTab:[self.tabBar.tabs objectAtIndex:self.selectedIndex] animated:NO];
}

- (void)viewDidUnload {
	self.tabBar = nil;
	self.selectedTab = nil;
}

- (void)setViewControllers:(NSArray *)array {
	if (array != viewControllers) {
		[viewControllers release];
		viewControllers = [array retain];
		
		if (viewControllers != nil) {
			[self loadTabs];
		}
	}
	
	//self.selectedIndex = 0;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
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

@end

WSI_END_OBJC