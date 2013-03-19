
# import "WSI/WSIFoundation.h"
# import "AppDelegate.h"
# import "OpenglController.h"

@implementation AppDelegate

- (void)load {        
    OpenglController* ctlr = [[OpenglController alloc] init];
    self.rootViewController = ctlr;
    [ctlr release];
}

@end
