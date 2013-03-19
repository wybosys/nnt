
# import "Core.h"
# import "UIWaiting.h"
# import "CoreGraphic+NNT.h"
# import "App.h"

NNT_BEGIN_OBJC

static int popup_count = 0;
static int overlap_count = 0;

@implementation UIWaitingPopup

+ (id)shared {
    static UIWaitingPopup* __gs_waitingpopup;
    NNT_SYNCHRONIZED(self)
    if (!__gs_waitingpopup)
        __gs_waitingpopup = [[self alloc] init];
    NNT_SYNCHRONIZED_END
    return __gs_waitingpopup;
}

- (id)init {
    self = [super init];
    
    _alert = [[UIAlertView alloc] initWithTitle:@""
                                        message:@"\r"
                                       delegate:nil
                              cancelButtonTitle:nil
                              otherButtonTitles:nil];
    
    return self;
}

- (void)dealloc {
    safe_release(_alert);
    [super dealloc];
}

- (void)show {    
    popup_count += 1;
    if (popup_count == 1) {                
        UIActivityIndicatorView *avi = [[UIActivityIndicatorView alloc]
                                        initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
        avi.frame = CGRectMake(120, 40, 50, 50);
        [_alert addSubview:avi];				
		[avi startAnimating];
		[avi release];        
        
        [_alert show];
    }
}

- (void)hide {
    popup_count -= 1;
    if (popup_count == 0) {
        [_alert dismissWithClickedButtonIndex:0 animated:YES];
    }
}

@end

@implementation UIWaitingOverlap

+ (id)shared {
    static UIWaitingOverlap* __gs_waiting;
    NNT_SYNCHRONIZED(self)
    if (!__gs_waiting)
        __gs_waiting = [[self alloc] init];
    NNT_SYNCHRONIZED_END
    return __gs_waiting;
}

- (id)init {
    self = [super init];
    
    UIView* root = [NNTApplication shared].window.rootViewController.view;
    _hud = [[UIView alloc] initWithFrame:root.bounds];
    
    return self;
}

- (void)dealloc {
    zero_release(_hud);
    [super dealloc];
}

- (void)show {
    [self performSelectorOnMainThread:@selector(_doShow) withObject:nil waitUntilDone:YES];
}

- (void)_doShow {
    overlap_count += 1;
    if (overlap_count == 1) {
        UIView* root = [NNTApplication shared].window.rootViewController.view;
        _hud = [[UIView alloc] initWithFrame:root.bounds];
        
        // add label.
        UIView* _lbl = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
        [_hud addSubview:_lbl];
        [_lbl release];
        [_lbl moveToCenter:CGRectCenterPoint2(_hud.bounds)];
        _lbl.backgroundColor = [UIColor darkGrayColor];
        _lbl.layer.cornerRadius = 5;
        
        // add ani.
        UIActivityIndicatorView *avi = [[UIActivityIndicatorView alloc]
                                        initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
        avi.frame = CGRectMake(0, 0, 50, 50);
        [avi moveToCenter:CGRectCenterPoint2(_lbl.bounds)];
        [_lbl addSubview:avi];
		[avi startAnimating];
		[avi release];
        
        [root addSubview:_hud];
        
        // ani.
        CATransition* ani = [CATransition animation];
        ani.duration = .35f;
        ani.type = kCATransitionFade;
        ani.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseIn];
        [_hud.layer addAnimation:ani forKey:nil];
    }
}

- (void)hide {
    [self performSelectorOnMainThread:@selector(_doHide) withObject:nil waitUntilDone:YES];
}

- (void)_doHide {
    overlap_count -= 1;
    if (overlap_count == 0) {
        [_hud removeFromSuperview];
        zero_release(_hud);
        
        /*
         CATransition* ani = [CATransition animation];
         ani.duration = .35f;
         ani.type = kCATransitionFade;
         ani.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseOut];
         ani.delegate = self;
         [_hud.layer addAnimation:ani forKey:@"end"];
         */
    }
}

- (void)animationDidStart:(CAAnimation *)anim {
    PASS;
}

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag {
    [_hud removeFromSuperview];
    zero_release(_hud);
    
    [self unlock];
}

@end

NNT_END_OBJC