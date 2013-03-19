
# import "Core.h"
# import "UICoverDrawer.h"
# import "UICoverDrawerItem.h"
# import "UICoverDrawerView.h"
# import "Math+NNT.h"
# import "UIFogView.h"
# import <QuartzCore/QuartzCore.h>
# import "NGTextStyle.h"
# import "NGGradient.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

@interface UICoverDrawer (hidden)

- (real)angle_h;
- (real)angle_v;
- (void)set_current:(UICoverDrawerItem*)item;

@end

@interface UICoverDrawerPrivate : NSObject {
    NSMutableArray *items;        
    NSUInteger rcd_idx_max;    
    UICoverDrawerView *drawerView;
}

@property (nonatomic, assign) UICoverDrawer *d_owner;
@property (nonatomic, retain) NSMutableArray *items;
@property (nonatomic, assign) NSUInteger rcd_idx_max;
@property (nonatomic, readonly) UICoverDrawerView *drawerView;

//! load covers.
- (void)loadCovers;

//! display item.
- (void)display_item:(UICoverDrawerItem*)item animated:(BOOL)animated;

//! undisplay item.
- (void)undisplay_item:(UICoverDrawerItem*)item animated:(BOOL)animated;

//! movedown.
- (void)movedown_item:(UICoverDrawerItem*)item animated:(BOOL)animated;

//! moveup.
- (void)moveup_item:(UICoverDrawerItem*)item animated:(BOOL)animated;

//! relayoutItems;
- (void)relayout_items;

- (UICoverDrawerItem*)find_item_bylayer_onscreen:(CALayer*)layer;
- (UICoverDrawerItem*)find_item_bylayer:(CALayer*)layer;

@end

@implementation UICoverDrawerPrivate

@synthesize d_owner;
@synthesize items;
@synthesize rcd_idx_max;
@synthesize drawerView;

- (id)init {
    self = [super init];
    
    items = [[NSMutableArray alloc] init];
    
    drawerView = [[UICoverDrawerView alloc] initWithFrame:d_owner.bounds];
    [d_owner addSubview:drawerView];
    drawerView.drawer = d_owner;
    
    return self;
}

- (void)dealloc {
    zero_release(items);
    [drawerView release];
    [super dealloc];
}

- (void)loadCovers {        
    NNT_AUTORELEASEPOOL_BEGIN;
    
    uint number = d_owner.numberCovers;
    if ([d_owner.dataSource respondsToSelector:@selector(coverdrawerNumberCovers:)]) {
        number = [d_owner.dataSource coverdrawerNumberCovers:d_owner];
    }

    for (uint idx = [items count]; idx < number; ++idx) {
        UICoverDrawerItem *item = nil;
        
        if ([d_owner.dataSource respondsToSelector:@selector(coverdrawerCover:idx:)]) {
            item = [d_owner.dataSource coverdrawerCover:d_owner idx:idx];
        }
        
        if (item == nil) {
            item = [UICoverDrawerItem item];
        }
        
        [d_owner appendItem:item];
        
        [self performSelectorOnMainThread:@selector(thd_insert_item:) withObject:item waitUntilDone:YES];
    }
    
    [d_owner performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:YES];
    
    NNT_AUTORELEASEPOOL_END;
}

- (void)thd_insert_item:(UICoverDrawerItem*)item {
    if (item.shouldOnScreen is_no)
        return;
    
    item.layer.transform = CATransform3DIdentity;
    
    CGRect rc_new = [d_owner calcItemRect:item];
    if (!CGRectEqualToRect(rc_new, item.frame))
        [item setFrame:rc_new];
    
    item.layer.hidden = NO;
    item.isOnScreen = YES;
    
    item.layer.transform = [d_owner calcItemTransform:item];
}

- (void)display_item:(UICoverDrawerItem *)item animated:(BOOL)animated {
    CGRect rc_new = [d_owner calcItemRect:item];
    
    CGRect *rect = nil;
    if (!CGRectEqualToRect(rc_new, item.frame)) {
        rect = &rc_new;
        [item moveToCenter:CGRectCenterPoint(&rc_new)];
    }
    
    if (animated) {
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
        [UIView setAnimationBeginsFromCurrentState:YES];
        [UIView setAnimationDuration:1.f];
    }
    
    if (rect) {
        [item setFrame:*rect];
    }
    
    item.layer.opacity = 1.f;
    
    [item forceShow];
    [item setNeedsDisplay];
    
    if (animated) {
        [UIView commitAnimations];
    }
}

- (void)undisplay_item:(UICoverDrawerItem *)item animated:(BOOL)animated {
    if (!animated) {
        [item forceHide];
        return;
    }            
    
    CGRect rc_new = [d_owner calcItemRect:item];
    CGRect *rect = nil;
    if (!CGRectEqualToRect(rc_new, item.frame)) {
        rect = &rc_new;
    }
    
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
    [UIView setAnimationBeginsFromCurrentState:YES];
    [UIView setAnimationDuration:1.f];
    
    if (rect) {
        [item setFrame:*rect];
    }
    
    item.layer.opacity = 0.f;
    [item setNeedsDisplay];
    
    [UIView setAnimationDelegate:item];
    [UIView setAnimationDidStopSelector:@selector(forceHide)];
    [UIView commitAnimations];
}

- (void)moveup_item:(UICoverDrawerItem *)item animated:(BOOL)animated {    
    // set transform
    //CATransform3D mat = [d_owner calcItemTransform:item];
    item.layer.transform = CATransform3DIdentity;
        
    // set rect
    ++item.level;
    item.layer.zPosition += d_owner.itemZPosStep;
    if (!item.shouldOnScreen && item.isOnScreen) {
        [self undisplay_item:item animated:animated];
    } else if (item.shouldOnScreen && !item.isOnScreen) {
        [self display_item:item animated:animated];
    } else if (item.isOnScreen) {
        CGRect rc_new = [d_owner calcItemRect:item];
        if (!CGRectEqualToRect(rc_new, item.frame)) {
            
            if (animated) {
                [UIView beginAnimations:nil context:nil];
                [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
                [UIView setAnimationBeginsFromCurrentState:YES];
                [UIView setAnimationDuration:1.f];
            }
            
            [item setFrame:rc_new];
            [item setNeedsDisplay];
            
            if (animated) {
                [UIView commitAnimations];
            }
            
        }
    }
    
    item.layer.transform = [d_owner calcItemTransform:item];
}

- (void)movedown_item:(UICoverDrawerItem *)item animated:(BOOL)animated {    
    // set transform
    //CATransform3D mat = [d_owner calcItemTransform:item];
    item.layer.transform = CATransform3DIdentity;
    
    // set rect.
    --item.level;
    item.layer.zPosition -= d_owner.itemZPosStep;
    if (!item.shouldOnScreen && item.isOnScreen) {
        [self undisplay_item:item animated:animated];
    } else if (item.shouldOnScreen && !item.isOnScreen) {
        [self display_item:item animated:animated];
    } else if (item.isOnScreen) {
        CGRect rc_new = [d_owner calcItemRect:item];
        if (!CGRectEqualToRect(rc_new, item.frame)) {
            
            if (animated) {
                [UIView beginAnimations:nil context:nil];
                [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
                [UIView setAnimationBeginsFromCurrentState:YES];
                [UIView setAnimationDuration:1.f];
            }
            
            [item setFrame:rc_new];
            [item setNeedsDisplay];
            
            if (animated) {
                [UIView commitAnimations];
            }
            
        }
    }
        
    // set mat.
    item.layer.transform = [d_owner calcItemTransform:item];
}

- (UICoverDrawerItem*)find_item_bylayer:(CALayer *)layer {
    for (UICoverDrawerItem *item in items) {
        if ([item.layer isEqual:layer]) {
            return item;
        }
    }
    return nil;
}

- (UICoverDrawerItem*)find_item_bylayer_onscreen:(CALayer *)layer {
    if (d_owner.currentCover == nil)
        return nil;
    if ([d_owner.currentCover.layer isEqual:layer])
        return d_owner.currentCover;
    UICoverDrawerItem *item = nil;
    item = d_owner.currentCover.hdl_preitem;
    while (item && item.isOnScreen) {
        if ([item.layer isEqual:layer])
            return item;
        item = item.hdl_preitem;
    }
    item = d_owner.currentCover.hdl_nextitem;
    while (item && item.isOnScreen) {
        if ([item.layer isEqual:layer])
            return item;
        item = item.hdl_nextitem;
    }
    // find by parent.
    if (layer.superlayer)
        return [self find_item_bylayer_onscreen:layer.superlayer];
    return nil;
}

- (void)relayout_items {
    if (!d_owner.currentCover)
        return;
    [self display_item:d_owner.currentCover animated:NO];
    UICoverDrawerItem *item = nil;
    item = d_owner.currentCover.hdl_preitem;
    while (item && item.isOnScreen) {
        [self display_item:item animated:NO];
        item = item.hdl_preitem;
    }
    item = d_owner.currentCover.hdl_nextitem;
    while (item && item.isOnScreen) {
        [self display_item:item animated:NO];
        item = item.hdl_nextitem;
    }
}

@end

@implementation UICoverDrawer (hidden)

# define _initialize \
maxCoversOnScreen = 6; \
minCoversOnScreen = 1; \
padding_left = .1f; \
padding_right = .1f; \
padding_top = .1f; \
padding_bottom = .1f; \
contentSize = CGSizeZero; \
itemSpacing = 20.f; \
itemAngle = itemAngleStep = itemPositionStep = (point3df){0}; \
itemDraggable = YES; \
viewportDepth = 200.f; \
viewportDistance = .0f; \
self.viewportAngle = 0.01f; \
enableRing = NO; \
itemsScrollable = YES; \
draggingDamp = 1.f; \
itemZPosStep = 10.f; \
itemZPosition = 0.f;

- (real)angle_h {
    real ret = self.bounds.size.width * .5f;
    ret = atan2r(ret, self.viewportDepth);
    return ret + ret;    
}

- (real)angle_v {
    real ret = self.bounds.size.height * .5f;
    ret = atan2r(ret, self.viewportDepth);
    return ret + ret;  
}

- (void)set_current:(UICoverDrawerItem *)item {
    UICoverDrawerItem *old = currentCover;
    currentCover = item;
    if (item || old) {
        if ([self.delegate respondsToSelector:@selector(coverdrawerItemSelectedChanged:cur:pas:)]) {
            [self.delegate coverdrawerItemSelectedChanged:self cur:item pas:old];
        }
    }
}

@end

@implementation UICoverDrawer

@synthesize dataSource, delegate, isDataSourceNeedRelease, isDelegateNeedRelease;
@synthesize currentCover, numberCovers;
@synthesize maxCoversOnScreen, minCoversOnScreen;
@synthesize padding_top, padding_left, padding_right, padding_bottom;
@synthesize contentSize;
@synthesize viewportDepth, viewportDistance, viewportAngle;
@synthesize draggingItem, draggingDamp;
@synthesize enableRing;
@synthesize itemSpacing, itemDefaultImage, itemDraggable, itemAngle, itemAngleStep, itemsScrollable, itemZPosStep, itemZPosition, itemPositionStep;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT(UICoverDrawer);       
    _initialize;    
    return self;
}

- (void)dealloc {        
    zero_release(itemDefaultImage);
    
    if (isDataSourceNeedRelease)
        zero_release(dataSource);
    if (isDelegateNeedRelease)
        zero_release(delegate);
    
    self.dataSource = nil;
    self.delegate = nil;
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)setViewportAngle:(real)__viewportAngle {
    if (viewportAngle == __viewportAngle)
        return;
    viewportAngle = __viewportAngle;
    
    if (viewportAngle == 0)
        [d_ptr.drawerView.layer setSublayerTransform:CATransform3DIdentity];
    else {
        CATransform3D mat = CATransform3DIdentity;
        mat.m34 = -viewportAngle;            
        [d_ptr.drawerView.layer setSublayerTransform:mat];
    }
}

- (UICoverDrawerItem*)insertItem:(UICoverDrawerItem *)item idx:(uint)idx {
    NNT_SYNCHRONIZED(self)
    
    UICoverDrawerItem *pre = nil, *next = nil;

    if (idx == -1) {
        if ([d_ptr.items count]) {
            pre = [d_ptr.items objectAtIndex:[d_ptr.items count] - 1];
        }
        [d_ptr.items addObject:item];
    } else {
        if (idx != 0) {
            pre = [d_ptr.items objectAtIndex:idx - 1];
        }
        next = [d_ptr.items objectAtIndex:idx];
        [d_ptr.items insertObject:item atIndex:idx];
    }
    
    item.index_sta = d_ptr.rcd_idx_max++;
    
    item.hdl_preitem = pre;
    if (pre)
        pre.hdl_nextitem = item;
    item.hdl_nextitem = next;
    if (next)
        next.hdl_preitem = item;
    
    item.level = pre ? pre.level - 1 : self.maxCoversOnScreen - 1;
    item.layer.zPosition = pre ? (pre.layer.zPosition - itemZPosStep) : itemZPosition;
    
    if (next) {
        UICoverDrawerItem *t_next = next;
        while (t_next) {
            if (t_next.level == 0) {
                [d_ptr undisplay_item:t_next animated:NO];
            }
            t_next.level -= 2;
            t_next.layer.zPosition -= itemZPosStep;
            t_next = t_next.hdl_nextitem;
        }
    }
    
    item.drawer = self;
    if (item.image == nil)
        item.image = self.itemDefaultImage;
    item.draggable = self.itemDraggable;    
    
    if ([delegate respondsToSelector:@selector(coverdrawerItemAdded:item:)]) {
        [delegate coverdrawerItemAdded:self item:item];
    }
    
    item.layer.hidden = YES;
    
    if (pre) {
        [d_ptr.drawerView insertSubview:item belowSubview:pre];
    } else {
        [d_ptr.drawerView addSubview:item];
    }
    
    // set select
    if (item.level == self.maxCoversOnScreen - 1) {
        [self selectItem:item animated:NO];
    }
    
    NNT_SYNCHRONIZED_END
    return item;
}

- (UICoverDrawerItem*)appendItem:(UICoverDrawerItem *)item {
    return [self insertItem:item idx:-1];
}

- (UICoverDrawerItem*)itemAtIndex:(uint)idx {
    return [d_ptr.items objectAtIndex:idx];
}

- (uint)count {
    return [d_ptr.items count];
}

- (void)clear {
    NNT_SYNCHRONIZED(self)
    
    for (UICoverDrawerItem *item in d_ptr.items) {
        [item removeFromSuperview];
    }
    [d_ptr.items removeAllObjects];
    [self set_current:nil];
    d_ptr.rcd_idx_max = 0;
    
    NNT_SYNCHRONIZED_END
}

- (uint)indexOfItem:(const UICoverDrawerItem *)item {
    return [d_ptr.items indexOfObject:item];
}

- (void)reloadData {
    [self clear];    
    [d_ptr loadCovers];
}

- (CGPoint)contentPosition {
    CGRect rc = self.bounds;
    real left = rc.size.width * padding_left;
    real top = rc.size.height * padding_top;
    return CGPointMake(left, top);
}

- (uint)countOnScreen {
    uint ret = 0;
    UICoverDrawerItem *each = currentCover;
    while (each) {
        if (each.isOnScreen)
            ++ret;
        each = each.next;
        if (each == currentCover)
            break;
    }
    return ret;
}

- (void)selectItem:(UICoverDrawerItem *)item animated:(BOOL)animated {
    if (item == nil)
        return;
    
    if (item == currentCover)
        return;

    if (currentCover) {        
        NSInteger distance = [currentCover distance:item];
        if (distance > 0) {
            for (uint idx = 0; idx < abs(distance); ++idx) {
                [self moveOut:animated];
            }
        } else {
            for (uint idx = 0; idx < abs(distance); ++idx) {
                [self moveIn:animated];
            }
        }
    } else {
        [self set_current:item];
    }
}

- (void)moveOut:(BOOL)animated {
    if (!currentCover || currentCover.next == nil)
        return;
    if ([self countOnScreen] <= minCoversOnScreen)
        return;
    
    UICoverDrawerItem *old_cur = currentCover;
    UICoverDrawerItem *each = currentCover;
    [self set_current:currentCover.next];
    while (each) {
        [d_ptr moveup_item:each animated:animated];
        each = each.hdl_preitem;
    }
    each = old_cur.next;
    while (each) {
        [d_ptr moveup_item:each animated:animated];
        each = each.hdl_nextitem;
    }        
}

- (void)moveIn:(BOOL)animated {
    if (!currentCover || currentCover.previous == nil)
        return;
    
    UICoverDrawerItem *old_cur = currentCover;
    [self set_current:currentCover.previous];
    [d_ptr movedown_item:currentCover animated:animated];
    
    UICoverDrawerItem *each = old_cur;
    while (each) {
        [d_ptr movedown_item:each animated:animated];
        each = each.hdl_nextitem;
    }
    
    each = currentCover.previous;
    while (each) {
        [d_ptr movedown_item:each animated:animated];
        each = each.hdl_preitem;
    }
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    
    [d_ptr relayout_items];
}

- (void)relayoutData {
    [d_ptr relayout_items];
}

- (void)layoutSubviews {    
    d_ptr.drawerView.frame = self.bounds;
}

- (CATransform3D)calcItemTransform:(UICoverDrawerItem *)item {
    CATransform3D ret = CATransform3DIdentity;    
    real depth = self.currentCover ? self.currentCover.level - item.level : item.level;
    //double div = 1 / self.maxCoversOnScreen * (self.maxCoversOnScreen - depth);
    double div = depth / self.maxCoversOnScreen;        
    
    real anglex = self.itemAngle.x + self.itemAngleStep.x * div;
    ret = CATransform3DRotate(ret, anglex, -1, 0, 0);
    
    real angley = self.itemAngle.y + self.itemAngleStep.y * div;
    ret = CATransform3DRotate(ret, angley, 0, -1, 0);
    
    real anglez = self.itemAngle.z + self.itemAngleStep.z * div;
    ret = CATransform3DRotate(ret, anglez, 0, 0, -1);        
    
    ret = CATransform3DTranslate(ret, self.itemPositionStep.x * depth, self.itemPositionStep.y * depth, self.itemPositionStep.z * depth);
    
    return ret;
}

- (CGRect)calcItemRect:(UICoverDrawerItem *)item {
    real depth = self.currentCover ? (self.currentCover.level - item.level) : item.level;
    depth *= self.itemSpacing;
    depth += self.viewportDistance;
    
    real offset_h = 0;
    real offset_v = 0;
    
    if (depth) {        
        real angle_h = [self angle_h] * .5f;
        real angle_v = [self angle_v] * .5f;
        
        offset_h = tanr(angle_h) * depth * d_ptr.drawerView.scale;
        offset_v = tanr(angle_v) * depth * d_ptr.drawerView.scale;
    }
    
    // recalc size
    CGRect rc;
    rc.origin = [self contentPosition];
    rc.size = [item calcBestSize];
    if (offset_h || offset_v) {                
        rc.size.width -= offset_h + offset_h;
        rc.size.height -= offset_v;
        
        rc.origin.x += offset_h;
        rc.origin.y -= offset_v;
    }        
    
    return rc;
}

# pragma mark route to main view

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)__event {
    [d_ptr.drawerView touchesBegan:touches withEvent:__event];
    [super touchesBegan:touches withEvent:__event];    
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)__event {
    [d_ptr.drawerView touchesCancelled:touches withEvent:__event];
    [super touchesCancelled:touches withEvent:__event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)__event {
    [d_ptr.drawerView touchesEnded:touches withEvent:__event];
    [super touchesEnded:touches withEvent:__event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)__event {
    [d_ptr.drawerView touchesMoved:touches withEvent:__event];
    [super touchesMoved:touches withEvent:__event];
}

@end

@implementation UICoverDrawer (_extern_)

- (UICoverDrawerItem*)find_item_bylayer_onscreen:(CALayer *)layer {
    return [d_ptr find_item_bylayer_onscreen:layer];
}

@end

NNT_END_OBJC