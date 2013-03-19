
# import "Core.h"
# import "WCALayer.h"
# import <QuartzCore/QuartzCore.h>
# import "CoreGraphic+WSI.h"
# import "WCALayerTheme.h"

WSI_BEGIN_OBJC

WSIIMPL_CATEGORY(CALayer, WCA);

@implementation CALayer (WCA)

- (void)moveTo:(CGPoint)pt {
    CGRect rc = self.frame;
    rc.origin = pt;
    self.frame = rc;
}

- (void)moveToSize:(CGSize)size {
    CGRect rc = self.frame;
    rc.size = size;
    self.frame = rc;
}

- (void)moveToCenter:(CGPoint)pt {
    CGRect rc = self.frame;
    CGPoint ct = CGRectCenterPoint(&rc);
    rc.origin.x += pt.x - ct.x;
    rc.origin.y += pt.y - ct.y;
    self.frame = rc;
}

- (void)freeze {
    [CATransaction begin];
    [CATransaction setValue:[NSNumber numberWithBool:YES]
                     forKey:kCATransactionDisableActions];
}

- (void)thaw {
    [CATransaction commit];
}

- (CGPoint)centerPoint {
    CGRect rc = self.frame;
    CGPoint pt = CGRectCenterPoint(&rc);
    return pt;
}

- (CGPoint)clientCenterPoint {
    CGRect rc = self.bounds;
    CGPoint pt = CGRectCenterPoint(&rc);
    return pt;
}

- (void)applyTheme:(WCALayerTheme *)theme {
    self.backgroundColor = theme.background;
    [theme setInLayer:self];
}

@end

@implementation WCALayer

WSIOBJECT_IMPL;

@synthesize backgroundFill;
@synthesize theme;

- (id)init {
    self = [super init];
    
    self.needsDisplayOnBoundsChange = YES;
    //self.backgroundColor = [UIColor clearColor].CGColor;
    
    return self;
}

- (id)initWithLayer:(id)layer {
    self = [super initWithLayer:layer];
    return self;
}

- (void)dealloc {
    zero_release(backgroundFill);
    zero_release(theme);
    
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)drawInContext:(CGContextRef)ctx {
    if (backgroundFill) {
        [backgroundFill fillRect:self.bounds inContext:ctx];
    }
    
    [self ownerDraw:self.bounds context:ctx];
}

- (void)ownerDraw:(CGRect)rect context:(CGContextRef)context {
    PASS;
}

- (void)applyTheme:(WCALayerTheme *)__theme {
    [super applyTheme:__theme];
    self.theme = __theme;
}

@end

WSI_END_OBJC