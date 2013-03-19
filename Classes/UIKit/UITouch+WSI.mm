
# import "Core.h"
# import "UITouch+WSI.h"

WSI_BEGIN_OBJC

@implementation UITouch (WSI)

- (CGPoint)offset {
    CGPoint cur = [self locationInView:self.view];
    CGPoint old = [self previousLocationInView:self.view];
    return CGPointMake(cur.x - old.x, cur.y - old.y);
}

@end

WSIIMPL_CATEGORY(UITouch, WSI);

WSI_END_OBJC
