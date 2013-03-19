
# import "Core.h"
# import "CATextLayer+WCA.h"
# import "WCGTextStyle.h"
# import "WCGDefines.h"
# import "WCGContext.h"

NNT_BEGIN_OBJC

@interface WCATextLayer ()

- (void)__init;

@end

@implementation WCATextLayer

@synthesize string;
@synthesize textStyle;

- (id)init {
    self = [super init];
    [self __init];
    return self;
}

- (id)initWithLayer:(id)layer {
    self = [super initWithLayer:layer];
    [self __init];
    return self;
}

- (void)__init {
    WCGMutableTextStyle *ts = [[WCGMutableTextStyle alloc] init];
    ts.alignment = WCGAlignmentCenter;
    textStyle = ts;
}

- (void)dealloc {
    zero_release(string);
    zero_release(textStyle);
    [super dealloc];
}

- (void)drawInContext:(CGContextRef)ctx {
    [super drawInContext:ctx];
    CGContextAddTextInRect(ctx, self.bounds, string, textStyle);
}

@end

NNT_END_OBJC