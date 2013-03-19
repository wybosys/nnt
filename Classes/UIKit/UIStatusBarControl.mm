
# import "NNTFoundation.h"
# import "UIStatusBarControl.h"

NNT_BEGIN_OBJC

@implementation UIStatusBarControl

@synthesize rightToLeft;

- (id)initWithWidth:(int)width {
    self = [super initWithFrame:CGRectMake(0, 0, width, [UIStatusBarControl barHeight])];
    
    self.rightToLeft = YES;
    
    return self;
}

+ (int)barHeight {
    return 20;
}

- (void)addSubview:(UIView *)view {
    CGRect rc = view.frame;
    rc.size.height = [UIStatusBarControl barHeight];
    rc.origin = CGRectRightTop2(self.bounds);
    view.frame = rc;
    
    [super addSubview:view];
    
    [self updateLayout:self.bounds];
}

- (void)updateLayout:(CGRect)rect {
    [UIView beginAnimations:nil context:nil];
    
    if (self.rightToLeft) {        
        CGPoint pt = CGRectRightTop(&rect);
        for (UIView* each in [self.subviews reverse]) {
            CGRect rc = each.frame;
            pt.x -= rc.size.width;
            rc.origin = pt;
            each.frame = rc;
        }
    } else {
        CGPoint pt = rect.origin;
        for (UIView* each in self.subviews) {
            CGRect rc = each.frame;
            rc.origin = pt;
            pt.x += rc.size.width;
            each.frame = rc;
        }
    }
    
    [UIView commitAnimations];
}

@end

NNT_END_OBJC