
# import "Core.h"
# import "CGAnimation.h"

WSI_BEGIN_OBJC

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

WSI_END_OBJC