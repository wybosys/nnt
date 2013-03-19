
# import "Core.h"
# import "NSRunLoop+NNT.h"

NNT_BEGIN_OBJC

@implementation NSRunSection

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [self unblock];
    [super dealloc];
}

- (void)block {
    if (_rl == NULL)
        _rl = CFRunLoopGetCurrent();
    CFRunLoopRun();
}

- (void)unblock {
    if (_rl) {
        CFRunLoopStop(_rl);
        _rl = NULL;
    }
}

@end

NNT_END_OBJC
