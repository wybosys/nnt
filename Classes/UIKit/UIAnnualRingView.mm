
# import "Core.h"
# import "UIAnnualRingView.h"
# include "JuiceCocoa++.hpp"
# include "Math+WSI.h"
# include "Linear.h"

WSI_BEGIN_OBJC

WSI_USINGCXXNAMESPACE;

signal_t kSignalRingRotated = @"::wsi::ui::ring::rotated";
signal_t kSignalItemLayoutted = @"::wsi::ui::item::layoutted";
signal_t kSignalItemsLayoutted = @"::wsi::ui::items::layoutted";

@implementation UIAnnualRingSingle

@synthesize length = _length, radius = _radius;
@synthesize ringColor = _ringColor, ringFill = _ringFill, ringShadow = _ringShadow;
@synthesize items = _items;
@synthesize startAngle = _startAngle, sweepAngle = _sweepAngle;
@synthesize innerRadius = _innerRadius, outterRadius = _outterRadius;
@synthesize clockwise = _clockwise;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.ringColor = [UIColor blackColor];
    
    _clockwise = true;
    _sweepAngle = M_2PI;
    
    _items = [[UIItemsContainer alloc] init];
    [_items connect:kSignalContentClicked sig:kSignalContentClicked obj:self];
    
    // event.
    [self connect:kSignalTouchesBegin sel:@selector(_act_touchesbegin:)];
    [self connect:kSignalTouchesMoved sel:@selector(_act_touches:)];
    //[self connect:kSignalTouchesEnd sel:@selector(_act_touches:)];
    
    return self;
}

- (void)dealloc {
    safe_release(_items);
    safe_release(_ringColor);
    safe_release(_ringFill);
    safe_release(_ringShadow);
    
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalRingRotated)
WSIEVENT_SIGNAL(kSignalContentClicked)
WSIEVENT_SIGNAL(kSignalItemsLayoutted)
WSIEVENT_END

- (void)setRadius:(real)radius {
    if (_radius == radius)
        return;
    
    _radius = radius;
    [self _updateFrame];
}

- (void)setLength:(real)length {
    if (_length == length)
        return;
    
    _length = length;
    [self _updateFrame];
}

// recalc fitable frame.
- (void)_updateFrame {
    real width = _radius * 2 + _length;
    CGRect rc = CGRectMake(0, 0, width, width);
    rc.origin = self.frame.origin;
    
    // set new frame.
    self.frame = rc;
    
    _innerRadius = _radius - _length * .5f;
    if (_innerRadius < 0)
        _innerRadius = 0;
    _outterRadius = _radius + _length * .5f;
}

- (void)paintRect:(CGRect)rect context:(CGContextRef)ctx {
    ::juice::cocoa::Graphics gra(ctx, rect);
    
    cg::Point center = gra.bounds().center();
    
    ::juice::cocoa::Path ph;
    ph.add_arc(center, _outterRadius, 0, M_2PI, ::juice::cocoa::cw);
    ph.add_arc(center, _innerRadius, 0, M_2PI, ::juice::cocoa::ccw);
    
    if (_ringShadow) {
        ::juice::cocoa::Shadow sd(_ringShadow);
        switch (sd.side())
        {
            case SideTypeDouble: {
                ph.stroke(gra, sd);
            } break;
            case SideTypeInner: {
                ::juice::cocoa::Path ph;
                ph.add_arc(center, _innerRadius, 0, M_2PI, ::juice::cocoa::ccw);
                ph.stroke(gra, sd);
            } break;
            case SideTypeOutter: {
                ::juice::cocoa::Path ph;
                ph.add_arc(center, _outterRadius, 0, M_2PI, ::juice::cocoa::cw);
                ph.stroke(gra, sd);
            } break;
            case SideTypeFill: {
                sd.set(gra);
            } break;
        }
    }
    
    if (_ringColor) {
        ::juice::cocoa::Brush br(::juice::cocoa::Color(_ringColor.CGColor));
        ph.fill(gra, br);
    }
    
    if (_ringFill) {
        ::juice::cocoa::Fill fl(_ringFill);
        ph.fill(gra, fl);
    }

}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event {
    return [self hitTest:point];
}

- (bool)hitTest:(CGPoint)pt {
    real len = cg::Line(cg::Rect(self.bounds).center(), cg::Point(pt)).length();
    return
    len > _innerRadius &&
    len < _outterRadius;
}

- (UIItemView*)hitTestFromAngle:(real)from toAngle:(real)to {
    from = M_2PI_RESTRICT_P(from);
    to = M_2PI_RESTRICT_P(to);
    
    cg::Point center = cg::Rect(self.bounds).center();
    for (UIItemView* view in _items.items) {
        cg::Point ictr = cg::Rect(view.frame).center();
        real angle = math::linear::Line<real, 2, cg::Point>(center, ictr).angle();
        
        if (from <= to) {
            if (angle >= from &&
                angle <= to) {
                return view;
            }
        } else {
            if (angle >= from ||
                angle <= to) {
                return view;
            }
        }
    }
    return nil;
}

- (real)currentAngle {
    real ret = _startAngle + _offAngle;
    ret = M_2PI_RESTRICT(ret);
    if (ret < 0)
        ret += M_2PI;
    return ret;
}

- (void)layoutSubviews {
    // layout items.
    [self relayout:NO];
}

- (void)relayout:(BOOL)animated {
    NSUInteger const count = [_items count];
    if (count == 0)
        return;
    
    real segangle = _sweepAngle / count;
    
    math::linear::Circle<real, cg::Point> cir;
    cir.radius = _radius;
    cir.center = cg::Rect(self.bounds).center();
    
    real angle = 0;
    for (uint i = 0; i < count; ++i) {
        UIItemView* item = [_items objectAtIndex:i];
        
        // add item to ring.
        if (item.superview == nil) {
            
            // add item.
            [item connect:kSignalTouchesBegin sig:kSignalTouchesBegin obj:self];
            [item connect:kSignalTouchesMoved sig:kSignalTouchesMoved obj:self];
            //[item connect:kSignalTouchesEnd sig:kSignalTouchesEnd obj:self];
            
            [self addSubview:item];
        }
        
        cg::Point pt = cir.at_angle(TRIEXP(_clockwise, angle, -angle) + _startAngle + _offAngle);
        angle += segangle;
        
        [item moveToCenter:pt];
    }
    
    [self emit:kSignalItemsLayoutted];
}

- (void)_act_touchesbegin:(WSIEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    _point = [[touches anyObject] locationInView:self];
}

- (void)_act_touches:(WSIEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    CGPoint pt = [[touches anyObject] locationInView:self];
    CGPoint center = cg::Rect(self.bounds).center();
    
    real angle_old = math::linear::Circle<real, cg::Point>::line_type(center, _point).angle();
    real angle_cur = math::linear::Circle<real, cg::Point>::line_type(center, pt).angle();
    real angle = angle_cur - angle_old;
    _point = pt;
    
    // set.
    _offAngle += angle;
    _offAngle = M_2PI_RESTRICT(_offAngle);
    
    // relayout.
    [self relayout:YES];
    
    // emit.
    [self emit:kSignalRingRotated];
}

@end

_CXXVIEW_IMPL_BEGIN(UIAnnualRingSingle)

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.items.dataSource = self;
    
    return self;
}

_CXXVIEW_IMPL_END

@implementation UIAnnualRingControl

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _rings = [[NSMutableArray alloc] init];
    
    return self;
}

- (void)dealloc {
    safe_release(_rings);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalContentClicked)
WSIEVENT_SIGNAL(kSignalItemsLayoutted)
WSIEVENT_SIGNAL(kSignalItemInserted)
WSIEVENT_SIGNAL(kSignalItemRemoving)
WSIEVENT_END

- (UIAnnualRingSingle*)addRingWithLength:(real)length radius:(real)radius {
    UIAnnualRingSingle* ring = [[UIAnnualRingSingle alloc] initWithZero];
    ring.length = length;
    ring.radius = radius;
    [self addRing:ring];
    safe_release(ring);
    return ring;
}

- (void)addRing:(UIAnnualRingSingle*)ring {
    // add object.
    [_rings addObject:ring];
    
    // send to view.
    [self addSubview:ring];
    [self setNeedsLayout];
    
    // signal.
    [ring connect:kSignalContentClicked sig:kSignalContentClicked obj:self];
    [self emit:kSignalItemInserted result:ring];
}

- (void)removeRing:(UIAnnualRingSingle*)ring {
    // signal.
    [self emit:kSignalItemRemoving result:ring];
    
    // remove event.
    [ring disconnect:self];
    
    // remove from memory.
    [ring removeFromSuperview];
    [_rings removeObject:ring];
}

- (void)removeRingAtIndex:(NSUInteger)idx {
    UIAnnualRingSingle* ring = [_rings objectAtIndex:idx];
    [self removeRing:ring];
}

- (UIAnnualRingSingle*)ringAtIndex:(NSUInteger)idx {
    return [_rings objectAtIndex:idx];
}

- (NSUInteger)count {
    return [_rings count];
}

- (void)layoutSubviews {
    cg::Rect rc = self.bounds;
    cg::Point center = rc.center();
    
    for (UIAnnualRingSingle* each in _rings) {
        [each moveToCenter:center];
    }
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event {
    UIAnnualRingSingle* hit = nil;
    for (UIAnnualRingSingle* each in _rings) {
        cg::Point pt = point;
        pt -= each.frame.origin;
        if ([each pointInside:pt withEvent:event]) {
            hit = each;
            break;
        }
    }
    
    return hit != nil;
}

@end

_CXXVIEW_IMPL(UIAnnualRingControl);

WSI_END_OBJC
