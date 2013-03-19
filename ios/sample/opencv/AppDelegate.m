
# import "Foundation+NNT.h"
# import "AppDelegate.h"
# import "MainController.h"

@implementation AppDelegate

- (void)load {
    MainController* ctlr = [[MainController alloc] init];
    self.window.rootViewController = ctlr;
    [ctlr release];
}

@end

WSIDEBUG_THEME_IMPL;
