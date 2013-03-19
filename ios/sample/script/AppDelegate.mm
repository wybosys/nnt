
# import "Foundation+NNT.h"
# import "AppDelegate.h"
# import "ScriptController.h"

@implementation WSIAppDelegate

- (void)load:(UIApplication *)application options:(NSDictionary *)launchOptions {
    ScriptController* ctlr = [[ScriptController alloc] init];
    ctlr.orientationEnable = UIOrientationEnableAll;
    self.rootViewController = ctlr;
    [ctlr release];
}

@end
