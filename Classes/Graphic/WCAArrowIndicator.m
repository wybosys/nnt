
# import "Core.h"
# import "WCAArrowIndicator.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

@interface WCAArrowIndicator ()

- (void)__init;
- (void)draw6:(CGContextRef)ctx;

@end

@implementation WCAArrowIndicator

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
    WCGMutableLineStyle* ls = [[WCGMutableLineStyle alloc] init];
    ls.lineWidth = 4;
    ls.lineColor = [WCGColor whiteColor];
    lineStyle = ls;
    
    arrowStyle = WCAArrowIndicatorStyle6;
}

- (void)drawInContext:(CGContextRef)ctx {
    switch (arrowStyle) {
        case WCAArrowIndicatorStyle6: {
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