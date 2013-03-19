
# import "Core.h"
# import "WSIUIObject.h"

WSI_BEGIN_OBJC

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

static WSIUIObject *__gs_uiobject = nil;

@implementation WSIUIObject

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalTouchesBegin)
WSIEVENT_SIGNAL(kSignalTouchesCancel)
WSIEVENT_SIGNAL(kSignalTouchesEnd)
WSIEVENT_SIGNAL(kSignalTouchesMoved)
WSIEVENT_SIGNAL(kSignalTouchesOffset)
WSIEVENT_SIGNAL(kSignalOrientationChanged)
WSIEVENT_SIGNAL(kSignalThemeChanged)
WSIEVENT_SIGNAL(kSignalDeviceShaked)
WSIEVENT_SIGNAL(kSignalRemoteControlEvent)
WSIEVENT_END

@dynamic isGlobalEventProcessing;

- (id)init {
    self = [super init];
    __is_global_event_processing = 0;
    return self;
}

- (void)dealloc {
    [super dealloc];
}

+ (WSIUIObject*)shared {    
    WSI_SYNCHRONIZED(self)
    if (__gs_uiobject == nil) {
        __gs_uiobject = [[self alloc] init];
        WSI *wsiobj = [WSI shared];
        if (wsiobj) {
            [wsiobj storeSet:@"wsi::uikit::uiobject::singleton" obj:__gs_uiobject];
        }
    }
    WSI_SYNCHRONIZED_END
    return __gs_uiobject;
}

- (BOOL)isGlobalEventProcessing {
    return __is_global_event_processing != 0;
}

@end

@implementation WSIUIObject (event)

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

WSI_END_OBJC
