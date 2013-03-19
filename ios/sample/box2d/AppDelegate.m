
# import "WSIFoundation.h"
# import "AppDelegate.h"
# import "mainController.h"

@implementation AppDelegate

- (void)load:(UIApplication *)application options:(NSDictionary *)launchOptions {
    MainController* ctlr = [[MainController alloc] init];
    self.rootViewController = ctlr;
    [ctlr release];
}

@end

WSIDEBUG_THEME_IMPL;