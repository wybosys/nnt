
# import "Core.h"
# import "NNTUIObject.h"

NNT_BEGIN_OBJC

// touch signal.
signal_t kSignalTouchesBegin = @"::wsi::ui::touches::begin";
signal_t kSignalTouchesEnd = @"::wsi::ui::touches::end";
signal_t kSignalTouchesMoved = @"::wsi::ui::touches::moved";
signal_t kSignalTouchesCancel = @"::wsi::ui::touches::cancel";
signal_t kSignalTouchesOffset = @"::wsi::ui::touches::offset";

// orient changed.
signal_t kSignalOrientationChanged = @"::wsi::orientation::changed";

// theme changed.
signal_t kSignalThemeChanged = @"::wsi::ui::theme::changed";

// impl signals.
signal_t kSignalContentClicked = @"::wsi::ui::content::clicked";
signal_t kSignalItemClicked = @"::wsi::ui::item::clicked";

// shake the device.
signal_t kSignalDeviceShaked = @"::wsi::device::shaked";

// recieve remove control event.
signal_t kSignalRemoteControlEvent = @"::wsi::ui::remote::control::event";

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
        NNT *wsiobj = [NNT shared];
        if (wsiobj) {
            [wsiobj storeSet:@"wsi::uikit::uiobject::singleton" obj:__gs_uiobject];
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
