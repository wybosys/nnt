
# import "AppDelegate.h"
# import "NaviController.h"

@implementation WSIAppDelegate

- (void)load {
    NaviController* ctlr = [[NaviController alloc] init];
    ctlr.orientationEnable = UIOrientationEnableAll;
    ctlr.view.backgroundColor = [UIColor whiteColor];
    
    WSIUINavigationController* navi = [[WSIUINavigationController alloc] initWithRootViewController:ctlr];
    
    self.rootViewController = navi;
    
    [navi release];
    [ctlr release];
}

@end

WSIDEBUG_THEME_IMPL;
