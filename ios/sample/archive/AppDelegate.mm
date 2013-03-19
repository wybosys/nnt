
# include "Foundation+NNT.h"
# import "AppDelegate.h"
# include "MainController.h"

@implementation AppDelegate

- (void)load {
    ::nntapp::MainController* ctlr = ::nntapp::MainController::New();
    self.rootViewController = *ctlr;
    ctlr->Release();
}

@end
