
# import "Core.h"
# import "UILineSeparator.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

@implementation UILineSeparator

@synthesize lineStyle = _lineStyle;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    WCGMutableLineStyle* tmp = [[WCGMutableLineStyle alloc] init];
    tmp.lineWidth = 1;
    tmp.lineColor = [WCGColor grayColor];
    tmp.dashPattern = [NSArray arrayWithObjects:NSNumber1, NSNumber1, nil];
    self.lineStyle = tmp;
    safe_release(tmp);
    
    self.userInteractionEnabled = NO;
    
    return self;
}

- (id)initWithLineStyle:(WCGLineStyle *)ls {
    self = [super initWithZero];
    
    WCGMutableLineStyle* tmp = [[WCGMutableLineStyle alloc] initWithLineStyle:ls];
    self.lineStyle = tmp;
    safe_release(tmp);
    
    return self;
}

- (id)initWithDashPattern:(NSArray *)pat {
    self = [super initWithZero];
    
    _lineStyle.dashPattern = pat;
    
    return self;
}

- (void)dealloc {
    safe_release(_lineStyle);
    [super dealloc];
}

@end

@implementation UIHovLineSeparator

- (void)setFrame:(CGRect)frame {
    if (_lineStyle)
        frame.size.height = _lineStyle.lineWidth * 2;
    [super setFrame:frame];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    [self.lineStyle setLineStyleInContext:ctx];
    CGPoint lc = CGRectLeftCenter(&rect);
    CGPoint rc = CGRectRightCenter(&rect);
    lc.y -= _lineStyle.lineWidth * .5f;
    rc.y -= _lineStyle.lineWidth * .5f;
    
    CGContextMoveToPoint(ctx, lc.x, lc.y);
    CGContextAddLineToPoint(ctx, rc.x, rc.y);
    
    CGContextStrokePath(ctx);
}

@end

@implementation UIVecLineSeparator

@end

NNT_END_OBJC
