
# import "Core.h"
# import "UIAnimation.h"

NNT_BEGIN_OBJC

signal_t kSignalAnimationStart = @"::nnt::ui::animation::start";
signal_t kSignalAnimationStop  = @"::nnt::ui::animation::stop";
signal_t kSignalAnimationRun = @"::nnt::ui::animation::run";

@implementation NNTUIAnimation

@synthesize name = _name, context = _context, commited = _commited, duration = _duration;

# ifdef NNT_BLOCKS

@synthesize run = _run, finish = _finish;

# endif

- (id)init {
    self = [super init];
    
    _commited = YES;
    _duration = 0.2f;
    
    return self;
}

- (void)dealloc {
    if (_commited == NO)
        [self commit];
    
    safe_release(_name);
    
# ifdef NNT_BLOCKS
    
    safe_release(_run);
    safe_release(_finish);
    
# endif
    
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAnimationStart)
NNTEVENT_SIGNAL(kSignalAnimationStop)
NNTEVENT_SIGNAL(kSignalAnimationRun)
NNTEVENT_END

- (BOOL)useBlock {
# ifdef NNT_BLOCKS
    if (_run || _finish)
        return YES;
# endif
    
    return NO;
}

- (void)begin {
    if ([self useBlock]) {
        return;
    }
    
    _commited = NO;
    
    [UIView beginAnimations:_name context:_context];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationWillStartSelector:@selector(act_willstart:context:)];
    [UIView setAnimationDidStopSelector:@selector(act_didstop:finished:context:)];
    [UIView setAnimationDuration:_duration];
    
    [self emit:kSignalAnimationRun];
    
    [self retain];
}

- (void)commit {
    if ([self useBlock]) {
        
        [UIView animateWithDuration:_duration
                         animations:^{
                             [self emit:kSignalAnimationRun];
                             [self emit:kSignalAnimationStart];
                             if (_run)
                                 _run();
                         } completion:^(BOOL finished) {
                             if (_finish)
                                 _finish();
                             [self emit:kSignalAnimationStop];
                         }];
        
        return;
    }
    
    [UIView commitAnimations];
    
    _commited = YES;
}

- (void)act_willstart:(NSString *)animationID context:(void *)context {
    if ((animationID && ![animationID isEqualToString:_name]) ||
        (context != _context))
        return;
    
    [self emit:kSignalAnimationStart];
}

- (void)act_didstop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context {
    if ((animationID && ![animationID isEqualToString:_name]) ||
        (context != _context))
        return;
    
    [self emit:kSignalAnimationStop];
    
    [self release];
}

@end

NNT_END_OBJC
