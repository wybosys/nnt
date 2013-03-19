
# import "Core.h"
# import "CorePlot+WSI.h"
# import "Math+WSI.h"

WSI_BEGIN

@interface CPIndicatorLayerPrivate : NSObject {
    CPIndicatorLayer *d_owner;
}

@property (nonatomic, assign) CPIndicatorLayer *d_owner;

- (void)init_layer;

@end

@implementation CPIndicatorLayerPrivate

@synthesize d_owner;

- (void)init_layer {
    d_owner.bounds = CGRectMake(0, 0, 10, 10);
    d_owner.needsDisplayOnBoundsChange = NO;
    [d_owner pixelAlign];
    [d_owner setNeedsLayout];
    [d_owner setNeedsDisplay];  
}

@end

@implementation CPIndicatorLayer 

@synthesize positionAngle, indicatorColor, indicatorBaseColor, baseHeight, identifier;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(CPIndicatorLayer);
    
    baseHeight = .1f;
    
    [d_ptr init_layer];
    
    return self;
}

- (void)dealloc {
    [indicatorColor release];
    [indicatorBaseColor release];
    [identifier release];
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

-(void)renderAsVectorInContext:(CGContextRef)context {
    CGRect bounds = self.bounds;
    
    CGContextSaveGState(context);
    
    if (indicatorColor == nil)
        indicatorColor = [CPColor blackColor];       
    if (indicatorBaseColor == nil) {
        self.indicatorBaseColor = [CPColor addWith:indicatorColor r:.2f g:.2f b:.2f];
    }
    
    CGFloat width = bounds.size.width;
    CGFloat height = bounds.size.height;
    CGFloat width_2 = width * .5;
    
    // draw left triangle
    CGMutablePathRef ph_lf = CGPathCreateMutable();
    CGPathMoveToPoint(ph_lf, nil, 0, 0);
    CGPathAddLineToPoint(ph_lf, nil, width_2, 0);
    CGPathAddLineToPoint(ph_lf, nil, width_2, height);
    CGPathAddLineToPoint(ph_lf, nil, 0, 0);
    CGPathCloseSubpath(ph_lf);
    
    CPFill *fill_lf = [CPFill fillWithColor:indicatorColor];
    CGContextBeginPath(context);
    CGContextAddPath(context, ph_lf);
    [fill_lf fillPathInContext:context];
    CGPathRelease(ph_lf);
    
    // draw right triangle
    CGMutablePathRef ph_rg = CGPathCreateMutable();
    CGPathMoveToPoint(ph_rg, nil, width_2, 0);
    CGPathAddLineToPoint(ph_rg, nil, width, 0);
    CGPathAddLineToPoint(ph_rg, nil, width_2, height);
    CGPathAddLineToPoint(ph_rg, nil, width_2, 0);
    CGPathCloseSubpath(ph_rg);
    
    CPGradient *grad_rg = [CPGradient gradientWithBeginningColor:indicatorColor endingColor:[CPColor whiteColor]];
    grad_rg.angle = 90;
    CPFill *fill_rg = [CPFill fillWithGradient:grad_rg];
    CGContextBeginPath(context);
    CGContextAddPath(context, ph_rg);
    [fill_rg fillPathInContext:context];
    CGPathRelease(ph_rg);
    
    // draw base rect
    CGMutablePathRef ph_ba = CGPathCreateMutable();
    CGFloat h = height * baseHeight;
    CGFloat w = h / height * width_2;
    CGPathMoveToPoint(ph_ba, nil, 0, 0);
    CGPathAddLineToPoint(ph_ba, nil, width, 0);
    CGPathAddLineToPoint(ph_ba, nil, width - w, h);
    CGPathAddLineToPoint(ph_ba, nil, w, h);
    CGPathAddLineToPoint(ph_ba, nil, 0, 0);
    CGPathCloseSubpath(ph_ba);
    
    CPFill *fill_ba = [CPFill fillWithColor:indicatorBaseColor];
    CGContextBeginPath(context);
    CGContextAddPath(context, ph_ba);
    [fill_ba fillPathInContext:context];
    CGPathRelease(ph_ba);
    
    // shadow path
    CGMutablePathRef ph_sd = CGPathCreateMutable();
    CGPathMoveToPoint(ph_sd, nil, 0, 0);
    CGPathAddLineToPoint(ph_sd, nil, width, 0);
    CGPathAddLineToPoint(ph_sd, nil, width_2, height);
    CGPathAddLineToPoint(ph_sd, nil, 0, 0);
    CGPathCloseSubpath(ph_sd);
    self.shadowPath = ph_sd;
    CGPathRelease(ph_sd);
    
    CGContextRestoreGState(context);
}

@end

WSI_END