
# import "Core.h"
# import "UIControl+WSI.h"
# import "WCGFill.h"

WSI_BEGIN_OBJC

@implementation WSIUIControl

WSIOBJECT_IMPL;

@synthesize backgroundFill;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (void)dealloc {
    zero_release(backgroundFill);
    
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {        
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    [backgroundFill fillRect:rect inContext:ctx];
    
    [super drawRect:rect];
}

@end

WSI_END_OBJC