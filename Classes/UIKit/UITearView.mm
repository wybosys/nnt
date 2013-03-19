
# import "Core.h"
# import "UITearView.h"
# import "UIDesktop.h"
# import "CoreGraphic+WSI.h"
# import "UIColor+WSI.h"
# import <QuartzCore/QuartzCore.h>

WSI_BEGIN_OBJC

signal_t kSignalViewClose = @"::wsi::view::close";

@interface UITearMaskDesk : WSIUIDesktop {
    UITearView *_tear;
    BOOL _closing;
}

@property (nonatomic, assign) UITearView *tear;

@end

@implementation UITearMaskDesk

@synthesize tear = _tear;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    [self connect:kSignalTouchesEnd sel:@selector(_act_close_tear:)];
    
    return self;
}

- (void)_act_close_tear:(WSIEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    if (_tear.autoClose && !_closing) {
        _closing = YES;
        CGPoint pt = [[touches anyObject] locationInView:_tear];
        CGRect rect = _tear.contentRect;
        if (!CGRectContainsPoint(rect, pt)) {
            [_tear close];
        }
    }
}

@end

struct _element_info {
    UIView *view;
    CGRect  rect;
    BOOL    changed;
};

typedef wsi::core::vector<_element_info> _element_infos;

@interface UITearViewPrivate : NSObject {
    UITearView *d_owner;
    
    //! store all old infos.
    _element_infos *element_infos;
    
    // mask desktop.
    UITearMaskDesk *desktop;
}

@property (nonatomic, assign) UITearView *d_owner;
@property (nonatomic, assign) _element_infos *element_infos;
@property (nonatomic, retain) UITearMaskDesk *desktop;

@end

@implementation UITearViewPrivate

@synthesize d_owner;
@synthesize element_infos;
@synthesize desktop;

- (id)init {
    self = [super init];
    
    element_infos = new _element_infos;
    desktop = [[UITearMaskDesk alloc] init];
    desktop.tear = d_owner;
    //[desktop addSubview:d_owner];
    
    return self;
}

- (void)dealloc {
    delete element_infos; element_infos = NULL;
    zero_release(desktop);
    
    [super dealloc];
}

@end

@interface UITearView ()

//! find element info by UIView.
- (_element_info*)find_info:(UIView*)view;

//! add info.
- (void)add_info:(_element_info*)info;

//! get desktop.
- (WSIUIDesktop*)desktop;

//! show source view.
- (void)showSourceView;

//! lock & unlock source view.
- (void)lockSourceView;
- (void)unlockSouceView;

@end

@implementation UITearView

@synthesize targetView, sourceView;
@synthesize location, spacing;
@synthesize edgeShadow, fill, edgeColor, edgeWidth;
@synthesize lenArrow, locationArrow;
@dynamic contentRect;
@synthesize autoClose;
@synthesize contentView;
@synthesize darkColor;
@synthesize desktopMode;
@synthesize padding;

- (id)initWith:(NSInteger)__pos spacing:(NSUInteger)__spacing {
    self = [super init];
    WSIDECL_PRIVATE_INIT(UITearView);
    
    location = __pos;
    spacing = __spacing;
    desktopMode = YES;
    
    self.backgroundColor = [UIColor clearColor];
    self.edgeShadow = [CGShadow shadow];
    self.edgeShadow.shadowColor = [WCGColor colorWithRGBA:0x00000060];
    edgeShadow.radius = 1;
    edgeShadow.opacity = 20;
    
    self.edgeColor = [UIColor blackColor];
    edgeWidth = 2;
    
    lenArrow = 20;
    locationArrow = 0;
    padding = CGPaddingZero;
    
    self.fill = [WCGFill fillWithColor:[WCGColor whiteColor]];
    
    autoClose = YES;
    
    self.layer.masksToBounds = YES;
    
    self.darkColor = [UIColor colorWithRGBA:0x00000060];
    
    return self;
}

- (void)dealloc {
    zero_release(edgeShadow);
    zero_release(fill);
    zero_release(edgeColor);
    zero_release(darkColor);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalViewClose)
WSIEVENT_END

- (void)setDarkColor:(UIColor *)__darkColor {
    [darkColor release];
    darkColor = [__darkColor retain];
    
    if (darkColor) {
        d_ptr.desktop.backgroundColor = darkColor;
    } else {
        d_ptr.desktop.backgroundColor = [UIColor clearColor];
    }
}

- (void)open {
    [self open:YES];
}

- (void)open:(BOOL)animated {
    if (desktopMode) {
        if (self.superview != d_ptr.desktop) {
            [d_ptr.desktop addSubview:self];
        }        
    } else {
        [self.targetView addSubview:self];
    }
    
    // lock source view.
    [self lockSourceView];
    
    // clear old infos.
    d_ptr.element_infos->clear();
    
    // increse of close.
    [self retain];
    
    if (desktopMode) {
        // show desktop.
        [d_ptr.desktop show:NO];
    }
    
    // show source.
    [self showSourceView];
}

- (void)close {
    [self close:YES];
}

- (void)close:(BOOL)animated {
    
    self.contentView = nil;
    
    if (animated) {
        [self freeze];
        
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDidStopSelector:@selector(act_close)];
    }
    
    for (_element_infos::iterator iter = d_ptr.element_infos->begin(); iter != d_ptr.element_infos->end(); ++iter) {
        _element_info& info = *iter;
        if (info.changed) {
            info.view.frame = info.rect;
        }
    }
    
    if (animated) {
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, 1);
        
        if (desktopMode) {
            d_ptr.desktop.backgroundColor = [UIColor clearColor];
        }
        
        [UIView commitAnimations];
    }
    
    if (!animated) {
        // remove
        [self removeFromSuperview];
        
        // signal.
        [self emit:kSignalViewClose];
        
        // release
        [self release];
        
        if (desktopMode) {
            // close deaktop
            [d_ptr.desktop close:NO];        
        }
    }

    [self unlockSouceView];
}

- (void)act_close {
    [self removeFromSuperview];
    
    // signal.
    [self emit:kSignalViewClose];
    
    [self release];
    [self thaw];
    
    if (desktopMode) {
        [d_ptr.desktop close:NO];
    }
}

- (_element_info*)find_info:(UIView *)view {
    for (_element_infos::iterator iter = d_ptr.element_infos->begin(); iter != d_ptr.element_infos->end(); ++iter) {
        if (iter->view == view) {
            return &*iter;
        }
    }
    return NULL;
}

- (WSIUIDesktop*)desktop {
    return d_ptr.desktop;
}

- (void)add_info:(_element_info *)info {
    *d_ptr.element_infos << *info;
}

- (CGRect)contentRect {
    CGRect rc = self.bounds;
    rc.origin.x += padding.left;
    rc.origin.y += lenArrow + padding.top;
    rc.size.height -= lenArrow + padding.top + padding.bottom;
    rc.size.width -= padding.left + padding.right;
    return rc;
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    
    if (contentView) {
        contentView.frame = self.contentRect;
    }
}

- (void)setContentView:(UIView*)view {
    [contentView removeFromSuperview];
    contentView = view;
    
    if (contentView) {
        contentView.frame = self.contentRect;
        [self addSubview:contentView];
    }
}

- (void)showSourceView {
    // only use in desktop mode.
    if (desktopMode == NO)
        return;
    
    if (sourceView == nil)
        return;
    if (darkColor == nil)
        return;
    if ([darkColor isEqual:[UIColor clearColor]])
        return;
    
    UIImage *snap = [sourceView convertToImage];
    UIImageView *view = [[UIImageView alloc] initWithImage:snap];
    CGRect rc = sourceView.frame;
    rc = [[self desktop] convertRect:rc fromView:sourceView.superview];
    view.frame = rc;
    [[self desktop] insertSubview:view atIndex:0];
    [view release];
}

- (void)lockSourceView {
    if ([sourceView respondsToSelector:@selector(lockPosition)]) {
        [(id<WSIUIViewLock>)sourceView lockPosition];
    }
}

- (void)unlockSouceView {
    if ([sourceView respondsToSelector:@selector(unlockPosition)]) {
        [(id<WSIUIViewLock>)sourceView unlockPosition];
    }
}

@end

@implementation UITearViewHov

- (void)open:(BOOL)animated {
    [self freeze];
    
    [super open:animated];
    
    CGRect rc_tgt = targetView.bounds;    
    CGRect rc_res = CGRectMake(rc_tgt.origin.x, rc_tgt.origin.y + location, rc_tgt.size.width, spacing);
    real max_edge = rc_res.origin.y + rc_res.size.height;
    
    wsi::core::vector<UIView*> in_region;
    for (UIView *view in targetView.subviews) {
        if (view == sourceView)
            continue;
        if (CGRectIntersectsRect(view.frame, rc_res)) {
            in_region << view;
            continue;
        }
        if (view.frame.origin.y > max_edge) {
            in_region << view;
            continue;
        }
    }
    
    if (desktopMode) {
        rc_res = [[self desktop] convertRect:rc_res fromView:targetView];
    }
    
    if (animated) {
        self.frame = CGRectMake(rc_res.origin.x, rc_res.origin.y, rc_res.size.width, 1);
        
        if (desktopMode) {
            [self desktop].backgroundColor = [UIColor clearColor];
        }
        
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
    }
    
    self.frame = rc_res;
    
    if (desktopMode) {
        [self desktop].backgroundColor = self.darkColor;
    }
    
    if (rc_res.size.height > targetView.bounds.size.height) {
        CGRect rect = targetView.frame;
        _element_info info;
        info.view = targetView;
        info.rect = rect;
        info.changed = YES;
        
        rc_res.size.height = rc_res.size.height;
        targetView.frame = rect;
        [self add_info:&info];
    }

    // push other views.
    for (wsi::core::vector<UIView*>::iterator iter = in_region.begin(); iter != in_region.end(); ++iter) {
        _element_info info;
        info.view = *iter;
        info.rect = (*iter).frame;
        info.changed = YES;
        
        (*iter).frame = CGRectAddY(info.rect, spacing);
        
        [self add_info:&info];
    }
    
    if (animated) {
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDidStopSelector:@selector(thaw)];
        [UIView commitAnimations];
    } else {
        [self thaw];
    }    
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    real pos_arrow = locationArrow;
    real len_arrow = lenArrow;
    real half_arrow = lenArrow;
    
    CGPoint pt0 = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height);
    CGPoint pt1 = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
    CGPoint pt2 = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + len_arrow);
    CGPoint pt3 = CGPointMake(rect.origin.x + pos_arrow + half_arrow, rect.origin.y + len_arrow);
    CGPoint pt4 = CGPointMake(rect.origin.x + pos_arrow, rect.origin.y);
    CGPoint pt5 = CGPointMake(rect.origin.x + pos_arrow - half_arrow, rect.origin.y + len_arrow);
    CGPoint pt6 = CGPointMake(rect.origin.x, rect.origin.y + len_arrow);
    CGPoint pts[] = {
      pt0, pt1, pt2, pt3, pt4, pt5, pt6  
    };
    
    // draw fill.
    CGContextSaveGState(ctx);        
    CGContextAddLines(ctx, pts, 7);        
    [fill fillPathInContext:ctx];
    
    CGContextRestoreGState(ctx);
    
    // draw shadow
    CGContextDrawShadowLine(ctx, pt0, pt1, edgeShadow.shadowColor.cgColor, edgeShadow.opacity, CGSizeMake(0, edgeShadow.radius));
    //CGContextDrawShadowLine(ctx, pt2, pt3, edgeShadow.shadowColor.CGColor, edgeShadow.opacity, CGSizeMake(0, -edgeShadow.radius));
    //CGContextDrawShadowLine(ctx, pt3, pt4, edgeShadow.shadowColor.CGColor, edgeShadow.opacity, CGSizeMake(edgeShadow.radius, -edgeShadow.radius));
    //CGContextDrawShadowLine(ctx, pt4, pt5, edgeShadow.shadowColor.CGColor, edgeShadow.opacity, CGSizeMake(-edgeShadow.radius, -edgeShadow.radius));
    CGContextDrawShadowLine(ctx, pt2, pt6, edgeShadow.shadowColor.cgColor, edgeShadow.opacity, CGSizeMake(0, -edgeShadow.radius));
    
    // fill triangle
    CGContextBeginPath(ctx);
    CGContextSetFillColorWithColor(ctx, edgeShadow.shadowColor.cgColor);
    CGContextMoveToPoint(ctx, pt3.x, pt3.y);
    CGContextAddLineToPoint(ctx, pt4.x, pt4.y);
    CGContextAddLineToPoint(ctx, pt5.x, pt5.y);
    CGContextClosePath(ctx);
    CGContextFillPath(ctx);  
    
    // draw edge.
    CGContextSaveGState(ctx);    
    CGContextSetLineWidth(ctx, edgeWidth);
    CGContextSetStrokeColorWithColor(ctx, edgeColor.CGColor);
    
    //CGContextSetShadowWithColor(ctx, CGSizeMake(0, -edgeShadow.radius), edgeShadow.opacity, edgeShadow.shadowColor.CGColor);    
    CGContextMoveToPoint(ctx, pt0.x, pt0.y - edgeWidth);
    CGContextAddLineToPoint(ctx, pt1.x, pt1.y - edgeWidth);
    CGContextStrokePath(ctx);    
        
    //CGContextSetShadowWithColor(ctx, CGSizeMake(0, edgeShadow.radius), edgeShadow.opacity, edgeShadow.shadowColor.CGColor);    
    CGContextMoveToPoint(ctx, pt2.x, pt2.y);
    CGContextAddLineToPoint(ctx, pt3.x, pt3.y);
    CGContextStrokePath(ctx);    
    
    //CGContextSetShadowWithColor(ctx, CGSizeMake(-edgeShadow.radius, edgeShadow.radius), edgeShadow.opacity, edgeShadow.shadowColor.CGColor);    
    CGContextMoveToPoint(ctx, pt3.x, pt3.y);
    CGContextAddLineToPoint(ctx, pt4.x, pt4.y);
    CGContextStrokePath(ctx);    
    
    //CGContextSetShadowWithColor(ctx, CGSizeMake(edgeShadow.radius, edgeShadow.radius), edgeShadow.opacity, edgeShadow.shadowColor.CGColor);    
    CGContextMoveToPoint(ctx, pt4.x, pt4.y);
    CGContextAddLineToPoint(ctx, pt5.x, pt5.y);
    CGContextStrokePath(ctx);    
    
    //CGContextSetShadowWithColor(ctx, CGSizeMake(0, edgeShadow.radius), edgeShadow.opacity, edgeShadow.shadowColor.CGColor);    
    CGContextMoveToPoint(ctx, pt5.x, pt5.y);
    CGContextAddLineToPoint(ctx, pt6.x, pt6.y);
    CGContextStrokePath(ctx);
    
    CGContextRestoreGState(ctx);               
}

@end

@implementation UITearViewVec

- (void)open {
    [super open];
}

@end

WSI_END_OBJC