
# import "WSIFoundation.h"
# import "SecController.h"

WSIAPP_BEGIN_OBJC

@implementation SecController

- (void)viewIsAppearing:(BOOL)animated {
    trace_msg(@"sec is appearing");
}

- (void)viewIsDisappearing:(BOOL)animated {
    trace_msg(@"sec is disppearing");    
}

@end

WSIAPP_END_OBJC