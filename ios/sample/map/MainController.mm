
# import "WSIFoundation.h"
# import "MainController.h"
# import "UIMapView.h"

WSIAPP_BEGIN_OBJC

@implementation MainController

- (void)loadView {
    UIMapView* view = [[UIMapView alloc] initWithZero];
    self.view = view;
    [view release];
}

@end

WSIAPP_END_OBJC