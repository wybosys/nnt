
# import "Foundation+NNT.h"
# import "mustacheAppDelegate.h"
# import "mustacheViewController.h"

@implementation mustacheAppDelegate

@synthesize viewController = _viewController;

- (void)load {
    self.rootViewController = self.viewController;
}

- (void)dealloc {
    [_viewController release];
    [super dealloc];
}

@end
