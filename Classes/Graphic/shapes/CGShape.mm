
# import "Core.h"
# import "CGShape.h"
# import "WCGContext.h"

NNT_BEGIN_OBJC

@implementation WCGShape

@synthesize context = _ctx;

- (void)dealloc {
    CGContextRelease(_ctx);
    [super dealloc];
}

- (void)setContext:(CGContextRef)ctx {
    CGContextRetain(ctx);
    CGContextRelease(_ctx);
    _ctx = ctx;
}

- (void)openPath:(CGRect)rect {
    CGContextSaveGState(_ctx);
    CGContextTranslateCTM(_ctx, CGRectGetMinX(rect), CGRectGetMinY(rect));
    CGContextBeginPath(_ctx);
}

- (void)closePath:(CGRect)rect {
    CGContextClosePath(_ctx);
    CGContextRestoreGState(_ctx);
}

- (void)addTopEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    PASS;
}

- (void)addRightEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    PASS;
}

- (void)addBottomEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    PASS;
}

- (void)addLeftEdgeToPath:(CGRect)rect lightSource:(NSInteger)lightSource {
    PASS;
}

- (void)addToPath:(CGRect)rect {
    PASS;
}

- (void)addInverseToPath:(CGRect)rect {
    PASS;
}

- (UIEdgeInsets)insetsForSize:(CGSize)size {
    return UIEdgeInsetsZero;
}

@end

NNT_END_OBJC