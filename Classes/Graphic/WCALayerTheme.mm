
# import "Core.h"
# import "WCALayer.h"
# import "WCALayerTheme.h"
# import "WCGColor.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

@implementation WCALayerTheme

@synthesize background;

- (id)init {
    self = [super init];
    
    background = [WCGColor clearColor].cgColor;

    return self;
}

- (void)setInLayer:(CALayer *)layer {
    PASS;
}

# ifdef NNT_TARGET_IOS

- (UIImage*)createImage:(CGSize)size {
    WCALayer *layer = [[WCALayer alloc] init];
    layer.frame = CGRectMakeSz(size);

    // set in layer.
    [self setInLayer:layer];

    // render.
    UIGraphicsBeginImageContext(layer.bounds.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    [layer renderInContext:context];
    
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    [layer release];
    
    return img;
}

# endif

@end

NNT_END_OBJC