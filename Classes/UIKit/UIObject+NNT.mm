
# import "Core.h"
# import "NNTUIObject.h"

NNT_BEGIN_OBJC

// touch signal.
signal_t kSignalTouchesBegin = @"::nnt::ui::touches::begin";
signal_t kSignalTouchesEnd = @"::nnt::ui::touches::end";
signal_t kSignalTouchesMoved = @"::nnt::ui::touches::moved";
signal_t kSignalTouchesCancel = @"::nnt::ui::touches::cancel";
signal_t kSignalTouchesOffset = @"::nnt::ui::touches::offset";

// orient changed.
signal_t kSignalOrientationChanged = @"::nnt::orientation::changed";

// theme changed.
signal_t kSignalThemeChanged = @"::nnt::ui::theme::changed";

// impl signals.
signal_t kSignalContentClicked = @"::nnt::ui::content::clicked";
signal_t kSignalItemClicked = @"::nnt::ui::item::clicked";

// shake the device.
signal_t kSignalDeviceShaked = @"::nnt::device::shaked";

// recieve remove control event.
signal_t kSignalRemoteControlEvent = @"::nnt::ui::remote::control::event";

static NNTUIObject *__gs_uiobject = nil;

@implementation NNTUIObject

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalTouchesBegin)
NNTEVENT_SIGNAL(kSignalTouchesCancel)
NNTEVENT_SIGNAL(kSignalTouchesEnd)
NNTEVENT_SIGNAL(kSignalTouchesMoved)
NNTEVENT_SIGNAL(kSignalTouchesOffset)
NNTEVENT_SIGNAL(kSignalOrientationChanged)
NNTEVENT_SIGNAL(kSignalThemeChanged)
NNTEVENT_SIGNAL(kSignalDeviceShaked)
NNTEVENT_SIGNAL(kSignalRemoteControlEvent)
NNTEVENT_END

@dynamic isGlobalEventProcessing;

- (id)init {
    self = [super init];
    __is_global_event_processing = 0;
    return self;
}

- (void)dealloc {
    [super dealloc];
}

+ (NNTUIObject*)shared {    
    NNT_SYNCHRONIZED(self)
    if (__gs_uiobject == nil) {
        __gs_uiobject = [[self alloc] init];
        NNT *nntobj = [NNT shared];
        if (nntobj) {
            [nntobj storeSet:@"::nnt::uikit::uiobject::singleton" obj:__gs_uiobject];
        }
    }
    NNT_SYNCHRONIZED_END
    return __gs_uiobject;
}

- (BOOL)isGlobalEventProcessing {
    return __is_global_event_processing != 0;
}

@end

@implementation NNTUIObject (event)

- (void)emit_begin {
    ++__is_global_event_processing;
}

- (void)emit_end {
    --__is_global_event_processing;
}

@end

@implementation cxxnsobject

@synthesize target;

@end

NNT_END_OBJC
