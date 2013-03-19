
# import "Core.h"
# import "UIDrawerView.h"
# import "WCGBase.h"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@implementation UIDrawerView

@synthesize positionType = _positionType;
@synthesize length = _length;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _positionType = CGRectPositionTypeLeft;
    _opened = NO;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)openBeyondView:(UIView *)view animated:(BOOL)animated {
    if (_opened) {
        [self close:animated];
        return;
    }
    
    _beyondView = view;
    UIView* workView = _beyondView.superview;
    [workView addSubview:self];
    
    // set origin rect.
    cg::TransformRect rc = _beyondView.logicFrame;
    switch (_positionType)
    {
        default:
        case CGRectPositionTypeLeft: {
            rc -= cg::Point(_length, 0);
            rc.set_width(_length);
        } break;
        case CGRectPositionTypeRight: {
            rc += cg::Point(rc.width(), 0);
            rc.set_width(_length);
        } break;
        case CGRectPositionTypeTop: {
            rc -= cg::Point(0, _length);
            rc.set_height(_length);
        } break;
        case CGRectPositionTypeBottom: {
            rc += cg::Point(0, rc.height());
            rc.set_height(_length);
        } break;
    }
    self.logicFrame = rc;
    
    // begin ani.
    self.alpha = .0f;
    
    // use ani.
    if (animated) {
        [UIView beginAnimations:nil context:nil];
    }
    
    // adjust appear.
    self.alpha = 1.f;

    cg::TransformRect rcb = _beyondView.logicFrame;
    switch (_positionType)
    {
        default:
        case CGRectPositionTypeLeft: {
            rcb += cg::Point(_length, 0);
            rc += cg::Point(_length, 0);
        } break;
        case CGRectPositionTypeRight: {
            rcb -= cg::Point(_length, 0);
            rc -= cg::Point(_length, 0);
        } break;
        case CGRectPositionTypeTop: {
            rcb += cg::Point(0, _length);
            rc += cg::Point(0, _length);
        } break;
        case CGRectPositionTypeBottom: {
            rcb -= cg::Point(0, _length);
            rc -= cg::Point(0, _length);
        } break;
    }
    
    _beyondView.logicFrame = rcb;
    self.logicFrame = rc;
    
    if (animated) {
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDidStopSelector:@selector(_ani_begin)];
        [UIView commitAnimations];
    } else {
        [self _ani_begin];
    }
}

- (void)_ani_begin {
    _opened = YES;
}

- (void)close:(BOOL)animated {
    if (_opened == NO)
        return;
    
    // use ani.
    if (animated) {
        [UIView beginAnimations:nil context:nil];
    }
    
    // adjust appear.
    self.alpha = 0.f;
    
    cg::TransformRect rcb = _beyondView.logicFrame;
    cg::TransformRect rc = self.logicFrame;
    switch (_positionType)
    {
        default:
        case CGRectPositionTypeLeft: {
            rcb -= cg::Point(rc.width(), 0);
            rc -= cg::Point(rc.width(), 0);
        } break;
        case CGRectPositionTypeRight: {
            rcb += cg::Point(rc.width(), 0);
            rc += cg::Point(rc.width(), 0);
        } break;
        case CGRectPositionTypeTop: {
            rcb -= cg::Point(0, rc.height());
            rc -= cg::Point(0, rc.height());
        } break;
        case CGRectPositionTypeBottom: {
            rcb += cg::Point(0, rc.height());
            rc += cg::Point(0, rc.height());
        } break;
    }
    
    _beyondView.logicFrame = rcb;
    self.logicFrame = rc;
    
    if (animated) {
        [UIView setAnimationDelegate:self];
        [UIView setAnimationDidStopSelector:@selector(_ani_end)];
        [UIView commitAnimations];
    } else {
        [self _ani_end];
    }
}

- (void)_ani_end {
    [self removeFromSuperview];
    _opened = NO;
}

@end

_CXXVIEW_IMPL(UIDrawerView);

NNT_END_OBJC
