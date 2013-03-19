
# import "Core.h"
# import "UISwitchView.h"
# import "UISwitchController.h"

NNT_BEGIN

@implementation UISwitchView

@synthesize switcher;

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    
    if (switcher == nil) 
        return;
    
    UISwitchPage *cur = [switcher cur_page];
    if (cur == nil) 
        return;
    
    [cur.view setFrame:rc];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    
}

@end

NNT_END