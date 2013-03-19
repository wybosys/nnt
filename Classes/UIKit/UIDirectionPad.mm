
# import "Core.h"
# import "UIDirectionPad.h"
# import "Math+NNT.h"

NNT_BEGIN_OBJC

@implementation UIDirectionPad

@synthesize position, location;
@synthesize color;

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalPadMoved)
NNTEVENT_END

+ (id)pad {
    CGSize sz = [UIDirectionPad sizeForPad];
    return [[[UIDirectionPad alloc] initWithFrame:CGRectMakeSz(sz)] autorelease];
}

+ (CGSize)sizeForPad {
    CGSize sz = [NNTApplication shared].window.bounds.size;
    real length = MIN(sz.width, sz.height);
    sz.width = sz.height = length * .33f;
    return sz;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    self.userInteractionEnabled = NO;
    self.color = [UIColor colorWithRGBA:0x000000A0];
    
    return self;
}

- (void)dealloc {
    zero_release(color);
    [super dealloc];
}

- (void)setPosition:(CGPoint)pos {
    if (CGPointEqualToPoint(pos, position))
        return;
    
    [self moveToCenter:pos];
    position = pos;
}

- (void)setLocation:(CGPoint)pos {
    location = pos;
    
    real d[2] = {location.x - position.x, location.y - position.y};
    [self emit:kSignalPadMoved data:(CGPoint*)d];
}

# pragma mark draw.

- (void)drawRect:(CGRect)rect {
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    CGPoint pt_center = CGRectCenterPoint(&rect);
    real radius = rect.size.width * .5f;
    real radius_button = radius * .3f;

    // draw edge.
    CGContextAddArc(ctx, pt_center.x, pt_center.y, radius, 0, M_2PI, 0);
    CGContextAddArc(ctx, pt_center.x, pt_center.y, radius - 10, 0, M_2PI, 1);
    CGContextSetFillColorWithColor(ctx, color.CGColor);
    CGContextFillPath(ctx);
    
    // draw button.
    CGPoint pt_button = CGPointAddXY(position, -location.x, -location.y);
    // pt muse in round.
    {
        real lengthsq = pt_button.x * pt_button.x + pt_button.y * pt_button.y;
        real radiussq = (radius - radius_button) * (radius - radius_button);
        if (lengthsq > radiussq) {
            real ratio = sqrt(radiussq / lengthsq);
            pt_button.x = pt_button.x * ratio;
            pt_button.y = pt_button.y * ratio;
        }
    }
    pt_button = CGPointAddXY(pt_center, -pt_button.x, -pt_button.y);
    CGContextAddArc(ctx, pt_button.x, pt_button.y, radius_button, radius_button, 0, M_2PI);
    CGContextFillPath(ctx);
}

@end

NNT_END_OBJC