
# import "Core.h"
# import "UIStyleSheet.h"

NNT_BEGIN_OBJC

NSString* kStyleBackground = @"background";

@implementation UIStyleSheet

@dynamic backgroundFill;

- (WCGFill*)backgroundFill {
    WCGFillStyle* style = (WCGFillStyle*)[self styleForKey:kStyleBackground];
    if (style == nil)
        return nil;
    return style.fill;
}

- (void)setBackgroundFill:(WCGFill*)fill {
    if (fill == nil) {
        [self removeStyleForKey:kStyleBackground];
        return;
    }
    WCGFillStyle* style = [[WCGFillStyle alloc] init];
    style.fill = fill;    
    [self addStyle:style forKey:kStyleBackground];
    [style release];
}

@end

NNT_END_OBJC