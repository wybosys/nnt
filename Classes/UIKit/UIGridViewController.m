
# import "Core.h"
# import "UIGridViewController.h"
# import "UIGridView.h"

WSI_BEGIN_OBJC

@implementation UIGridViewController

@synthesize rows, cols;
@dynamic gridView;

- (void)loadView {
    UIGridView* view = [[UIGridView alloc] initWithFrame:CGRectZero rows:rows cols:cols];
    self.view = view;
    [view release];
}

- (UIGridView*)gridView {
    return (UIGridView*)self.view;
}

@end

WSI_END_OBJC