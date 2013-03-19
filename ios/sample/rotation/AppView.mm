
# import "WSIFoundation.h"
# import "AppView.h"

# import "AController.h"
# import "BController.h"

WSI_BEGIN_OBJC

@implementation AppView

- (id)initWithZero {
    self = [super initWithZero];
    
    ctlr_a = [[ACtlr alloc] init];
    ctlr_b = [[BCtlr alloc] init];
    
    [self addSubview:ctlr_a.view];
    [self addSubview:ctlr_b.view];
    
    return self;
}

- (void)dealloc {
    [ctlr_a release];
    [ctlr_b release];
    [super dealloc];
}

- (void)layoutSubviews {
    if (self.isLandscape) {
        trace_msg(@"view's orientation: landscape.");
    } else if (self.isPortrait) {
        trace_msg(@"view's orientation: portrait.");
    }
    
    using namespace ::wsi;
    
    CGRectLayoutHBox lyt(self.bounds, 5);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    ctlr_a.view.frame = lyt << lnr;
    ctlr_b.view.frame = lyt << lnr;
}

@end

WSI_END_OBJC