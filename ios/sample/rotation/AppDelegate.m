
# import "WSIFoundation.h"
# import "AppDelegate.h"
# import "AppController.h"

@implementation WSIAppDelegate

- (void)load {
    AppController* ctlr = [[AppController alloc] init];
    ctlr.orientationEnable = UIOrientationEnableAll;
    self.rootViewController = ctlr;
    safe_release(ctlr);
}

@end
