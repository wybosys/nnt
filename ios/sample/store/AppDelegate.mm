
# import "Foundation+NNT.h"
# import "AppDelegate.h"
# import "MainController.h"

@implementation AppDelegate

- (void)load {
    MainController* ctlr = [[MainController alloc] init];
    self.rootViewController = ctlr;
    [ctlr release];
}

@end
