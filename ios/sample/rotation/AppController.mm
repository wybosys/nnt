
# import "Foundation+NNT.h"
# import "AppController.h"
# import "AppView.h"

WSI_BEGIN_OBJC

@implementation AppController

- (void)loadView {
    AppView* view = [[AppView alloc] initWithZero];
    self.view = view;
    safe_release(view);
}

- (void)viewController:(WSIUIViewController *)ctlr orientation:(UIInterfaceOrientation)orientation {
    switch (orientation)
    {
        case UIInterfaceOrientationPortrait: trace_msg(@"controller's orientation: portrait."); break;
        case UIInterfaceOrientationPortraitUpsideDown: trace_msg(@"controller's orientation: portrait upsidedown."); break;
        case UIInterfaceOrientationLandscapeLeft: trace_msg(@"controller's orientation: landscape left."); break;
        case UIInterfaceOrientationLandscapeRight: trace_msg(@"controller's orientation: landscape right."); break;
    }
}

@end

WSI_END_OBJC