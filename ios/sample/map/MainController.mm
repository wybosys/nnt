
# import "Foundation+NNT.h"
# import "MainController.h"
# import "UIMapView.h"

NNTAPP_BEGIN_OBJC

@implementation MainController

- (void)loadView {
    UIMapView* view = [[UIMapView alloc] initWithZero];
    self.view = view;
    [view release];
}

@end

NNTAPP_END_OBJC