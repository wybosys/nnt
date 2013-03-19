
# import "Core.h"
# import "UIWindow+WSI.h"
# import "UIScreen+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalBecomeKey = @"::wsi::window::key::become";
signal_t kSignalResignKey = @"::wsi::window::key::resign";

@implementation UIWindow (WSI)

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

@implementation WSIUIWindow

WSIOBJECT_IMPL_NOSIGNALS;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    
    return self;
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    WSIEVENT_SIGNAL(kSignalBecomeKey);
    WSIEVENT_SIGNAL(kSignalResignKey);
}

- (void)becomeKeyWindow {
    [self emit:kSignalBecomeKey];
}

- (void)resignKeyWindow {
    [self emit:kSignalResignKey];
}

@end

WSIIMPL_CATEGORY(UIWindow, WSI);

WSI_END_OBJC
