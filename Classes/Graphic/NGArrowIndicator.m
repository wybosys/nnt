
# import "Core.h"
# import "NGArrowIndicator.h"
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

@interface NgArrowIndicator ()

- (void)__init;
- (void)draw6:(CGContextRef)ctx;

@end

@implementation NgArrowIndicator

@synthesize lineStyle;
@synthesize arrowStyle;

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

- (void)dealloc {
    zero_release(lineStyle);
    
    [super dealloc];
}

- (void)__init {
    NgMutableLineStyle* ls = [[NgMutableLineStyle alloc] init];
    ls.lineWidth = 4;
    ls.lineColor = [NgColor whiteColor];
    lineStyle = ls;
    
    arrowStyle = NgArrowIndicatorStyle6;
}

- (void)drawInContext:(CGContextRef)ctx {
    switch (arrowStyle) {
        case NgArrowIndicatorStyle6: {
            [self draw6:ctx];
        } break;
    }
}

- (void)draw6:(CGContextRef)ctx {
    CGRect rc = CGRectDeflateCenter(self.bounds, 4, 4);
    CGPoint pt0 = CGRectLeftBottom(&rc);
    CGPoint pt2 = CGRectRightBottom(&rc);
    CGPoint pt1 = CGRectTopCenter(&rc);
    CGContextSaveGState(ctx);
    
    [lineStyle setLineStyleInContext:ctx];
    
    CGContextMoveToPoint(ctx, pt0.x, pt0.y);
    CGContextAddLineToPoint(ctx, pt1.x, pt1.y);
    CGContextAddLineToPoint(ctx, pt2.x, pt2.y);
    
    CGContextStrokePath(ctx);
    
    CGContextRestoreGState(ctx);
}

@end

NNT_END_OBJC