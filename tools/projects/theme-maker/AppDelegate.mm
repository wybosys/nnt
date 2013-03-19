
# import "AppDelegate.h"
# import "TMMainController.h"

@implementation AppDelegate

- (void)load {
    wsiapp::MainController* ctlr = wsiapp::MainController::New();
    self.rootViewController = *ctlr;
    ctlr->Release();
}

@end
