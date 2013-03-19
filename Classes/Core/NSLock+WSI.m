
# import "Core.h"
# import "NSLock+WSI.h"
# include <pthread.h>

//# define LOCK_VERBOSE

WSI_BEGIN_OBJC

@implementation WSINSLock

# ifdef LOCK_VERBOSE

- (void)lock {
    BOOL suc = [self tryLock];
    if (suc == FALSE) {
        dexpress(ptrdiff_t tid = (ptrdiff_t)pthread_self());
        trace_fmt(@"thread [0x%x] will be block", tid);
        [super lock];
        trace_fmt(@"thread [0x%x] resume", tid);
    }
}

# ifdef WSI_DEBUG

- (void)unlock {
    [super unlock];
    trace_fmt(@"thread [0x%x] is free", (ptrdiff_t)pthread_self());
}

# endif

- (BOOL)tryLock {
    BOOL suc = [super tryLock];
    if (suc) {
        trace_fmt(@"lock [0x%x] is accquired", (ptrdiff_t)self);
    }
    return suc;
}

# endif

@end

@implementation WSINSConditionLock

# ifdef LOCK_VERBOSE

- (void)lock {
    BOOL suc = [self tryLock];
    if (suc == FALSE) {
        dexpress(ptrdiff_t tid = (ptrdiff_t)pthread_self());
        trace_fmt(@"thread [0x%x] will be block", tid);
        [super lock];
        trace_fmt(@"thread [0x%x] resume", tid);
    }
}

# ifdef WSI_DEBUG

- (void)unlock {
    [super unlock];
    trace_fmt(@"thread [0x%x] is free", (ptrdiff_t)pthread_self());
}

# endif

- (BOOL)tryLock {
    BOOL suc = [super tryLock];
    if (suc) {
        trace_fmt(@"lock [0x%x] is accquired", (ptrdiff_t)self);
    }
    return suc;
}

# endif

@end

@implementation WSINSRecursiveLock

# ifdef LOCK_VERBOSE

- (void)lock {
    BOOL suc = [self tryLock];
    if (suc == FALSE) {
        dexpress(ptrdiff_t tid = (ptrdiff_t)pthread_self());
        trace_fmt(@"thread [0x%x] will be block", tid);
        [super lock];
        trace_fmt(@"thread [0x%x] resume", tid);
    }
}

# ifdef WSI_DEBUG

- (void)unlock {
    [super unlock];
    trace_fmt(@"thread [0x%x] is free", (ptrdiff_t)pthread_self());
}

# endif

- (BOOL)tryLock {
    BOOL suc = [super tryLock];
    if (suc) {
        trace_fmt(@"lock [0x%x] is accquired", (ptrdiff_t)self);
    }
    return suc;
}

# endif

@end

WSI_END_OBJC