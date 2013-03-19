
# import "WSIFoundation.h"
# import "AppDelegate.h"
# import "MainController.h"

@implementation WSIAppDelegate

- (void)load {
    MainController* ctlr = [[MainController alloc] init];
    self.rootViewController = ctlr;
    [ctlr release];
}

@end
