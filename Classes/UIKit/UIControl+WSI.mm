
# import "Core.h"
# import "UIControl+NNT.h"
# import "WCGFill.h"

NNT_BEGIN_OBJC

@implementation NNTUIControl

NNTOBJECT_IMPL;

@synthesize backgroundFill;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (void)dealloc {
    zero_release(backgroundFill);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {        
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    [backgroundFill fillRect:rect inContext:ctx];
    
    [super drawRect:rect];
}

@end

NNT_END_OBJC