
# import "Core.h"
# import "CGStyleContext.h"

WSI_BEGIN_OBJC

@implementation WCGStyleContext

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

WSI_END_OBJC