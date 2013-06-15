
# import "Core.h"
# import "UIGesture+NNT.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

signal_t kSignalGestureBegin = @"::nnt::ui::gesture::begin";
signal_t kSignalGestureEnd = @"::nnt::ui::gesture::end";
signal_t kSignalGestureActive = @"::nnt::ui::gesture::active";
signal_t kSignalGestureChanged = @"::nnt::ui::gesture::changed";
signal_t kSignalGestureCancel = @"::nnt::ui::gesture::cancel";

# define NNTUI_GESTURE_INITSIGNAL \
- (void)initSignals { \
NNTEVENT_SIGNAL(kSignalGestureBegin); \
NNTEVENT_SIGNAL(kSignalGestureEnd); \
NNTEVENT_SIGNAL(kSignalGestureActive); \
NNTEVENT_SIGNAL(kSignalGestureChanged); \
NNTEVENT_SIGNAL(kSignalGestureCancel); \
}

@interface UIGestureRecognizer (NNT)

- (void)_action_:(UIGestureRecognizer*)rec;

@end

@implementation UIGestureRecognizer (NNT)

- (void)_action_:(UIGestureRecognizer *)rec {
    switch (rec.state)
    {
        case UIGestureRecognizerStateBegan:
            [self emit:kSignalGestureBegin]; break;
        case UIGestureRecognizerStateCancelled:
            [self emit:kSignalGestureCancel]; break;
        case UIGestureRecognizerStateChanged:
            [self emit:kSignalGestureChanged]; break;
        case UIGestureRecognizerStateEnded:
            [self emit:kSignalGestureEnd];
            [self emit:kSignalGestureActive]; break;
        default: break;
    }
}

@end

@implementation NNTUIGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_action_:)];

    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTUI_GESTURE_INITSIGNAL;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesBegan:touches withEvent:event];

    if (NNT_OBJCXX_ISTYPE(self)) {
        ((ui::gesture::tpl::IGesture*)NNT_OBJCXX_TYPE(self))->touches_begin(ns::Set(touches), ui::Event(event));
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesMoved:touches withEvent:event];
    
    if (NNT_OBJCXX_ISTYPE(self)) {
        ((ui::gesture::tpl::IGesture*)NNT_OBJCXX_TYPE(self))->touches_moved(ns::Set(touches), ui::Event(event));
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesEnded:touches withEvent:event];
    
    if (NNT_OBJCXX_ISTYPE(self)) {
        ((ui::gesture::tpl::IGesture*)NNT_OBJCXX_TYPE(self))->touches_end(ns::Set(touches), ui::Event(event));
    }
    
    [self reset];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesCancelled:touches withEvent:event];
    
    if (NNT_OBJCXX_ISTYPE(self)) {
        ((ui::gesture::tpl::IGesture*)NNT_OBJCXX_TYPE(self))->touches_cancel(ns::Set(touches), ui::Event(event));
    }
    
    [self reset];
}

- (void)reset {
    if (NNT_OBJCXX_ISTYPE(self)) {
        ((ui::gesture::tpl::IGesture*)NNT_OBJCXX_TYPE(self))->reset();
    }
}

@end

@implementation NNTUISwipeGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_action_:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTUI_GESTURE_INITSIGNAL;

@end

@implementation NNTUITapGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_action_:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTUI_GESTURE_INITSIGNAL;

@end

@implementation NNTUIPinchGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_action_:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTUI_GESTURE_INITSIGNAL;

@end

@implementation NNTUIRotationGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_action_:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTUI_GESTURE_INITSIGNAL;

@end

@implementation NNTUIPanGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_action_:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTUI_GESTURE_INITSIGNAL;

@end

@implementation NNTUILongPressGestureRecognizer

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super initWithTarget:self action:@selector(_action_:)];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTUI_GESTURE_INITSIGNAL;

@end

NNTIMPL_OBJCXX_WRAPPER(NNTUIGestureRecognizer);

NNT_END_OBJC
