
# import "Foundation+NNT.h"
# import "AppDelegate.h"
# import "AppController.h"
# import "UIViewController+WSI.hpp"

@implementation AppDelegate

- (void)load {
    //AppController* ctlr = [[AppController alloc] init];
    //self.window.rootViewController = ctlr;
    //[ctlr release];
    
    wsi::UIHtmlController<> ctlr(@"index.html");
    self.window.rootViewController = ctlr;
}

@end

WSIDEBUG_THEME_IMPL;