
# import "WSIFoundation.h"
# import "AppDelegate.h"
# import "MainController.h"

@implementation WSIAppDelegate

- (void)load:(UIApplication *)application options:(NSDictionary *)launchOptions {    
    [self enableFileCache];
    
    MainController* ctlr = [[MainController alloc] init];
    self.rootViewController = ctlr;
    [ctlr release];
}

@end
