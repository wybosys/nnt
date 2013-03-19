
# import "Core.h"
# import "UINavigationDial.h"
# import "UINavigationDialLayers.h"
# import "Math+NNT.h"
# import "WCABadgeIndicator.h"
# import "CoreGraphic+NNT.h"
# import "CGShadow.h"
# import <QuartzCore/QuartzCore.h>
# import "UIViewController+NNT.h"

NNT_BEGIN_OBJC

NSString *kSignalDialClicked = @"::nnt::uikit::dial::clicked";

@interface UINavigationDialPrivate : NSObject {
    UINavigationDial *d_owner;
    
    WCALayerDialRing *layer_ring;
    WCALayerDialLabelRing *layer_label;
    WCALayerDialRingCenter *layer_center;
    
    //real oldOuter;
    
    CGPoint pt_rotate;
    BOOL in_rotating;
    BOOL waiting_click;
    
    UISwipeGestureRecognizer *rgz_ges;
}

@property (nonatomic, assign) UINavigationDial *d_owner;
@property (nonatomic, retain) WCALayerDialRing *layer_ring;
@property (nonatomic, retain) WCALayerDialLabelRing *layer_label;
@property (nonatomic, retain) WCALayerDialRingCenter *layer_center;
@property (nonatomic, assign) CGPoint pt_rotate;
@property (nonatomic, assign) BOOL in_rotating, waiting_click;
@property (nonatomic, assign) UISwipeGestureRecognizer *rgz_ges;
//@property (nonatomic, assign) real oldOuter;

@end

@implementation UINavigationDialPrivate

@synthesize d_owner;
@synthesize layer_ring, layer_label, layer_center;
@synthesize pt_rotate, in_rotating, waiting_click;
@synthesize rgz_ges;
//@synthesize oldOuter;

- (id)init {
    self = [super init];
        
    layer_ring = [[WCALayerDialRing alloc] init]; 
    layer_label = [[WCALayerDialLabelRing alloc] init];
    layer_center = [[WCALayerDialRingCenter alloc] init];
    
    layer_label.hidden = YES;
    
    [d_owner.layer addSublayer:layer_label];
    [d_owner.layer addSublayer:layer_ring];    
    [d_owner.layer addSublayer:layer_center];
        
    rgz_ges = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(act_recognizer:)];
    rgz_ges.delaysTouchesEnded = NO;
    [d_owner addGestureRecognizer:rgz_ges];
    safe_release(rgz_ges);
        
    return self;
}

- (void)dealloc {
    zero_release(layer_ring);
    zero_release(layer_label);
    zero_release(layer_center);
    
    [super dealloc];
}

- (void)setIn_rotating:(BOOL)val {
    in_rotating = val;
    [d_owner showLabel:val];
}

# pragma mark recognizer

- (void)act_recognizer:(UISwipeGestureRecognizer*)rgz {
    if (rgz.state == UIGestureRecognizerStateEnded) {
        real tgt_angle = M_2PI_360;
        CGPoint pt = [rgz locationInView:d_owner];
        switch (rgz.direction) {
            case UISwipeGestureRecognizerDirectionUp:
            case UISwipeGestureRecognizerDirectionDown:
                tgt_angle *= pt.y;
                break;
            case UISwipeGestureRecognizerDirectionRight:
            case UISwipeGestureRecognizerDirectionLeft:
                tgt_angle *= pt.x;
                break;
        }
        
        [d_owner rotateAngle:tgt_angle animated:YES];
    }
}

@end

@interface UINavigationDial (hidden)

- (UINavigationDialItem*)_find_item_by_layer:(CALayer*)layer;

@end

@implementation UINavigationDial (hidden)

- (UINavigationDialItem*)_find_item_by_layer:(CALayer*)layer {
    NSUInteger idx = [d_ptr.layer_ring.itemLayers indexOfObject:layer];
    if (idx == NSNotFound)
        return nil;
    return [self.items objectAtIndex:idx null:nil];
}

@end

@implementation UINavigationDial

@synthesize dataSource, delegate;
@synthesize radiusInner, radiusOuter, radiusCollapse, radiusExpand;
@synthesize items;
@synthesize itemDefaultColor, itemSelectedColor, itemFill;
@synthesize dialFill, centerFill;
@synthesize labelFill, labelTextStyle, preferredLabelSize, labelOffset;
@synthesize clockwise;
@dynamic startAngle;
@synthesize isExpanded;
@dynamic dialInnerShadow, dialOutterShadow;
@synthesize itemEdgeShadow;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT(UINavigationDial);
    
    self.radiusOuter = 100;
    self.radiusInner = 40;
    self.radiusCollapse = 30;
    self.radiusExpand = 60;
    
    self.itemDefaultColor = [UIColor grayColor];
    self.itemSelectedColor = [UIColor blueColor];
    self.dialFill = [WCGFill fillWithColor:[WCGColor whiteColor]];
    self.centerFill = [WCGFill fillWithColor:[WCGColor blackColor]];
    self.labelFill = [WCGFill fillWithColor:[WCGColor blackColor]];
    self.labelOffset = 0;
    
    NgMutableTextStyle *ts = [[WCGMutableTextStyle alloc] init];
    ts.color = [WCGColor whiteColor];
    ts.fontSize = 30;
    ts.charRotation = -M_PI_2;
    self.labelTextStyle = ts;
    [ts release];
    
    itemEdgeShadow = [[CGShadow alloc] init];
    
    clockwise = YES;
    self.startAngle = -M_PI_2;
    
    self.isExpanded = NO;    
    self.sendGlobalEvent = NO;
        
    return self;
}

- (void)dealloc {
    zero_release(items);
    zero_release(itemDefaultColor);
    zero_release(itemSelectedColor);
    zero_release(dialFill);
    zero_release(centerFill);
    zero_release(labelFill);
    zero_release(labelTextStyle);
    zero_release(itemEdgeShadow);
    zero_release(itemFill);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalDialClicked)
NNTEVENT_END

- (void)setRadiusOuter:(real)val {
    radiusOuter = val;
    
    d_ptr.layer_ring.radiusOutter = radiusOuter;
    d_ptr.layer_label.radius = d_ptr.layer_ring.diameterOuter * .5f;
    //d_ptr.oldOuter = radiusOuter;
    
    CGRect frm = self.frame;
    frm.size = d_ptr.layer_ring.frame.size;
    self.frame = frm;
}

- (void)setRadiusInner:(real)val {
    radiusInner = val;
    
    d_ptr.layer_ring.radiusInner = radiusInner;
    
    CGRect frm = self.frame;
    frm.size = d_ptr.layer_ring.frame.size;
    self.frame = frm;
}

- (void)setRadiusCollapse:(real)val {
    radiusCollapse = val;
    
    d_ptr.layer_center.radiusCollapse = val;
}

- (void)setRadiusExpand:(real)val {
    radiusExpand = val;
    
    d_ptr.layer_center.radiusExpend = val;
}

- (void)setDialInnerShadow:(CGShadow *)shadow {
    d_ptr.layer_ring.ringShadowInner = shadow;
}

- (CGShadow*)dialInnerShadow {
    return d_ptr.layer_ring.ringShadowInner;
}

- (void)setDialOutterShadow:(CGShadow*)shadow {
    d_ptr.layer_ring.ringShadowOuter = shadow;
}

- (CGShadow*)dialOutterShadow {
    return d_ptr.layer_ring.ringShadowOuter;
}

- (real)startAngle {
    //return d_ptr.layer_label.startAngle;
    return d_ptr.layer_ring.startAngle;
}

- (void)setStartAngle:(real)val {
    d_ptr.layer_label.startAngle = val;
    d_ptr.layer_ring.startAngle = val;
}

- (void)setDialFill:(NgFill *)color {
    [NSObject refobjSet:&dialFill obj:&color];
    d_ptr.layer_ring.backgroundFill = color;
}

- (void)setCenterFill:(NgFill *)color {
    [NSObject refobjSet:&centerFill obj:&color];
    d_ptr.layer_center.backgroundFill = color;
}

- (void)setItems:(NSArray *)arr {    
    d_ptr.layer_ring.itemLayers = nil;
    [items release];
    
    if (clockwise) {
        items = [arr retain];
    } else {
        NSMutableArray *tmp = [NSMutableArray arrayWithArray:[arr reverse]];
        [tmp rightRotate];
        items = [tmp retain];
    }
    
    NSMutableArray *layers = [[NSMutableArray alloc] initWithCapacity:[arr count]];
    NSMutableArray *titles = [[NSMutableArray alloc] initWithCapacity:[arr count]];
    
    //int i = 0;
    for (UINavigationDialItem *item in items) {
        // test
        //item.badgeValue = [NSString stringWithFormat:@"test %d", i++];
        
        // set.
        if (!CGSizeEqualToSize(preferredLabelSize, CGSizeZero)) {
            item.layerLabel.preferredSize = preferredLabelSize;
            item.layerLabel.adaptContent = NO;
        }
        
        item.layerLabel.offset = labelOffset;
        item.layerItem.edgeShadow = itemEdgeShadow;
        item.layerItem.backgroundFill = itemFill;
        
        // add layer.
        [layers addObject:item.layerItem];
        [titles addObject:item.layerLabel];
    }
    
    d_ptr.layer_ring.itemLayers = layers;
    d_ptr.layer_label.itemLayers = titles;
    
    [layers release];
    [titles release];
}

- (void)setPreferredLabelSize:(CGSize)sz {
    preferredLabelSize = sz;
    BOOL adapt = CGSizeEqualToSize(preferredLabelSize, CGSizeZero);
    for (UINavigationDialItem *item in items) {
        item.layerLabel.preferredSize = preferredLabelSize;
        item.layerLabel.adaptContent = adapt;
    }
}

- (void)setIsExpanded:(BOOL)val {
    isExpanded = val;
    
    if (val) {
        [d_ptr.layer_center setRadius:d_ptr.layer_center.radiusCollapse];        
        d_ptr.layer_ring.hidden = NO;
        //self.radiusOuter = d_ptr.oldOuter;
    } else {
        [d_ptr.layer_center setRadius:d_ptr.layer_center.radiusExpend];        
        d_ptr.layer_ring.hidden = YES;
        //self.radiusOuter = self.radiusCollapse;
    }
    
    CGPoint pt_center = self.clientCenter;
    [d_ptr.layer_center moveToCenter:pt_center];
}

- (void)showLabel:(BOOL)val {
    d_ptr.layer_label.hidden = !val;
}

- (void)setClockwise:(BOOL)val {
    clockwise = val;
    d_ptr.layer_label.clockwise = val;
}

@end

@implementation UINavigationDial (interactive)

- (BOOL)hitTest:(CGPoint)pt {
    CGPoint centerpt = [d_ptr.layer_ring clientCenterPoint];
    real distance = distance_points2d(pt.x, pt.y, centerpt.x, centerpt.y);

    if (distance > radiusInner && distance < radiusOuter)
        return YES;
    
    return NO;
}

- (void)rotateAngle:(real)angle animated:(BOOL)animated {
    real res = self.startAngle + angle;
    [self rotateToAngle:res animated:animated];
}

- (void)rotateToAngle:(real)angle animated:(BOOL)animated {
    real res = M_2PI_RESTRICT(angle);
    
    [CATransaction begin];
    if (animated) {        
        [CATransaction setAnimationDuration:.5f];        
    } else {
        [CATransaction setDisableActions:YES];
    }
    
    self.startAngle = res;
    [CATransaction commit];
}

@end

@interface UINavigationDial (event)

@end

@implementation UINavigationDial (event)

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)__event {
    CGPoint pt = [[touches anyObject] locationInView:self];
    
    if (isExpanded) {
        d_ptr.in_rotating = [self hitTest:pt];
        if (d_ptr.in_rotating) {            
            d_ptr.pt_rotate = pt;                      
        }
    }
        
    d_ptr.waiting_click = YES;  
    
    [super touchesBegan:touches withEvent:__event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)__event {
    CGPoint pt = [[touches anyObject] locationInView:self];
    
    if (d_ptr.waiting_click) {
        CALayer *layer = nil;
        
        // if click a item.
        if (isExpanded) {
            layer = [d_ptr.layer_ring hitTest:pt];
            if (layer) {
                UINavigationDialItem *item = [self _find_item_by_layer:layer];
                if (item) {
                    [self emit:kSignalDialClicked result:item];
                }
            }
        }
        
        // if click expand.
        CGPoint npt = [d_ptr.layer_center convertPoint:pt fromLayer:self.layer];
        if ([d_ptr.layer_center containsPoint:npt]) {
            self.isExpanded = !self.isExpanded;
        }
    }
    
    d_ptr.in_rotating = NO;
    d_ptr.waiting_click = NO;
    
    [super touchesEnded:touches withEvent:__event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)__event {
    CGPoint pt = [[touches anyObject] locationInView:self];    
    CGPoint pt_center = [d_ptr.layer_ring clientCenterPoint];
    
    if (isExpanded) {
        BOOL onring = [self hitTest:pt];
        if (onring && d_ptr.in_rotating) {
            real dangle_x = pt.x - d_ptr.pt_rotate.x;
            real dangle_y = pt.y - d_ptr.pt_rotate.y;
            real dangle = 0;                
            
            if (ABS(dangle_x) > ABS(dangle_y)) {            
                dangle = dangle_x;
                if (pt.y > pt_center.y){
                    dangle = -dangle; 
                }
            } else {
                dangle = dangle_y;
                if (pt.x < pt_center.x){
                    dangle = -dangle;
                }
            }
            
            dangle = (dangle / radiusOuter) * M_PI_2;
            [self rotateAngle:dangle animated:NO];
            
            d_ptr.pt_rotate = pt;
        }
    }
    
    d_ptr.waiting_click = NO;
    
    [super touchesMoved:touches withEvent:__event];
}

@end

@implementation UINavigationDialItem

@synthesize layerItem, layerLabel, layerBadge;
@synthesize imageMaskColor;
@synthesize viewController;
@synthesize labelFill, labelTextStyle;
@synthesize badgeValue;

- (id)init {
    self = [super init];
    
    layerItem = [[WCALayerDialRingItem alloc] init];
    layerLabel = [[WCALayerDialLabelRingItem alloc] init];
    layerBadge = [[WCABadgeIndicator alloc] init];
    
    return self;
}

- (void)dealloc {
    zero_release(layerItem);
    zero_release(layerLabel);
    zero_release(layerBadge);
    
    zero_release(viewController);
    zero_release(imageMaskColor);
    
    zero_release(badgeValue);
    
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalValueChanged)
NNTEVENT_END

- (void)setViewController:(NNTUIViewController *)ctlr {
    [NSObject refobjSet:&viewController obj:&ctlr];
    
    layerItem.image = ctlr.titleImage.CGImage;
    layerLabel.string = ctlr.title;
}

- (void)setImageMaskColor:(UIColor *)color {
    [NSObject refobjSet:&imageMaskColor obj:&color];
    layerItem.imageMaskColor = imageMaskColor;
    
    [self setNeedsDisplay];
}

- (void)setLabelFill:(NgFill *)color {
    [NSObject refobjSet:&labelFill obj:&color];
    
    layerLabel.backgroundFill = color;
}

- (void)setLabelTextStyle:(NgTextStyle *)ts {
    [NSObject refobjSet:&labelTextStyle obj:&ts];
    layerLabel.textStyle = ts;
}

- (void)setNeedsDisplay {
    [layerItem setNeedsDisplay];
    [layerLabel setNeedsDisplay];
    [layerBadge setNeedsDisplay];
}

- (void)setBadgeValue:(NSString*)val {
    // set value.
    [badgeValue release];
    badgeValue = [val copy];
    
    // replace layer.
    if (badgeValue == nil) {
        layerItem.layerBadge = nil;
    } else {
        self.layerBadge.value = val;
        layerItem.layerBadge = self.layerBadge;
    }
    
    // event.
    [self emit:kSignalValueChanged];
}

@end

NNT_END_OBJC