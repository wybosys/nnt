
# import "Core.h"
# import "UICHMView.h"

NNT_BEGIN_OBJC

@implementation UICHMView 

@synthesize main;

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    main.frame = rc;
}

@end

NNT_END_OBJC