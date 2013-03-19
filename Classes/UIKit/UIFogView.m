
# import "Core.h"
# import "UIFogView.h"
# import <QuartzCore/QuartzCore.h>
# import "CoreGraphic+WSI.h"

WSI_BEGIN_OBJC

@implementation UIFogView

@synthesize fogDepth, fogColor;

- (id)init {
    self = [super init];
    
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (void)dealloc {
    zero_release(fogColor);
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    if (fogDepth <= 0 || !fogColor)
        return;
    
    fogColor.angle = 90;
    
    self.layer.zPosition = 0.5;
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSaveGState(context);
    
    CGRect rc_fill = rect;
    rc_fill.size.height = rc_fill.size.height * fogDepth;
    [fogColor fillRect:rc_fill inContext:context];
    
    CGContextRestoreGState(context);
}

@end

WSI_END_OBJC
