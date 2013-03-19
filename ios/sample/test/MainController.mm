
# include "WSIFoundation.h"
# include "MainController.h"

@interface CA : NSObject
@property (nonatomic, retain) NSString* str;
@end

@implementation CA
@synthesize str;

- (void)dealloc {
    [str release];
    [super dealloc];
}

@end

WSIAPP_BEGIN

class CB
: public ns::Object<CA>
{
public:
    
    WSIDECL_PROPERTY_RETAIN(str, NSString*);
    
};

MainView::MainView()
{
    NSMutableString* str = [[NSMutableString alloc] init];
    trace_rc(str);
    [str appendString:@"A"];
    
    {
        CB obj;
        obj.str() = str;
        trace_rc(str);
        [str appendString:@"B"];
    }

    trace_rc(str);
    [str appendString:@"C"];
    
    set_background(ui::Color::Orange());
    
    add_sub(btn);
    
    btn.set_text(@"HELLO");
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    
    btn.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn.connect(kSignalButtonClicked, _action(_class::act_btn), this);
}

void MainController::act_btn()
{
    core::Confirm::info(@"Hello, WSI !");
}

WSIAPP_END
