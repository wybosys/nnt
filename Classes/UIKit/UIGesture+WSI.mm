
# import "Core.h"
# import "UIGesture+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalGestureActive = @"::wsi::ui::gesture::active";

@implementation NNTUISwipeGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UISwipeGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation NNTUITapGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UITapGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation NNTUIPinchGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UIPinchGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation NNTUIRotationGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UIRotationGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation NNTUIPanGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UIPanGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

@implementation NNTUILongPressGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_active:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalGestureActive);
}

- (void)_active:(UILongPressGestureRecognizer*)rec {
    [self emit:kSignalGestureActive];
}

@end

NNT_END_OBJC
