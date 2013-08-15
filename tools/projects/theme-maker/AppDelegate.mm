
# import "AppDelegate.h"
# import "TMMainController.h"

NNT_USINGNAMESPACE;

@implementation AppDelegate

- (void)load {
    ::nntapp::MainController* ctlr = ::nntapp::MainController::New();
    self.rootViewController = *ctlr;
    ctlr->drop();
}

@end
