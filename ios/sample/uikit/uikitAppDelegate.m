
# import "WSIFoundation.h"
# import "uikitAppDelegate.h"
# import "uikitViewController.h"

@implementation uikitAppDelegate

@dynamic window;
@synthesize viewController = _viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return [super application:application didFinishLaunchingWithOptions:launchOptions];
}

- (void)dealloc {
    [_viewController release];
    [super dealloc];
}

@end

WSIDEBUG_THEME_IMPL;