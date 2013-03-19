
# import "AppDelegate.h"
# import "MainController.h"

@implementation WSIAppDelegate

- (void)load {    
    MainController* ctlr = [[MainController alloc] init];
    WSIUINavigationController* navi = [[WSIUINavigationController alloc] initWithRootViewController:ctlr];
    navi.orientationEnable = UIOrientationEnableAll;
    self.rootViewController = navi;
    [ctlr release];
    [navi release];
}

@end
