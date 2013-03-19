
# import "Foundation+NNT.h"
# import "AController.h"

NNTAPP_BEGIN_OBJC

@implementation AView

- (void)layoutSubviews {
    if (self.isLandscape) {
        trace_msg(@"aview is landscape.");
    } else if (self.isPortrait) {
        trace_msg(@"aview is portrait.");
    }
}

@end

@implementation ACtlr

- (void)loadView {
    AView* view = [[AView alloc] initWithZero];
    self.view = view;
    [view release];
    
    view.backgroundColor = [UIColor yellowColor];
}

- (void)viewController:(WSIUIViewController *)ctlr orientation:(UIInterfaceOrientation)orientation {
    trace_msg(@"ACtlr is rotated.");
}

@end

NNTAPP_END_OBJC