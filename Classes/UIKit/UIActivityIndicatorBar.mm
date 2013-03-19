
# import "Core.h"
# import "UIActivityIndicatorBar.h"
# import "JuiceCocoa++.hpp"

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(UIActivityIndicatorBar, NNTObject) {
    @public
    real value;
    CADisplayLink* dl;
    BOOL dir;
    real step;
}

NNTDECL_PRIVATE_IMPL(UIActivityIndicatorBar)

- (id)init {
    self = [super init];
    
    dir = YES;
    step = 3;
    
    return self;
}

- (void)_cb_dl {
    CGSize sz = d_owner.bounds.size;
    
    if (dir) {
        if (value < sz.width) {
            value += step;
        } else {
            dir = NO;
        }
    } else {
        if (value > 0) {
            value -= step;
        } else {
            dir = YES;
        }
    }
    
    [d_owner setNeedsDisplay];
}

NNTDECL_PRIVATE_END

@implementation UIActivityIndicatorBar

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT(UIActivityIndicatorBar);
    return self;
}

- (void)dealloc {
    [self stopAnimating];
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    using namespace juice::cocoa;
    
    Graphics gra = Graphics::Current();
    
    // draw edge.
    Pen edge(Color::Black());
    edge.stroke(gra, rect);
    
    // move.
    gra.translate(d_ptr->value, 0);
    
    // draw inp.
    struct draw_block : ::nnt::core::sc<draw_block>
    {
        void operator () (Graphics& gra, CGRect const& rc) const
        {
            Brush br(Color::Black());
            int o = 2;
            int l = rc.size.height - o - o;
            br.fill(gra, juice::cocoa::Rect(0, o, l, l));
        }
    };
    
    // draw at position.
    draw_block::imp(gra, rect);
}

- (void)startAnimating {
    d_ptr->dl = [CADisplayLink displayLinkWithTarget:d_ptr selector:@selector(_cb_dl)];
    [d_ptr->dl addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)stopAnimating {
    if (d_ptr->dl) {
        [d_ptr->dl invalidate];
        d_ptr->dl = nil;
    }
}

@end

_CXXVIEW_IMPL(UIActivityIndicatorBar);

NNT_END_OBJC
