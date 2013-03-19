
# import "Core.h"
# import "DTraceLogoSwitch.h"
# import "DTrace.res"
# import "DTraceController.h"

NNT_BEGIN_OBJC

@implementation DTraceLogoSwitch

+ (id)logoSwitch {
    NgImage* wcgimage = NgImageLoadPngData(png_dtrace_logo, sizeof(png_dtrace_logo));
    UIImage* image = [UIImage imageWithCGImage:wcgimage.image];
    DTraceLogoSwitch* ret = [[DTraceLogoSwitch alloc] initWithImage:image];
    
    ret.userInteractionEnabled = YES;
    ret.layer.shadowOpacity = 1.f;
    ret.layer.shadowOffset = CGSizeMake(0, 3);
    ret.layer.borderWidth = 2.f;
    ret.layer.borderColor = [UIColor whiteColor].CGColor;
    
    [ret connect:kSignalViewClicked sel:@selector(act_clicked)];
    
    return [ret autorelease];
}

- (void)act_clicked {
    if (_skipmoved) {
        _skipmoved = false;
        return;
    }
    
    DTraceController* ctlr = [DTraceController shared];
    ctlr.viewForSwitch = self;
    [ctlr show];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    [super touchesMoved:touches withEvent:event];
    
    CGPoint offset = [(UITouch*)[touches anyObject] offset];
    CGRect frame = self.frame;
    frame.origin.x += offset.x;
    frame.origin.y += offset.y;
    self.frame = frame;
    
    _skipmoved = true;
}

@end

NNT_END_OBJC