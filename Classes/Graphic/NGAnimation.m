
# import "Core.h"
# import "NGAnimation.h"

NNT_BEGIN_OBJC

@implementation CGAnimation

@synthesize duration;

- (id)init {
    self = [super init];
    
    duration = 1.f;
    
    return self;
}

- (void)fini {
    [super fini];
}

@end

NNT_END_OBJC