
# import "Foundation+NNT.h"
# import "AppDelegate.h"

//# import "MainController.h"
# import "MapabcController.h"
# import "MamapController.h"

@implementation WSIAppDelegate

- (void)load {
    //MainController* ctlr = [[MainController alloc] init];
    //MapabcController* ctlr = [[MapabcController alloc] init];
    MamapController* ctlr = [[MamapController alloc] init];
    
    ctlr.orientationEnable = UIOrientationEnableAll;    
    self.rootViewController = ctlr;
    [ctlr release];
}

@end
