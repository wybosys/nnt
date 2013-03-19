
# import "Core.h"
# import "NGLayer.h"
# import "NGLayerTheme.h"
# import "NGColor.h"
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

@implementation NgLayerTheme

@synthesize background;

- (id)init {
    self = [super init];
    
    background = [NgColor clearColor].cgColor;

    return self;
}

- (void)setInLayer:(CALayer *)layer {
    PASS;
}

# ifdef NNT_TARGET_IOS

- (UIImage*)createImage:(CGSize)size {
    NgLayer *layer = [[NgLayer alloc] init];
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