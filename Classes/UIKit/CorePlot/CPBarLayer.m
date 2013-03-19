
# import "Core.h"
# import "CorePlot+NNT.h"
# import "CPBarLayer.h"

NNT_BEGIN_OBJC

@implementation CPBarLayer

@synthesize layerFill, layerBorderLineStyle, layerFillHighlight, layerBorderLineStyleHighlight;

- (id)initWithFrame:(CGRect)newFrame {
    self = [super initWithFrame:newFrame];
 
    if (self) {
        
        self.anchorPoint = CGPointMake(0, 0);
        self.frame = newFrame;
        
        [self setNeedsDisplay];
    }
    
    return self;
}

- (void)dealloc {
    [layerFill release];
    [layerFillHighlight release];
    [layerBorderLineStyle release];
    [layerBorderLineStyleHighlight release];
    [super dealloc];
}

# pragma mark -

- (void)drawInContext:(CGContextRef)ctx {    
    
    CGContextSaveGState(ctx);
        
    CPFill *fill = layerFillHighlight;
    if (fill == nil)
        fill = layerFill;
    if (fill) {
        CGContextSaveGState(ctx);
        [fill fillRect:self.bounds inContext:ctx];
        CGContextRestoreGState(ctx);
    }
    
    CPLineStyle *ls = layerBorderLineStyleHighlight;
    if (ls == nil)
        ls = layerBorderLineStyle;
    if (ls) {
        CGContextSaveGState(ctx);
        CGMutablePathRef path = CGPathCreateMutable();
        CGPathAddRect(path, nil, self.bounds);
        CGContextBeginPath(ctx);
        CGContextAddPath(ctx, path);
        [ls setLineStyleInContext:ctx];
        CGContextStrokePath(ctx);
        CGContextRestoreGState(ctx);
        CGPathRelease(path);
    }
    
    CGContextRestoreGState(ctx);
}

@end

NNT_END_OBJC