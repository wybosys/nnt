
# import "Core.h"
# import "UITouch+NNT.h"

NNT_BEGIN_OBJC

@implementation UITouch (NNT)

- (CGPoint)offset {
    CGPoint cur = [self locationInView:self.view];
    CGPoint old = [self previousLocationInView:self.view];
    return CGPointMake(cur.x - old.x, cur.y - old.y);
}

@end

NNTIMPL_CATEGORY(UITouch, NNT);

NNT_END_OBJC
