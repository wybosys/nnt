
# import "Core.h"
# import "UICHMView.h"

WSI_BEGIN_OBJC

@implementation UICHMView 

@synthesize main;

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    main.frame = rc;
}

@end

WSI_END_OBJC