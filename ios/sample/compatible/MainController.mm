
# import "WSIFoundation.h"
# import "MainController.h"
# import "SecController.h"

WSIAPP_BEGIN_OBJC

@implementation MainController

SecController* ctlr = nil;

- (void)viewIsLoading {
    ctlr = [SecController new];
    
    //[self.view addSubview:ctlr.view];
    [self addSubController:ctlr];
    
    [self performSelector:@selector(act_remove) withObject:nil afterDelay:5];
}
     
- (void)act_remove {
    [ctlr removeFromSuperController];
    
    [self performSelector:@selector(act_add) withObject:nil afterDelay:5];
}

- (void)act_add {
    [self addSubController:ctlr];
}

- (void)viewIsAppearing:(BOOL)animated {
    trace_msg(@"main is appearing");
}

- (void)viewIsDisappearing:(BOOL)animated {
    trace_msg(@"main is disppearing");    
}

@end

WSIAPP_END_OBJC