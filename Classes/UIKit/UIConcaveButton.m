
# import "Core.h"
# import "UIConcaveButton.h"
# import "CoreGraphic+NNT.h"
# import "WCGColor.h"
# import "UIColor+NNT.h"

NNT_BEGIN_OBJC

@implementation UIConcaveButton

@synthesize isPushed;
@synthesize imagePushed, imageNormal;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    [self addTarget:self action:@selector(act_pushed:) forControlEvents:UIControlEventTouchDown];
    
    return self;
}

- (id)initWithImage:(UIImage *)image {
    self = [super initWithFrame:CGRectMake(0, 0, image.size.width, image.size.height)];
    [self setImage:image forState:UIControlStateNormal];
    [self addTarget:self action:@selector(act_pushed:) forControlEvents:UIControlEventTouchDown];
    return self;
}

- (void)dealloc {
    zero_release(imagePushed);
    zero_release(imageNormal);
    [super dealloc];
}

- (void)setImage:(UIImage *)image forState:(UIControlState)state {
    [super setImage:image forState:state];        
    
    if (UIControlStateNormal == state) {
        CGRect rect = CGRectMakeSz(image.size);
        self.imageNormal = image;
        UIGraphicsBeginImageContext(rect.size);
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextSaveGState(context);
        // draw image
        [image drawAtPoint:CGPointZero];
        CGContextSetFillColorWithColor(context, [UIColor colorWithRGBA:0x00000033].CGColor);
        CGContextFillRect(context, rect);
        // draw shadow
        real flur_w = rect.size.width * .5f;
        real flur_h = rect.size.height * .5f;
        real flur = MIN(flur_w, flur_h);
        CGContextSetShadowWithColor(context, CGSizeMake(0, 0), flur, [UIColor whiteColor].CGColor);
        CGContextSetStrokeColorWithColor(context, [UIColor clearColor].CGColor);
        CGContextSetLineWidth(context, 5);
        CGContextStrokeRect(context, rect);
        CGContextRestoreGState(context);
        self.imagePushed = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    
    if (image == nil) {
        self.imagePushed = nil;
    }
}

# pragma mark delegate

- (void)act_pushed : (UIConcaveButton*)__btn {
    isPushed = !isPushed;
    
    UIImage *image = isPushed ? self.imagePushed : self.imageNormal;
    [super setImage:image forState:UIControlStateNormal];
}

@end

NNT_END_OBJC