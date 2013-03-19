
# import "Core.h"
# import "NSButton+WSI.h"

WSI_BEGIN_OBJC

@implementation WSINSButton

- (id)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    return self;
}

WSIOBJECT_IMPL_NOSIGNALS;

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalAction);
}

@end

WSI_END_OBJC