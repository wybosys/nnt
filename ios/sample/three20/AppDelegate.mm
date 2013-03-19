
# import "WSIFoundation.h"
# import "AppDelegate.h"
# import "MainController.h"

@implementation AppDelegate

- (void)load {
    static wsiapp::MainController ctlr_main;
    self.rootViewController = ctlr_main;
}

@end
