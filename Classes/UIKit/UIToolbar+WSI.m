
# import "Core.h"
# import "UIToolbar+NNT.h"

NNT_BEGIN_OBJC

@implementation NNTUIToolbar

NNTOBJECT_IMPL;

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    if (self.backgroundColor) {
        return;
    }
    
    [super drawRect:rect];
}

@end

NNT_END_OBJC