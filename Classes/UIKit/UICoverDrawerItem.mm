
# import "Core.h"
# import "UICoverDrawer.h"
# import "UICoverDrawerItem.h"
# import "NGDefines.h"
# import "NGLineStyle.h"
# import "NGFill.h"
# import "NGTextStyle.h"
# import <QuartzCore/QuartzCore.h>
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

@interface UICoverDrawerItemPrivate : NNTObject {
    UICoverDrawerItem *d_owner;
    NSTimer *timer_drag;
    BOOL is_dragging;
    NSSet *touches;
    BOOL drawer_old_scrollable;
}

@property (nonatomic, assign) UICoverDrawerItem *d_owner;
@property (nonatomic, retain) NSTimer *timer_drag;
@property (nonatomic) BOOL is_dragging;
@property (nonatomic, retain) NSSet *touches;

- (void)drag_start;
- (void)drag_cancel;
- (void)drag_end;

@end

@implementation UICoverDrawerItemPrivate

@synthesize d_owner;
@synthesize timer_drag;
@synthesize is_dragging;
@synthesize touches;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(timer_drag);
    zero_release(touches);
    [super dealloc];
}

- (void)drag_start {
    trace_msg(@"dragging start");
    
    is_dragging = YES;
    self.timer_drag = nil;
    
    if ([d_owner.drawer.delegate respondsToSelector:@selector(coverdrawerItemDragBegin:item:touchs:)])
        [d_owner.drawer.delegate coverdrawerItemDragBegin:d_owner.drawer item:d_owner touchs:touches];
    
    drawer_old_scrollable = d_owner.drawer.itemsScrollable;
    d_owner.drawer.itemsScrollable = NO;
    d_owner.drawer.draggingItem = d_owner;
}

- (void)drag_end {
    trace_msg(@"dragging end");
    
    is_dragging = NO;    
    d_owner.drawer.itemsScrollable = drawer_old_scrollable;
    d_owner.drawer.draggingItem = nil;
}

- (void)drag_cancel {
    self.timer_drag = nil;
    is_dragging = YES;
}

- (void)timer_drag_waiting {
    if (is_dragging) 
        return;
    self.timer_drag = nil;
    
    [self drag_start];
}

@end

@interface UICoverDrawerItem ()

- (void)__init;

@end

@implementation UICoverDrawerItem

@synthesize level;
@synthesize hdl_preitem, hdl_nextitem;
@dynamic shouldOnScreen;
@synthesize isOnScreen;
@synthesize drawer;
@synthesize contentSize;
@dynamic index_dyn;
@synthesize index_sta;
@synthesize image;
@synthesize title;
@synthesize draggable, interval_draggable;
@dynamic next, previous;

- (void)__init {
    NNTDECL_PRIVATE_INIT(UICoverDrawerItem);
    
    self.backgroundColor = [UIColor clearColor];
    self.contentSize = CGSizeZero;
    self.interval_draggable = .3f;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    [self __init];
    
    return self;
}

- (void)dealloc {
    zero_release(image);
    zero_release(title);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

+ (id)item {
    return [[[UICoverDrawerItem alloc] initWithZero] autorelease];
}

- (BOOL)shouldOnScreen {
    BOOL ret = NO;
    
    if (drawer.currentCover) {
        int offset = drawer.currentCover.level - level;
        ret = (offset >= 0) && (offset < drawer.maxCoversOnScreen);
    } else {
        ret = (level >= 0) && (level < drawer.maxCoversOnScreen);
    }
    
    return ret;
}

- (void)layoutSubviews {
    [super layoutSubviews];
}

- (void)forceHide {
    self.hidden = YES;
    self.isOnScreen = NO;
}

- (void)forceShow {
    self.hidden = NO;
    self.isOnScreen = YES;
}

- (CGSize)calcBestSize {
    if (!CGSizeEqualToSize(contentSize, CGSizeZero)) {
        return contentSize;
    }
    
    CGRect drawer_rc = drawer.bounds;
    CGSize drawer_sz = drawer_rc.size;
    
    if (!CGSizeEqualToSize(drawer.contentSize, CGSizeZero)) {
        return drawer.contentSize;
    }
    
    // calc by padding
    drawer_sz.width -= (real)drawer_sz.width * (drawer.padding_left + drawer.padding_right);
    drawer_sz.height -= (real)drawer_sz.height * (drawer.padding_top + drawer.padding_bottom);
    
    return drawer_sz;
}

- (CGRect)contentRect {
    CGRect rc = self.bounds;
    return rc;
}

- (void)drawRect:(CGRect)rect {
    if (CGRectEqualToRect(rect, CGRectZero))
        return;
    
    CGRect rc_client = self.bounds; 
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);                          
    
    if (image) {
        [image drawInRect:rc_client];
    }
    
    CGContextRestoreGState(context);
}

- (NSUInteger)index_dyn {
    NSUInteger ret = 0;
    UICoverDrawerItem *pre = self.hdl_preitem;
    while (pre) {
        ++ret;
        pre = pre.hdl_preitem;
    }
    return ret;
}

- (NSInteger)distance:(UICoverDrawerItem *)item {
    UICoverDrawerItem *each = self.hdl_preitem;
    NSInteger ret = -1;
    while (each) {
        if (each == item)
            return ret;
        --ret;
        each = each.hdl_preitem;
    }
    each = self.hdl_nextitem;
    ret = 1;
    while (each) {
        if (each == item)
            return ret;
        ++ret;
        each = each.hdl_nextitem;
    }
    return 0;
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    
    for (UIView *child in self.subviews) {
        child.frame = [self contentRect];
    }
}

- (UICoverDrawerItem*)next {
    UICoverDrawerItem *ret = self.hdl_nextitem;
    if (ret == nil &&
        drawer.enableRing) {
        
        ret = [drawer itemAtIndex:0];
        [self setFeatureAsNext:ret];
    }
    return ret;
}

- (UICoverDrawerItem*)previous {
    UICoverDrawerItem *ret = self.hdl_preitem;
    if (ret == nil && 
        drawer.enableRing) {
        
        ret = [drawer itemAtIndex:[drawer count] - 1];
        [self setFeatureAsPre:ret];
    }
    return ret;
}

- (void)setFeatureAsNext:(UICoverDrawerItem *)item {
    item.level = self.level - 1;
    item.layer.zPosition = self.layer.zPosition - 1;
}

- (void)setFeatureAsPre:(UICoverDrawerItem *)item {
    item.level = self.level + 1;
    item.layer.zPosition = self.layer.zPosition + 1;
}

- (void)addSubview:(UIView *)view {
    view.userInteractionEnabled = NO;
    [super addSubview:view];
}

# pragma mark -
# pragma mark event

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)__event {
    
    if (d_ptr.is_dragging) {
        if ([drawer.delegate respondsToSelector:@selector(coverdrawerItemDragEnd:item:touchs:)])
            [drawer.delegate coverdrawerItemDragEnd:drawer item:self touchs:touches];  
        [d_ptr drag_end];
    }
        
    if (draggable) {            
        d_ptr.timer_drag = [NSTimer scheduledTimerWithTimeInterval:interval_draggable 
                                                            target:d_ptr
                                                          selector:@selector(timer_drag_waiting)
                                                          userInfo:nil repeats:NO];
        d_ptr.touches = touches;
    }
    
    [drawer touchesBegan:touches withEvent:__event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)__event {
    if (d_ptr.timer_drag) {
        [d_ptr.timer_drag invalidate];
        d_ptr.timer_drag = nil;
    }
    
    if (d_ptr.is_dragging) {
        if ([drawer.delegate respondsToSelector:@selector(coverdrawerItemDragging:item:touchs:)])
            [drawer.delegate coverdrawerItemDragging:drawer item:self touchs:touches];
    }
    
    [drawer touchesMoved:touches withEvent:__event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)__event {
    if (d_ptr.timer_drag) {
        [d_ptr.timer_drag invalidate];
        d_ptr.timer_drag = nil;
    }
    
    if (d_ptr.is_dragging) {
        if ([drawer.delegate respondsToSelector:@selector(coverdrawerItemDragEnd:item:touchs:)])
            [drawer.delegate coverdrawerItemDragEnd:drawer item:self touchs:touches];                       
    }
    
    [drawer touchesEnded:touches withEvent:__event];
    
    if (d_ptr.is_dragging) {
        [d_ptr drag_end];
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)__event {
    [drawer touchesCancelled:touches withEvent:__event];
    
    if (d_ptr.is_dragging) {
        if ([drawer.delegate respondsToSelector:@selector(coverdrawerItemDragEnd:item:touchs:)])
            [drawer.delegate coverdrawerItemDragEnd:drawer item:self touchs:touches];  
        [d_ptr drag_end];
    }
}

@end

NNT_END_OBJC