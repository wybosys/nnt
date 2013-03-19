
# import "Core.h"
# import "UIActivityIndicatorWave.h"
# import "JuiceCocoa++.hpp"

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(UIActivityIndicatorWave, NNTObject) {
    @public
    CADisplayLink* dl;
    uint segsize;
    ::nnt::core::vector<CGPoint> pts;
    uint delay;
}

NNTDECL_PRIVATE_IMPL(UIActivityIndicatorWave)

- (id)init {
    self = [super init];
    
    segsize = 10;
    
    return self;
}

- (void)cb_display {
    if (delay == 2) {
        delay = 0;
    } else {
        ++delay;
        return;
    }
    
    CGSize sz = d_owner.bounds.size;
    uint count = ceil(sz.width / (float)segsize);
    if (count != pts.size()) {
        pts.resize(count + 1);
    }
    
    for (uint i = 0; i <= count; ++i) {
        CGPoint& pt = pts[i];
        
        pt.x = segsize * i;
        pt.y = rand01() * sz.height;
    }
    
    [d_owner setNeedsDisplay];
}

NNTDECL_PRIVATE_END

@implementation UIActivityIndicatorWave

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    NNTDECL_PRIVATE_INIT(UIActivityIndicatorWave);
    return self;
}

- (void)dealloc {
    [self stopAnimating];
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    using namespace ::juice::cocoa;
    
    Graphics gra = Graphics::Current();
    //gra.scale(1, rect.size.height);
    
    Path ph;
    ph.add_lines(d_ptr->pts);
    Pen pn(Color::Black());
    ph.stroke(gra, pn);
}

- (void)startAnimating {
    d_ptr->dl = [CADisplayLink displayLinkWithTarget:d_ptr selector:@selector(cb_display)];
    [d_ptr->dl addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)stopAnimating {
    if (d_ptr->dl) {
        [d_ptr->dl invalidate];
        d_ptr->dl = nil;
    }
}

@end

_CXXVIEW_IMPL(UIActivityIndicatorWave)

NNT_END_OBJC
