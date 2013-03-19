
# import "Core.h"
# import "UIToolbar+WSI.h"

WSI_BEGIN_OBJC

@implementation WSIUIToolbar

WSIOBJECT_IMPL;

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    if (self.backgroundColor) {
        return;
    }
    
    [super drawRect:rect];
}

@end

WSI_END_OBJC