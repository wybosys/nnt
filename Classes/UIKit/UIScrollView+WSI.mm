
# import "Core.h"
# import "UIScrollView+NNT.h"
# import "UIView+NNT.h"
# import "NNTUIObject.h"
# import "CoreGraphic+NNT.h"
# include <cmath>

NNT_BEGIN_OBJC

signal_t kSignalBeginScroll = @"::wsi::ui::scroll:begin";
signal_t kSignalEndScroll = @"::wsi::ui::scroll::end";

@implementation UIScrollView (NNT)

- (CGRect)rectForLayout {
    CGSize sz = self.contentSize;
    CGSize bsz = self.bounds.size;
    if (sz.width < bsz.width || sz.height < bsz.height)
        sz = bsz;
    CGRect rc = CGRectMakePtSz(self.contentOffset, sz);
    return rc;
}

- (CGRect)boundsForLayout {
    CGSize sz = self.contentSize;
    CGSize bsz = self.bounds.size;
    if (sz.width < bsz.width || sz.height < bsz.height)
        sz = bsz;
    CGRect rc = CGRectMakeSz(sz);
    return rc;
}

- (CGRect)visibleFrame {
    CGRect rc = self.bounds;
    CGPoint off = self.contentOffset;
    rc.origin.x += off.x;
    rc.origin.y += off.y;
    return rc;
}

@end

NNTIMPL_CATEGORY(UIScrollView, NNT);

@interface NNTUIScrollView ()

- (void)processHeaders;
- (void)scrollHeaders;

@end

@implementation NNTUIScrollView

@dynamic contentFrame;
@synthesize backgroundFill = _backgroundFill;
@synthesize sendGlobalEvent = _sendGlobalEvent;
@synthesize topHeaderView = _topHeaderView, bottomHeaderView = _bottomHeaderView;
@synthesize contentView = _contentView2;

NNTOBJECT_IMPL_NOSIGNALS;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _sendGlobalEvent = YES;
    self.backgroundColor = [UIColor clearColor];
    self.delegate = self;
    
    return self;
}

- (void)dealloc {
    zero_release(_backgroundFill);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalViewClicked);
    NNTEVENT_SIGNAL(kSignalTouchesBegin);
    NNTEVENT_SIGNAL(kSignalTouchesEnd);
    NNTEVENT_SIGNAL(kSignalTouchesMoved);
    NNTEVENT_SIGNAL(kSignalTouchesCancel);
    NNTEVENT_SIGNAL(kSignalBeginScroll);
    NNTEVENT_SIGNAL(kSignalEndScroll);
    NNTEVENT_SIGNAL(kSignalFrameChanged);
}

- (void)setTopHeaderView:(UIHeaderView*)view {
    if (_topHeaderView == view)
        return;
    
    [_topHeaderView removeFromSuperview];
    [self addSubview:view];

    _topHeaderView = view;
    _topHeaderView.hidden = YES;
    _topHeaderView.direction = WCGDirectionTop;
}

- (void)setBottomHeaderView:(UIHeaderView*)view {
    if (_bottomHeaderView == view)
        return;
    
    [_bottomHeaderView removeFromSuperview];
    [self addSubview:view];

    _bottomHeaderView = view;
    _bottomHeaderView.hidden = YES;
    _bottomHeaderView.direction = WCGDirectionBottom;
}

- (void)processHeaders {
    CGPoint offset = self.contentOffset;
    
    if (_topHeaderView && _topHeaderView.hidden == NO) {
        if (-offset.y > _topHeaderView.height) {
            if ([_topHeaderView respondsToSelector:@selector(headerDidAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_topHeaderView;
                [obj headerDidAction:_topHeaderView];
            }
        }
    }
    
    if (_bottomHeaderView && _bottomHeaderView.hidden == NO) {
        CGSize sz = self.contentSize;
        sz.height -= self.bounds.size.height;
        if (offset.y > sz.height + _bottomHeaderView.height) {
            if ([_bottomHeaderView respondsToSelector:@selector(headerDidAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_bottomHeaderView;
                [obj headerDidAction:_bottomHeaderView];
            }
        }
    }
}

- (void)scrollHeaders {
    CGPoint offset = self.contentOffset;

    if (_topHeaderView) {
        if (offset.y < 0 && _topHeaderView.hidden == YES) {
            _topHeaderView.hidden = NO;
            [_topHeaderView setNeedsDisplay];
            if ([_topHeaderView respondsToSelector:@selector(headerBeginAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_topHeaderView;
                [obj headerBeginAction:_topHeaderView];
            }
                
        } else if (offset.y >= 0 && _topHeaderView.hidden == NO) {
            _topHeaderView.hidden = YES;
            
            if ([_topHeaderView respondsToSelector:@selector(headerEndAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_topHeaderView;
                [obj headerEndAction:_topHeaderView];
            }
        } else if (_topHeaderView.hidden == NO) {
            if ([_topHeaderView respondsToSelector:@selector(headerMovedAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_topHeaderView;
                [obj headerMovedAction:_topHeaderView];
            }
            
            if (-offset.y > _topHeaderView.height) {
                if ([_topHeaderView respondsToSelector:@selector(headerWillAction:)]) {
                    id<UIHeaderView> obj = (id<UIHeaderView>)_topHeaderView;
                    [obj headerWillAction:_topHeaderView];
                }
            }
        }
    }
    
    if (_bottomHeaderView) {
        CGSize sz = self.contentSize;
        sz.height -= self.bounds.size.height;
        if (offset.y > sz.height && _bottomHeaderView.hidden == YES) {
            _bottomHeaderView.hidden = NO;
            [_bottomHeaderView setNeedsDisplay];
            if ([_bottomHeaderView respondsToSelector:@selector(headerBeginAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_bottomHeaderView;
                [obj headerBeginAction:_bottomHeaderView];
            }
        } else if (offset.y <= sz.height && _bottomHeaderView.hidden == NO) {
            _bottomHeaderView.hidden = YES;
            
            if ([_bottomHeaderView respondsToSelector:@selector(headerEndAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_bottomHeaderView;
                [obj headerEndAction:_bottomHeaderView];
            } 
        } else if (_bottomHeaderView.hidden == NO) {
            if ([_bottomHeaderView respondsToSelector:@selector(headerMovedAction:)]) {
                id<UIHeaderView> obj = (id<UIHeaderView>)_bottomHeaderView;
                [obj headerMovedAction:_bottomHeaderView];
            }
            
            if (offset.y > sz.height + _bottomHeaderView.height) {
                if ([_bottomHeaderView respondsToSelector:@selector(headerWillAction:)]) {
                    id<UIHeaderView> obj = (id<UIHeaderView>)_bottomHeaderView;
                    [obj headerWillAction:_bottomHeaderView];
                }
            }
        }
    }
}

- (void)setBounds:(CGRect)rect {
    [super setBounds:rect];
}

- (void)setFrame:(CGRect)rect {
    if (CGRectEqualToRect(rect, self.frame))
        return;
    
    // set.
    [super setFrame:rect];
    
    // signal.
    [self emit:kSignalFrameChanged];
}

- (void)setContentOffset:(CGPoint)contentOffset {
    // iOS may call auto reset to content offset use CGPoint(-0, -0)
    // so if pass it, we skip.
    if (::std::signbit(contentOffset.x) &&
        ::std::signbit(contentOffset.y)) {
        //[self setNeedsLayout];
        return;
    }
    
    [super setContentOffset:contentOffset];
}

- (void)setContentView:(UIView *)contentView {
    [_contentView2 removeFromSuperview];
    _contentView2 = contentView;
    [self addSubview:_contentView2];
    [self setNeedsLayout];
}

- (void)layoutSubviews {
    // super.
    [super layoutSubviews];
    
    // if bounds changed.
    CGRect rc = self.bounds;
    if (CGRectEqualToRect(rc, CGRectZero))
        return;
    
    // layout content.
    if (_contentView2) {
        _contentView2.frame = self.contentFrame;
    }
    
    CGPoint const offset = self.contentOffset;
    CGSize const size = self.contentSize;
    
    // calc header.
    if (_topHeaderView && _topHeaderView.hidden == NO) {
        CGRect rc_top = _topHeaderView.frame;
        rc_top.origin = CGPointZero;
        
        if (_topHeaderView.autoScale)
            rc_top.size.height = -offset.y;
        
        rc_top.origin.y -= rc_top.size.height;;
        rc_top.size.width = rc.size.width;
        
        _topHeaderView.frame = rc_top;
    }
    
    if (_bottomHeaderView && _bottomHeaderView.hidden == NO) {
        CGRect rc_bot = _bottomHeaderView.frame;
        rc_bot.origin = CGPointMake(0, size.height);
        
        if (_topHeaderView.autoScale)
            rc_bot.size.height = offset.y - (size.height - rc.size.height);
        
        rc_bot.size.width = rc.size.width;
        _bottomHeaderView.frame = rc_bot;
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {       
    [super touchesBegan:touches withEvent:event];
    
    __waiting_touch = 0;
    [self performSelector:@selector(fun_waiting_touch) withObject:nil afterDelay:kUITouchDelay];
    
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesBegin, self, touches, event);
    
    [self emit:kSignalTouchesBegin result:touches data:event];
}

- (void)fun_waiting_touch {
    if (__waiting_touch == 0)
        __waiting_touch = 1;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {        
    [super touchesEnded:touches withEvent:event];
    
    if (__waiting_touch == 1) {
        [self emit:kSignalViewClicked result:[NSPair pairWith:touches second:event]];
    }
        
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesEnd, self, touches, event);

    [self emit:kSignalTouchesEnd result:touches data:event];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesCancelled:touches withEvent:event];
    
    __waiting_touch = -1;
    
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesCancel, self, touches, event);
    
    [self emit:kSignalTouchesCancel result:touches data:event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesMoved:touches withEvent:event];
    
    __waiting_touch = -1;
    
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesMoved, self, touches, event);
    
    [self emit:kSignalTouchesMoved result:touches data:event];
}

- (CGRect)contentFrame {
    CGPoint off = self.contentOffset;
    CGSize sz = self.contentSize;
    
    CGRect rc = self.bounds;
    off.x = rc.origin.x - off.x;
    off.y = rc.origin.y - off.y;
    
    CGRect ret = CGRectMakePtSz(off, sz);
    
    return ret;
}

- (void)drawRect:(CGRect)rect {
    // draw super.
    [super drawRect:rect];
    
    // draw background.
    CGContextRef ctx = UIGraphicsGetCurrentContext();        
    [_backgroundFill fillRect:rect inContext:ctx];
}

// delegate.

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    [self emit:kSignalBeginScroll];
}

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate {
    if (decelerate == NO) {
        [self emit:kSignalEndScroll];                
    }
    
    // headers.
    [self processHeaders];
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    [self emit:kSignalEndScroll];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {    
    [self scrollHeaders];
}

- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView {
    PASS;
}

- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView {
    PASS;
}

@end

_CXXVIEW_IMPL(NNTUIScrollView);

NNT_END_OBJC
