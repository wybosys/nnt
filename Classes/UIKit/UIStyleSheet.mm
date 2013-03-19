
# import "Core.h"
# import "UIStyleSheet.h"

NNT_BEGIN_OBJC

NSString* kStyleBackground = @"background";

@implementation UIStyleSheet

@dynamic backgroundFill;

- (NgFill*)backgroundFill {
    NgFillStyle* style = (NgFillStyle*)[self styleForKey:kStyleBackground];
    if (style == nil)
        return nil;
    return style.fill;
}

- (void)setBackgroundFill:(NgFill*)fill {
    if (fill == nil) {
        [self removeStyleForKey:kStyleBackground];
        return;
    }
    NgFillStyle* style = [[NgFillStyle alloc] init];
    style.fill = fill;    
    [self addStyle:style forKey:kStyleBackground];
    [style release];
}

@end

NNT_END_OBJC