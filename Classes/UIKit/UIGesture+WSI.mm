
# import "Core.h"
# import "UIGesture+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalGestureActive = @"::wsi::ui::gesture::active";

@implementation WSIUISwipeGestureRecognizer

WSIOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UISwipeGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation WSIUITapGestureRecognizer

WSIOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UITapGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation WSIUIPinchGestureRecognizer

WSIOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UIPinchGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation WSIUIRotationGestureRecognizer

WSIOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UIRotationGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation WSIUIPanGestureRecognizer

WSIOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UIPanGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation WSIUILongPressGestureRecognizer

WSIOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UILongPressGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

WSI_END_OBJC
