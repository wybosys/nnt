
# import "Core.h"
# import "UIDesktop.h"
# import <QuartzCore/QuartzCore.h>
# import "UIDevice+WSI.h"
# import "CoreGraphic+WSI.h"
# import "UIScreen+WSI.h"
# import "App.h"
# import "QzEffect.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

NSString *kSignalClosed = @"::wsi::closed";
NSString *kSignalShown = @"::wsi::shown";

@implementation WSIUIDesktop

@synthesize contentFrame = _contentFrame, preferredContentFrame = _preferredContentFrame;
@synthesize enableAutoClose = _enableAutoClose, enableAutoCloseAnimated = _enableAutoCloseAnimated;
@synthesize effectClose = _effectClose, effectShow = _effectShow;

+ (WSIUIDesktop*)desktop {
    return [[[WSIUIDesktop alloc] initWithZero] autorelease];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    // default.
    self.userInteractionEnabled = YES;
    _enableAutoClose = NO;
    _enableAutoCloseAnimated = YES;
    _preferredContentFrame = CGRectZero;
    
    // default effect.
    // show.
    {
        instance_ref<qz::effect::Slide> ef;
        instance_ref<qz::effect::Fadein> fd;
        ef->direction = qz::effect::Slide::TOP;
        ef->accord(*fd);
        self.effectShow = *ef;
    }
    // close
    {
        instance_ref<qz::effect::Slide> ef;
        instance_ref<qz::effect::Fadeout> fd;
        ef->in = false;
        ef->direction = qz::effect::Slide::BOTTOM;
        ef->accord(*fd);
        self.effectClose = *ef;
    }
    
    // set default position.
    UIView* parent = [WSIApplication shared].window.rootViewController.view;
    self.frame = parent.bounds;
    
    // sigs.
    [self connect:kSignalTouchesBegin sel:@selector(_act_desktop_touches_began:)];
    [self connect:kSignalTouchesMoved sel:@selector(_act_desktop_touches_moved:)];
    [self connect:kSignalTouchesEnd sel:@selector(_act_desktop_touches_ended:)];
    
    return self;
}

- (void)dealloc {
    safe_release(_effectShow);
    safe_release(_effectClose);
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalShown)
WSIEVENT_SIGNAL(kSignalClosed)
WSIEVENT_END

- (void)show:(BOOL)animated {
    [self retain];
    
    // force layout.
    [self layoutSubviews];
    
    // add view and show.
    UIView* parent = [WSIApplication shared].window.rootViewController.view;
    [parent addSubview:self];
    
    if (animated) {
        for (UIView *each in self.contentViews) {
            [_effectShow active:each.layer];
        }
    }
    
    [self emit:kSignalShown];
}

- (void)show {
    [self show:YES];
}

- (void)close:(BOOL)animated {    
    [self emit:kSignalClosed];        
    
    if (animated) {
        for (UIView *each in self.contentViews) {
            [_effectClose active:each.layer];
        }
        
        WSI_MAINTHREAD(
        [self performSelector:@selector(act_close)
                   withObject:nil
                   afterDelay:kQzEffectDuration]
                       );
        
    } else {
        [self performSelectorOnMainThread:@selector(act_close)
                               withObject:nil
                            waitUntilDone:YES];
    }        
}

- (NSArray*)contentViews {
    return self.subviews;
}

- (void)close {
    [self close:YES];
}

- (void)act_close {
    //self.hidden = YES;
    [self removeFromSuperview];
    
    [self release];
}

- (CGRect)contentFrame {
    if ([self.subviews count] == 0)
        return CGRectZero;
    
    CGRect rc = ((UIView*)[self.subviews objectAtIndex:0]).frame;
    
    for (uint i = 1; i < [self.subviews count]; ++i) {
        rc = CGRectUnion(rc, ((UIView*)[self.subviews objectAtIndex:i]).frame);
    }
    
    return rc;
}

- (void)_act_desktop_touches_began:(WSIEventObj*)evt {
    PASS;
}

- (void)_act_desktop_touches_ended:(WSIEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    
    if (_enableAutoClose == NO)
        return;
    
    CGPoint pt = [[touches anyObject] locationInView:self];
    
    CGRect rc = _preferredContentFrame;
    if (CGRectEqualToRect(CGRectZero, rc))
        rc = self.contentFrame;
    
    if (CGRectContainsPoint(rc, pt) == NO) {
        [self close:_enableAutoCloseAnimated];
    }
}

- (void)_act_desktop_touches_moved:(WSIEventObj*)evt {
    PASS;
}

- (BOOL)hitTestInContent:(CGPoint)pt {
    CGRect rc = self.contentFrame;
    return CGRectContainsPoint(rc, pt);
}

@end

_CXXVIEW_IMPL_BEGIN(WSIUIDesktop)

- (NSArray*)contentViews {
    ui::IDesktop* cxx = dynamic_cast<ui::IDesktop*>(self._cxxobj);
    return cxx->contents();
}

_CXXVIEW_IMPL_END

WSI_END_OBJC
