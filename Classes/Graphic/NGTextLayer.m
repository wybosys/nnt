
# import "Core.h"
# import "NGTextLayer.h"
# import "NGTextStyle.h"
# import "NGDefines.h"
# import "NGContext.h"

NNT_BEGIN_OBJC

@interface NgTextLayer ()

- (void)__init;

@end

@implementation NgTextLayer

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
    NgMutableTextStyle *ts = [[NgMutableTextStyle alloc] init];
    ts.alignment = NgAlignmentCenter;
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