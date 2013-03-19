
# import "Foundation+NNT.h"
# import "AppDelegate.h"
# import "MainController.h"

@implementation AppDelegate

- (void)load {
    static nntapp::MainController ctlr_main;
    self.rootViewController = ctlr_main;
}

@end
