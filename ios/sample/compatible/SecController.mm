
# import "Foundation+NNT.h"
# import "SecController.h"

NNTAPP_BEGIN_OBJC

@implementation SecController

- (void)viewIsAppearing:(BOOL)animated {
    trace_msg(@"sec is appearing");
}

- (void)viewIsDisappearing:(BOOL)animated {
    trace_msg(@"sec is disppearing");    
}

@end

NNTAPP_END_OBJC