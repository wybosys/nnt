
# import "Core.h"
# import "UINavigationDialLayers.h"
# import "Math+NNT.h"
# import "Graphic+NNT.h"
# import "UIColor+NNT.h"

NNT_BEGIN_OBJC

//# define DRAW_ITEM_CENTER

@implementation NgLayerDialRingCenter

@synthesize radiusExpend, radiusCollapse, radius;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)setRadius:(real)val {    
    radius = val;
    real dia = val + val;
    [self moveToSize:CGSizeMake(dia, dia)];
}

- (void)drawInContext:(CGContextRef)ctx {
    //[super drawInContext:ctx];
    
    CGRect const rc_client = CGContextGetClipBoundingBox(ctx);
    real color_hole[] = {1, 1, 1, 1};
    
    CGContextAddEllipseInRect(ctx, rc_client);
    CGContextSetFillColor(ctx, color_hole);
    CGContextFillPath(ctx);
    
    CGContextSetBlendMode(ctx, kCGBlendModeSourceIn);
    [super drawInContext:ctx];
}

- (BOOL)containsPoint:(CGPoint)p {
    real dis = distance_points2d(p.x, p.y, radius, radius);
    return dis < radius;
}

@end

@interface NgLayerDialRing ()

//- (NSArray*)copyItems;

@end

@implementation NgLayerDialRing

@synthesize radiusInner, radiusOutter, diameterOuter;
@synthesize ringShadowOuter, ringShadowInner;
@synthesize itemLayers;
@synthesize startAngle;

- (id)init {
    self = [super init];    
    
    self.ringShadowOuter = [CGShadow shadow];
    self.ringShadowOuter.shadowColor = [NgColor colorWithRGBA:0x00000077];
    self.ringShadowInner = [CGShadow shadow];
    self.ringShadowInner.shadowColor = [NgColor colorWithRGBA:0x00000077];
    
    startAngle = -M_PI_2;
    
    return self;
}

- (id)initWithLayer:(id)layer {
    self = [super initWithLayer:layer];
    if (self && [layer isKindOfClass:[self class]]) {
        NgLayerDialRing *ring = (NgLayerDialRing*)layer;
                
        self.ringShadowOuter = ring.ringShadowOuter;
        self.ringShadowInner = ring.ringShadowInner;
        self.radiusInner = ring.radiusInner;
        self.radiusOutter = ring.radiusOutter;
        //self.itemLayers = ring.itemLayers;
        self.startAngle = ring.startAngle;
        
    }
    return self;
}

- (void)dealloc {
    zero_release(ringShadowOuter);
    zero_release(ringShadowInner);
    zero_release(itemLayers);
    
    [super dealloc];
}

+ (BOOL)needsDisplayForKey:(NSString *)key {
    if ([key isEqualToString:@"startAngle"]) {
        return YES;
    }
    return [super needsDisplayForKey:key];
}

- (void)setStartAngle:(real)val {
    startAngle = val;
    
    CGAffineTransform mat = CGAffineTransformMakeRotation(startAngle);
    [self setAffineTransform:mat];
    
    if (self.hidden == NO) {
        [self relayoutItems];
    }
}

- (void)setValue:(id)value forKeyPath:(NSString *)keyPath {
    [super setValue:value forKeyPath:keyPath];
}

- (id)valueForKeyPath:(NSString *)keyPath {
    return [super valueForKeyPath:keyPath];
}

- (void)setRadiusOutter:(real)val {
    radiusOutter = val;

    real dis = ceil(self.ringShadowOuter.radius);
    diameterOuter = radiusOutter + radiusOutter + dis + dis;
    [self moveToSize:CGSizeMake(diameterOuter, diameterOuter)];
}

- (void)setRadiusInner:(real)val {
    radiusInner = val;
}

- (void)setItemLayers:(NSArray *)arr {
    [itemLayers release];
    itemLayers = [arr retain];
    
    for (NgLayerDialRingItem *layer in itemLayers) {
        [self addSublayer:layer];
    }
}

/*
- (NSArray*)copyItems {
    NSMutableArray *arr = [[[NSMutableArray alloc] initWithCapacity:[itemLayers count]] autorelease];
    for (NgLayerDialRingItem *each in itemLayers) {
        NgLayerDialRingItem *item = [[NgLayerDialRingItem alloc] init];
        [arr addObject:item];
        [item release];
    }
    return arr;
}
 */

- (void)relayoutItems {
    [self freeze];
    
    real itemLength = radiusOutter - radiusInner;
    CGRect itemRc = CGRectMake(0, 0, itemLength, itemLength);
    
    CGRect const rc_client = self.bounds;
    CGPoint const pt_center = CGRectCenterPoint(&rc_client);
    real dangle = M_2PI / [itemLayers count];
    
    real const itemDistance = radiusOutter - itemLength * .5f;
    
    for (uint i = 0; i < [itemLayers count]; ++i) {
        NgLayerDialRingItem *item = [itemLayers objectAtIndex:i];        
        
        [item setAffineTransform:CGAffineTransformIdentity];        
                
        real cur_angle = dangle * i;
        
        real x = pt_center.x + itemDistance * cg_cos(cur_angle);
        real y = pt_center.y + itemDistance * cg_sin(cur_angle);

        itemRc.origin = CGPointMake(x - itemLength * .5f, y - itemLength * .5f);
        
        item.frame = CGRectDeflateCenterR(itemRc, item.deflate, item.deflate);
        
        real item_angle = cur_angle - M_3_2_PI;        
        CGAffineTransform mat = CGAffineTransformMakeRotation(item_angle);
        [item setAffineTransform:mat];
    }
        
    [self thaw];
    
    [self setNeedsDisplay];
}

- (void)layoutSublayers {
    [super layoutSublayers]; 
    [self relayoutItems];
}

- (void)drawInContext:(CGContextRef)ctx {
    //[super drawInContext:ctx];
    
    CGRect const rc_client = self.bounds;
    CGPoint const pt_center = CGRectCenterPoint(&rc_client);
    
    real color_hole[] = {1, 1, 1, 1};
    
    // draw hole.
    CGContextSaveGState(ctx);
    
    // draw outer
    CGContextSetBlendMode(ctx, kCGBlendModeNormal);
    CGContextAddArc(ctx, pt_center.x, pt_center.y, radiusOutter, 0, M_2PI, 1);
    CGContextSetFillColor(ctx, color_hole);
    // fill
    CGContextFillPath(ctx);
    
    // dig hole
    CGContextSetBlendMode(ctx, kCGBlendModeClear);
    CGContextAddArc(ctx, pt_center.x, pt_center.y, radiusInner, 0, M_2PI, 1);
    CGContextSetFillColor(ctx, color_hole);    
    // fill
    CGContextFillPath(ctx);
    
    CGContextSetBlendMode(ctx, kCGBlendModeSourceIn);
    [super drawInContext:ctx];
    
    CGContextRestoreGState(ctx);
    
    // draw shadow.
    // outer.
    CGContextSetLineWidth(ctx, kCGShadowLineWidth);
    CGContextSetBlendMode(ctx, kCGBlendModeNormal);
    CGContextAddArc(ctx, pt_center.x, pt_center.y, radiusOutter, 0, M_2PI, 1);
    for (uint i = 0; i < ringShadowOuter.radius; ++i) {
        NgColor *color = [ringShadowOuter.shadowColor colorByMulti:1 g:1 b:1 a:(1 - i / (real)ringShadowOuter.radius)];
        
        
        CGContextSetStrokeColorWithColor(ctx, color.cgColor);
        CGContextAddArc(ctx, pt_center.x, pt_center.y, radiusOutter + i, 0, M_2PI, 1);        
        CGContextStrokePath(ctx);
    }    
    // inner.
    CGContextAddArc(ctx, pt_center.x, pt_center.y, radiusInner, 0, M_2PI, 1);
    for (uint i = 0; i < ringShadowInner.radius; ++i) {
        NgColor *color = [ringShadowInner.shadowColor colorByMulti:1 g:1 b:1 a:(1 - i / (real)ringShadowInner.radius)];
        CGContextSetStrokeColorWithColor(ctx, color.cgColor);        
        CGContextAddArc(ctx, pt_center.x, pt_center.y, radiusInner - i, 0, M_2PI, 1);
        CGContextStrokePath(ctx);
    }
    
# ifdef DRAW_ITEM_CENTER
    if ([itemLayers count]) {
        CGContextSetStrokeColorWithColor(ctx, [UIColor blackColor].CGColor);
        CGPoint *pts = (CGPoint*)malloc([itemLayers count] * sizeof(CGPoint));
        for (uint i = 0; i < [itemLayers count]; ++i) {
            pts[i] = [((NgLayerRingItem*)[itemLayers objectAtIndex:i]) centerPoint];
        }
        CGContextAddLines(ctx, pts, [itemLayers count]);
        CGContextClosePath(ctx);
        CGContextStrokePath(ctx);
        free(pts);
    }
# endif
    
    /*
    for (NgLayerRingItem *each in itemLayers) {
        [each drawInContext:ctx];
    }
     */
    
}

@end

@implementation NgLayerDialRingItem

@synthesize image;
@synthesize edgeShadow;
@synthesize scaleImage;
@synthesize deflate;
@synthesize imageMaskColor;
@synthesize layerBadge;

- (id)init {
    self = [super init];
    
    self.edgeShadow = [CGShadow shadow];
    scaleImage = .2f;
    deflate = .2f;
    
    return self;
}

- (id)initWithLayer:(id)layer {
    self = [super initWithLayer:layer];
    if (self && [layer isKindOfClass:[self class]]) {
        
        NgLayerDialRingItem *item = (NgLayerDialRingItem*)layer;
        self.image = item.image;
        self.edgeShadow = item.edgeShadow;
        self.scaleImage = item.scaleImage;
        self.imageMaskColor = item.imageMaskColor;
        
    }
    return self;
}

- (void)dealloc {
    zero_release(edgeShadow);
    zero_release(imageMaskColor);
    
    [super dealloc];
}

- (void)drawInContext:(CGContextRef)ctx {   
    [super drawInContext:ctx];
    
    CGRect const rc_client = self.bounds;
    CGPoint const pt_center = CGRectCenterPoint(&rc_client);
    real const offset_len = rc_client.size.width * scaleImage;
    real const radius = rc_client.size.width * .5f;
    int const offset_edge = ceil(edgeShadow.radius);
    real const deflate_len = offset_len + offset_edge;
    CGRect const rc_region = CGRectDeflateCenter(rc_client, deflate_len, deflate_len);
    
    // draw shadow.
    CGContextSetLineWidth(ctx, kCGShadowLineWidth);
    for (uint i = 0; i < offset_edge; ++i) {
        NgColor *color = [edgeShadow.shadowColor colorByMulti:1 g:1 b:1 a:(1 - i / (real)offset_edge)];
        CGContextSetStrokeColorWithColor(ctx, color.cgColor);
        CGContextAddArc(ctx, pt_center.x, pt_center.y, radius - i, 0, M_2PI, 1);
        CGContextStrokePath(ctx);
    }
    
    // draw image.
    if (image) {
        if (imageMaskColor) 
            CGContextFillImageMask(ctx, rc_region, image, imageMaskColor.CGColor);
        else
            CGContextDrawImageOri(ctx, rc_region, image);
    }
}

- (void)setLayerBadge:(NgLayer*)layer {
    if (layerBadge == layer) {
        [layerBadge setNeedsDisplay];
        return;
    }
    
    [layerBadge removeFromSuperlayer];
    layerBadge = layer;
    [self addSublayer:layer];
}

@end

@implementation NgLayerDialLabelRing

@synthesize radius, diameter;
@synthesize itemLayers;
@synthesize startAngle;
@synthesize clockwise;

- (id)init {
    self = [super init];
    
    startAngle = -M_PI_2;
    clockwise = YES;
    
    return self;
}

- (id)initWithLayer:(id)layer {
    self = [super initWithLayer:layer];
    if (self && [layer isKindOfClass:[self class]]) {
        NgLayerDialLabelRing *ring = (NgLayerDialLabelRing*)layer;
        
        self.radius = ring.radius;        
        self.clockwise = ring.clockwise;
        //self.itemLayers = ring.itemLayers;
        self.startAngle = ring.startAngle;
        
    }
    return self;
}

- (void)dealloc {
    zero_release(itemLayers);
    [super dealloc];
}

+ (BOOL)needsDisplayForKey:(NSString *)key {
    if ([key isEqualToString:@"startAngle"]) {
        return YES;
    }
    return [super needsDisplayForKey:key];
}

- (void)setRadius:(real)val {
    radius = val;
    
    diameter = radius + radius;
    [self moveToSize:CGSizeMake(diameter, diameter)];
}

- (void)setItemLayers:(NSArray *)arr {
    [itemLayers release];
    itemLayers = [arr retain];
    for (NgTextLayer *layer in itemLayers) {
        [self addSublayer:layer];
    }
}

- (void)relayoutItems {
    [self freeze];        
    
    CGRect const rc_client = self.bounds;
    CGPoint const pt_center = CGRectCenterPoint(&rc_client);
    real dangle = M_2PI / [itemLayers count];       
    
    for (uint i = 0; i < [itemLayers count]; ++i) {
        NgLayerDialLabelRingItem *item = [itemLayers objectAtIndex:i];  
        CGRect rc_item = CGRectMakeSz(item.preferredSize);
        
        if (item.adaptContent) {
            CGSize sz_title = [item.textStyle sizeOfString:item.string];
            rc_item.size.width = sz_title.width + item.textStyle.fontSize;
            rc_item.size.height = sz_title.height;
        }
        
        [item setAffineTransform:CGAffineTransformIdentity]; 
        
        real const itemDistance = radius + rc_item.size.width * .5f + item.offset;                       
        
        real cur_angle = dangle * i;
        
        real x = pt_center.x + itemDistance * cg_cos(cur_angle);
        real y = pt_center.y + itemDistance * cg_sin(cur_angle);
        
        rc_item.origin = CGPointMake(x - rc_item.size.width * .5f, y - rc_item.size.height * .5f);
        item.frame = rc_item;
        
        real item_angle = cur_angle + (clockwise ? 0 : M_PI);
        CGAffineTransform mat = CGAffineTransformMakeRotation(item_angle);
        [item setAffineTransform:mat];
    }
    
    [self thaw];
    
    [self setNeedsDisplay];
}

- (void)setStartAngle:(real)val {
    startAngle = val;
    
    CGAffineTransform mat = CGAffineTransformMakeRotation(startAngle);
    [self setAffineTransform:mat];
    
    if (self.hidden == NO) {
        [self relayoutItems];
    }
}

- (void)drawInContext:(CGContextRef)ctx {
    [super drawInContext:ctx];
    
# ifdef DRAW_ITEM_CENTER
    if ([itemLayers count]) {
        CGContextSetStrokeColorWithColor(ctx, [UIColor blackColor].CGColor);
        CGPoint *pts = (CGPoint*)malloc([itemLayers count] * sizeof(CGPoint));
        for (uint i = 0; i < [itemLayers count]; ++i) {
            pts[i] = [((NgTextLayer*)[itemLayers objectAtIndex:i]) centerPoint];
        }
        CGContextAddLines(ctx, pts, [itemLayers count]);
        CGContextClosePath(ctx);
        CGContextStrokePath(ctx);
        free(pts);
    }
# endif
}

- (void)layoutSublayers {
    [super layoutSublayers]; 
    [self relayoutItems];
}

@end

@implementation NgLayerDialLabelRingItem

@synthesize adaptContent;
@synthesize preferredSize;
@synthesize offset;

- (id)init {
    self = [super init];
    
    self.cornerRadius = 5.f;
    self.masksToBounds = YES;
    
    self.offset = 0;
    adaptContent = YES;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

NNT_END_OBJC