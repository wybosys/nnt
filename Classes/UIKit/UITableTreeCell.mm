
# import "Core.h"
# import "UITableTreeCell.h"
# import "UITableTreeViewController.h"

WSI_BEGIN_OBJC

@implementation UITableViewGroupCell

@synthesize isExpanded;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    isExpanded = NO;
    
    return self;
}

- (BOOL)expand {
    if (isExpanded)
        return NO;
    isExpanded = YES;
    
    if (self.accessoryView) {
        CGAffineTransform mat = self.accessoryView.transform;
        mat = CGAffineTransformScale(mat, 1, -1);
        self.accessoryView.transform = mat;
    }
    
    return YES;
}

- (BOOL)collapse {
    if (!isExpanded)
        return NO;
    isExpanded = NO;
    
    if (self.accessoryView) {
        CGAffineTransform mat = self.accessoryView.transform;
        mat = CGAffineTransformScale(mat, 1, -1);
        self.accessoryView.transform = mat;
    }
    
    return YES;
}

@end

_CXXVIEW_IMPL_BEGIN(UITableViewGroupCell)
_CXXVIEW_IMPL_END

WSI_END_OBJC
