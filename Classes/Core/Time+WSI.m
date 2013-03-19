
# import "Core.h"
# import "Time+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalTimerStart = @"::wsi::core::timer::start";
signal_t kSignalTimerStop  = @"::wsi::core::timer::stop";
signal_t kSignalTimerFired = @"::wsi::core::timer::fired";
signal_t kSignalTimerSuspended = @"::wsi::core::timer::suspended";
signal_t kSignalTimerResume = @"::wsi::core::timer::resume";

@implementation NNTNSTimer

@synthesize interval = _seconds;
@synthesize repeat = _repeats;

- (id)init {
    self = [super init];
    
    _suspend = 0;
    _seconds = 1.f;
    _repeats = YES;
    
    return self;
}

- (id)initWithTimeInterval:(NSTimeInterval)seconds repeats:(BOOL)repeats {
    self = [self init];
    
    _seconds = seconds;
    _repeats = repeats;
    
    return self;
}

- (void)dealloc {
    if ([_timer isValid])
        [self stop];
    zero_release(_timer);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalTimerStart)
NNTEVENT_SIGNAL(kSignalTimerStop)
NNTEVENT_SIGNAL(kSignalTimerFired)
NNTEVENT_SIGNAL(kSignalTimerSuspended)
NNTEVENT_SIGNAL(kSignalTimerResume)
NNTEVENT_END

- (void)_act_timer_fired:(id)obj {
    if (_suspend != 0)
        return;
    [self emit:kSignalTimerFired];
}

- (void)start {
    [self performSelectorOnMainThread:@selector(do_start) withObject:nil waitUntilDone:YES];
}

- (void)do_start {
    if ([_timer isValid])
        [self stop];
    zero_release(_timer);
    
    // new timer.
    _timer = [[NSTimer scheduledTimerWithTimeInterval:_seconds 
                                               target:self 
                                             selector:@selector(_act_timer_fired:) 
                                             userInfo:nil 
                                              repeats:_repeats] retain];
    
    [self emit:kSignalTimerStart];
}

- (void)stop {
    [self performSelectorOnMainThread:@selector(do_stop) withObject:nil waitUntilDone:YES];
}

- (void)do_stop {
    if (_timer == nil)
        return;
    
    if ([_timer isValid])
        [_timer invalidate];
    zero_release(_timer);
    
    [self emit:kSignalTimerStop];
}

- (void)pause {
    if (0 == _suspend++) {
        [self emit:kSignalTimerSuspended];
    }
}

- (void)resume {
    if (_suspend == 0)
        return;
    if (0 == --_suspend) {
        [self emit:kSignalTimerResume];
    }
}

@end

NNT_END_OBJC