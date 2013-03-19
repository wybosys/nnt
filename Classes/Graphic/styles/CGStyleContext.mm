
# import "Core.h"
# import "CGStyleContext.h"

NNT_BEGIN_OBJC

@implementation NgStyleContext

@synthesize context = _ctx;
@synthesize bounds;
@synthesize shape = _shape;

- (id)init {
    self = [super init];
    
    bounds = CGRectZero;
    
    return self;
}

- (void)dealloc {
    CGContextRelease(_ctx);
    [super dealloc];
}

- (void)setContext:(CGContextRef)ctx {
    CGContextRetain(ctx);
    CGContextRelease(_ctx);
    _ctx = ctx;
}

@end

NNT_END_OBJC