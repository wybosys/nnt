
# include "Foundation+NNT.h"
# import "AppDelegate.h"
# import "MainController.h"

/*
 
@interface CA : NNTObject
@end

@implementation CA

- (id)init {
    self = [super init];
    return self;
}

@end

@interface CB : NNTObject
@end

@implementation CB

- (id)init {
    self = [super init];        
    return self;
}

- (void)act_a:(NNTEventObj*)evt {
    trace_msg(@"ACT A");    
    while(1) {sleep_second(1);}
}

@end
 */

NNTAPP_BEGIN

class CA
: public ns::Object<>
{
public:
    
    ns::property<int> count;
    
};

class CB
: public ns::Object<>
{
public:
    
    void act_a()
    {
        trace_msg(@"ACT A");
        while(1) {sleep_second(1);}
    }
    
    void act_a_changed(EventObj& evt)
    {
        int val = evt.data();
        trace_fmt(@"value: %d", val);
    }
    
};

App::App()
{
    CA a;
    a.register_signal(@"a");
    
    CB b;
    a.connect(@"a", _action(CB::act_a), &b).background().set_parallel(3);
    
    for (uint i = 0; i < 10; ++i)
    {
        a.emit(@"a");
    }
    
    a.count.connect_changed(_action(CB::act_a_changed), &b);
    //a.count.disconnect(&b);
    a.count = 123;
}

App::~App()
{
    
}

void App::load()
{
    set_root(ctlr);
}

NNTAPP_END
