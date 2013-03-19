
# import "Core.h"
# import "CGShadow.h"

# ifdef WSI_TARGET_IOS
# import "UIColor+WSI.h"
# endif

# import <QuartzCore/QuartzCore.h>

WSI_BEGIN_OBJC

@implementation CGShadow

@synthesize
beginColor = _beginColor,
endColor = _endColor,
offset = _offset,
direction = _direction,
radius = _radius,
shadowColor = _shadowColor,
opacity = _opacity,
sideType = _sideType,
alpha = _alpha;

+ (id)shadow {
    return [[[CGShadow alloc] init] autorelease];
}

+ (id)textShadow {
    CGShadow *ret = [CGShadow shadow];
    ret.offset = CGSizeMake(0, -1);
    return ret;
}

- (id)init {
    self = [super init];
    
    _opacity = .618f;
    _radius = 3.09f;
    _offset = CGSizeMake(0, -3);
    _direction = CGSizeZero;
    _sideType = SideTypeDouble;
    _alpha = .33f;
    self.shadowColor = [WCGColor colorWithRGB:0x000000];
    
    return self;
}

- (void)dealloc {
    zero_release(_beginColor);
    zero_release(_endColor);
    zero_release(_shadowColor);
    
    [super dealloc];
}

- (void)setShadowColor:(WCGColor *)shadowColor {
    if ([shadowColor alphaComponent] != 1.f)
        _alpha = 1;
    
    [WSIObject refobjSet:&_shadowColor ref:shadowColor];
}

- (void)setInContext:(CGContextRef)ctx {
    CGContextSetShadowWithColor(ctx, _offset, _opacity, _shadowColor.cgColor);
}

- (void)setInLayer:(CALayer*)layer {
    layer.shadowColor = _shadowColor.cgColor;
    layer.shadowOffset = _offset;
    layer.shadowOpacity = _opacity;
    layer.shadowRadius = _radius;
}

- (void)encodeWithCoder:(NSCoder *)coder {
	[coder encodeFloat:_opacity forKey:@"opacity"];
	[coder encodeFloat:_radius forKey:@"radius"];
	[coder encodeFloat:_offset.width forKey:@"offsetWidth"];
    [coder encodeFloat:_offset.height forKey:@"offsetHeight"];
    [_shadowColor encodeWithCoder:coder];
}

- (id)initWithCoder:(NSCoder *)coder {
	self = [super init];
    if (self == nil)
        return nil;
    
    _opacity = [coder decodeFloatForKey:@"opacity"];
    _radius = [coder decodeFloatForKey:@"raidus"];
    _offset = CGSizeZero;
    _offset.width = [coder decodeFloatForKey:@"offsetWidth"];
    _offset.height = [coder decodeFloatForKey:@"offsetHeight"];
    _shadowColor = [[WCGColor alloc] initWithCoder:coder];

    return self;
}

- (id)copyWithZone:(NSZone *)zone {
    CGShadow *shadowCopy = [[self class] allocWithZone:zone];
    shadowCopy.opacity = _opacity;
    shadowCopy.radius = _radius;
    shadowCopy.offset = _offset;
    shadowCopy.shadowColor = [WCGColor colorWithCGColor:_shadowColor.cgColor];
    return shadowCopy;
}

- (WCGColor*)alphaColor {
    return [_shadowColor colorByMulti:1 g:1 b:1 a:_alpha];
}

- (void)drawInContext:(CGContextRef)ctx {
    if (CGContextIsPathEmpty(ctx))
        return;
    
    CGPoint dir = CGPointMake(1, 1);
    if (_direction.width < 0)
        dir.x = -1;
    else if (_direction.width == 0)
        dir.x = 0;
    if (_direction.height < 0)
        dir.y = -1;
    else if (_direction.height == 0)
        dir.y = 0;
    
    CGPathRef path = CGContextCopyPath(ctx);
    CGRect rc = CGPathGetBoundingBox(path);
    CGPoint center = CGRectCenterPoint(&rc);
    
    // draw.
    CGContextSaveGState(ctx);
    
    // move to offset.
    CGContextTranslateCTM(ctx, _offset.width, _offset.height);
    
    // set default line.
    CGContextSetLineWidth(ctx, 1);
    
    int segments = ceil(_radius);
    real seg_op = 1.f / segments;
    real seg_offset_x = _radius / rc.size.width / segments;
    real seg_offset_y = _radius / rc.size.height / segments;
    real seg_offset = _radius / segments;
    WCGColor* tgt_color = [self alphaColor];
    
    WSI_AUTORELEASEPOOL_BEGIN;
    for (uint i = 0; i <= segments;) {
        WCGColor* color = [tgt_color colorByMulti:1 g:1 b:1 a:(1 - i * seg_op)];
        CGContextSetStrokeColorWithColor(ctx, color.cgColor);
        CGContextStrokePath(ctx);
        
        if (++i < segments) {
            if (MASK_CHECK(SideTypeOutter, _sideType)) {
                CGContextSaveGState(ctx);
                
                CGContextTranslateCTM(ctx, center.x, center.y);
                CGContextScaleCTM(ctx, 1 + seg_offset_x * i, 1 + seg_offset_y * i);
                CGContextTranslateCTM(ctx, -center.x, -center.y);
            
                CGContextTranslateCTM(ctx, dir.x * seg_offset * i, dir.y * seg_offset * i);
                CGContextAddPath(ctx, path);
                
                CGContextRestoreGState(ctx);
            }
            
            if (MASK_CHECK(SideTypeInner, _sideType)) {
                CGContextSaveGState(ctx);
                
                CGContextTranslateCTM(ctx, center.x, center.y);
                CGContextScaleCTM(ctx, 1 - seg_offset_x * i, 1 - seg_offset_y * i);
                CGContextTranslateCTM(ctx, -center.x, -center.y);
                
                CGContextTranslateCTM(ctx, -dir.x * seg_offset * i, -dir.y * seg_offset * i);
                CGContextAddPath(ctx, path);
                
                CGContextRestoreGState(ctx);
            }
        }
    }
    WSI_AUTORELEASEPOOL_END;
    
    CGPathRelease(path);
    
    CGContextRestoreGState(ctx);
}

@end

WSI_END_OBJC