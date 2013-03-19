
# import "Core.h"
# import "QzDisplayLink.h"

WSI_BEGIN_OBJC

signal_t kSignalDisplayLink = @"::wsi::ui::displaylink::got";

@implementation UIDisplayLink

@synthesize displayLink = _ca;

- (id)init {
    self = [super init];
    
    _ca = [[CADisplayLink displayLinkWithTarget:self selector:@selector(_cb_displaylink)] retain];
    
    return self;
}

- (void)dealloc {
    safe_release(_ca);
    
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalDisplayLink)
WSIEVENT_END

- (void)_cb_displaylink {
    [self emit:kSignalDisplayLink];
}

- (void)hook {

}

- (void)unhook {
    [_ca invalidate];
}

@end

WSI_END_OBJC
