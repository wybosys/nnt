
# import "WSIFoundation.h"
# import "custometabbarAppDelegate.h"
# import "TestView.h"

@implementation custometabbarAppDelegate

@dynamic window;

- (void)load {
      //TestController* ctlr_root = [[TestController alloc] init];
      TestView *ctlr_root = [[TestView alloc] init];
      self.window.rootViewController = ctlr_root;
      [ctlr_root release];
}

@end
