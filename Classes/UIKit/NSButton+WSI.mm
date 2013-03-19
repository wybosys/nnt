
# import "Core.h"
# import "NSButton+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTNSButton

- (id)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    return self;
}

NNTOBJECT_IMPL_NOSIGNALS;

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalAction);
}

@end

NNT_END_OBJC