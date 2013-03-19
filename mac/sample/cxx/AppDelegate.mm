
# include "wsi/WSIFoundation.h"
# import "AppDelegate.h"
# include "MainController.h"

@implementation AppDelegate

- (void)load {
    wsiapp::MainController* ctlr = wsiapp::MainController::New();
    self.rootViewController = *ctlr;
    ctlr->Release();
}

@end
