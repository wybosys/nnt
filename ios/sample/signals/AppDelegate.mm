
# include "WSIFoundation.h"
# import "AppDelegate.h"
# import "MainController.h"

@interface CA : WSIObject
@end

@implementation CA

- (id)init {
    self = [super init];
    return self;
}

@end

@interface CB : WSIObject
@end

@implementation CB

- (id)init {
    self = [super init];        
    return self;
}

- (void)act_a:(WSIEventObj*)evt {
    trace_msg(@"ACT A");
}

@end

WSIAPP_BEGIN

App::App()
{
    CA* a = [[CA alloc] init];
    [a register_signal:@"a"];
    
    CB* b = [[CB alloc] init];
    [a connect:@"a" sel:@selector(act_a:) obj:b];
    
    [_self attachSet:@"a" obj:a];
    [_self attachSet:@"b" obj:b];
    
    [a emit:@"a"];
}

App::~App()
{
    [[_self attachPop:@"a"] release];
    [[_self attachPop:@"b"] release];
}

void App::load()
{
    set_root(ctlr);
}

WSIAPP_END
