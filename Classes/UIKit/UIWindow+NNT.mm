
# import "Core.h"
# import "UIWindow+NNT.h"
# import "UIScreen+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalBecomeKey = @"::nnt::window::key::become";
signal_t kSignalResignKey = @"::nnt::window::key::resign";

@implementation UIWindow (NNT)

- (CGRect)boundsOnScreen {
    CGRect rc = self.bounds;
    rc = [UIScreen convertCurrentRect:rc];
    return rc;
}

- (CGRect)frameOnScreen {
    CGRect rc = self.bounds;
    rc = [UIScreen convertCurrentRect:rc];
    return rc;
}

- (CGRect)locationIn:(UIView*)view {
    CGRect rcself = self.boundsOnScreen;
    CGRect rc = [self convertRect:view.frame fromView:view.superview];
    rc = [UIScreen convertCurrentRect:rc];
    switch ([UIScreen orientation])
    {
        case UIInterfaceOrientationPortrait: {
        } break;
        case UIInterfaceOrientationPortraitUpsideDown: {
            rc.origin.y = rcself.size.height - rc.origin.y;
        } break;
        case UIInterfaceOrientationLandscapeLeft: {
        } break;
        case UIInterfaceOrientationLandscapeRight: {
            rc.origin.y = rcself.size.height - rc.origin.y;
        } break;
    }
    return rc;
}

- (void)offsetX:(int)x Y:(int)y {
    CGPoint pt = self.frameOnScreen.origin;
    pt.x += [UIScreen convertCurrentOffset:x];
    pt.y += [UIScreen convertCurrentOffset:y];
    pt = [UIScreen convertCurrentPoint:pt];
    CGRect rc = self.frame;
    rc.origin = pt;
    self.frame = rc;
}

- (UIWindow*)window {
    return self;
}

- (UIView*)root {
    return self;
}

@end

@implementation NNTUIWindow

NNTOBJECT_IMPL_NOSIGNALS;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalBecomeKey);
    NNTEVENT_SIGNAL(kSignalResignKey);
}

- (void)becomeKeyWindow {
    [self emit:kSignalBecomeKey];
}

- (void)resignKeyWindow {
    [self emit:kSignalResignKey];
}

@end

NNTIMPL_CATEGORY(UIWindow, NNT);

NNT_END_OBJC
