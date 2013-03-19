
# import "Core.h"
# import "UIInitialView.h"
# import "UIDevice+NNT.h"
# import "NNTResource.h"
# import "NNTUIObject.h"

NNT_BEGIN_OBJC

signal_t kSignalInitialWillComplete = @"::wsi::ui::initial::complete::will";
signal_t kSignalInitialComplete = @"::wsi::ui::initial::complete";

@implementation UIInitialView

@synthesize imageView = _image;
@synthesize delegate = _delegate;
@synthesize delay = _delay;
@synthesize orientationEnable = _orientationEnable;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _image = [[NNTUIImageView alloc] initWithZero];
    [self addSubview:_image];
    [_image release];
    
    // init.
    _counter = 0;
    _delegate = self;
    _delay = 1;
    _orientationEnable = UIOrientationEnableAll;
    
    // set default image.
    UIScreenImage* si = [UIInitialView ScreenImage];
    _image.image = [UIImage imageNamed:si.name];
    
    [[NNTUIObject shared] connect:kSignalOrientationChanged sel:@selector(_act_orientation_changed) obj:self];
    
    return self;
}

- (void)dealloc {
    [[NNTUIObject shared] disconnect:self];
    
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalInitialWillComplete)
NNTEVENT_SIGNAL(kSignalInitialComplete)
NNTEVENT_END

- (void)layoutSubviews {
    _image.frame = self.bounds;
}

+ (UIScreenImage*)ScreenImage {
    enum {
        IDX_IPHONE_NORMAL,
        IDX_IPHONE_RETINA,
        IDX_IPHONE_RETINA4,
        
        IDX_IPAD_LANDSCAPE_NORMAL,
        IDX_IPAD_LANDSCAPE_RETINA,
        IDX_IPAD_PORTRAIT_NORMAL,
        IDX_IPAD_PORTRAIT_RETINA,
        
        IDX_COUNT
    };
    
    UIInterfaceOrientation oris[IDX_COUNT] = {
        UIInterfaceOrientationPortrait,
        UIInterfaceOrientationPortrait,
        UIInterfaceOrientationPortrait,
        
        UIInterfaceOrientationLandscapeLeft,
        UIInterfaceOrientationLandscapeLeft,
        UIInterfaceOrientationPortrait,
        UIInterfaceOrientationPortrait,
    };
    
    NSString* names[IDX_COUNT] = {
        // iphone
        @"Default.png",
        @"Default@2x.png",
        @"Default-568h@2x.png",
        
        // ipad
        @"Default-Landscape~ipad.png",
        @"Default-Landscape@2x~ipad.png",        
        @"Default-Portrait~ipad.png",
        @"Default-Portrait@2x~ipad.png"
    };
    
    bool exists[IDX_COUNT] = {
        false,
        false,
        false,
        false,
        false,
        false,
        false
    };
    
    for (uint i = 0; i < IDX_COUNT; ++i) {
        exists[i] = [NNTResource IsExist:names[i]];
    }
    
    UIScreenImage* ret = [[UIScreenImage alloc] init];
    //UIDeviceOrientation ori = [UIDevice currentDevice].orientation;
    UIInterfaceOrientation ori = [UIScreen orientation];
    
    if ([UIDevice isIPad] || [UIDevice isIPadSimulator]) {
        if (UIInterfaceOrientationIsLandscape(ori)) {
            if ([UIScreen isRetina]) {
                if (exists[IDX_IPAD_LANDSCAPE_RETINA]) {
                    ret.name = names[IDX_IPAD_LANDSCAPE_RETINA];
                    ret.orientation = ori;
                }
            }
            
            if (ret.name == nil) {
                if (exists[IDX_IPAD_LANDSCAPE_NORMAL]) {
                    ret.name = names[IDX_IPAD_LANDSCAPE_NORMAL];
                    ret.orientation = ori;
                }
            }
            
            if (ret.name == nil) {
                if (exists[IDX_IPAD_LANDSCAPE_RETINA]) {
                    ret.name = names[IDX_IPAD_LANDSCAPE_RETINA];
                    ret.orientation = ori;
                }
            }
        }
        
        if (UIInterfaceOrientationIsPortrait(ori)) {
            if ([UIScreen isRetina]) {
                if (exists[IDX_IPAD_PORTRAIT_RETINA]) {
                    ret.name = names[IDX_IPAD_PORTRAIT_RETINA];
                    ret.orientation = ori;
                }
            }
            
            if (ret.name == nil) {
                if (exists[IDX_IPAD_PORTRAIT_NORMAL]) {
                    ret.name = names[IDX_IPAD_PORTRAIT_NORMAL];
                    ret.orientation = ori;
                }
            }
            
            if (ret.name == nil) {
                if (exists[IDX_IPAD_PORTRAIT_RETINA]) {
                    ret.name = names[IDX_IPAD_PORTRAIT_RETINA];
                    ret.orientation = ori;
                }
            }
        }                
    }
    
    if (ret.name == nil) {
        if ([UIScreen isRetina]) {
            if (exists[IDX_IPHONE_RETINA]) {
                ret.name = names[IDX_IPHONE_RETINA];
                ret.orientation = ori;
            }
        }
        
        if (ret.name == nil) {
            if (exists[IDX_IPHONE_NORMAL]) {
                ret.name = names[IDX_IPHONE_NORMAL];
                ret.orientation = ori;
            }
        }
        
        if (ret.name == nil) {
            if (exists[IDX_IPHONE_RETINA]) {
                ret.name = names[IDX_IPHONE_RETINA];
                ret.orientation = ori;
            }
        }
    }
    
    if (ret.name == nil) {
        for (uint i = 0; i < IDX_COUNT; ++i) {
            if (exists[i]) {
                ret.name = names[i];
                ret.orientation = oris[i];
                break;
            }
        }
    }
    
    return [ret autorelease];
}

- (void)show {
    _win = [[NNTUIWindow alloc] initWithZero];
    _win.windowLevel = UIWindowLevelNormal + 1;
    
    // create window.
    NNTUIViewController* ctlr = [[NNTUIViewController alloc] init];
    ctlr.view = self;
    ctlr.orientationEnable = _orientationEnable;
    _win.rootViewController = ctlr;
    [ctlr release];
    
    // show window.
    [_win connect:kSignalBecomeKey sel:@selector(_keywin_become) obj:self];
    [_win connect:kSignalResignKey sel:@selector(_keywin_resign) obj:self];
    [_win makeKeyAndVisible];
}

- (void)hide {
    [self hide:YES];
}

- (void)hideImmed {
    [self hide:NO];
}

- (void)hide:(BOOL)animated {
    [self emit:kSignalInitialWillComplete];
    
    if (animated == NO) {
        [self _do_hide];
        return;
    }
        
    if (_delay == 0) {
        [self _do_animated_close];
    } else {
        NNT_MAINTHREAD(
                       [self performSelector:@selector(_do_animated_close) withObject:nil afterDelay:_delay];
                       );
    }
}

- (void)_do_animated_close {
    NNTUIAnimation* ani = [[NNTUIAnimation alloc] init];
    ani.duration = 1.f;
    
    [ani connect:kSignalAnimationRun sel:@selector(_ani_hiding) obj:self];
    [ani connect:kSignalAnimationStop sel:@selector(_do_hide) obj:self];
    
    [ani begin];
    [ani commit];
    [ani release];
}

- (void)_ani_hiding {
    CGRect rc = self.frame;
    real ratio = .4f;
    CGAffineTransform af = CGAffineTransformIdentity;
    af = CGAffineTransformTranslate(af, rc.size.width * -ratio * .5f, rc.size.height * -ratio * .5f);
    af = CGAffineTransformScale(af, 1 + ratio, 1 + ratio);
    
    _win.transform = af;
    _win.alpha = 0;
}

- (void)_do_hide {
    zero_release(_win);
    
    [self emit:kSignalInitialComplete];
}

- (void)_keywin_become {
    [_delegate initialViewWork:self];
}

- (void)_keywin_resign {
    PASS;
}

- (void)initialViewWork:(UIInitialView*)view {
    PASS;
}

- (void)_act_orientation_changed {
    // change image.
    UIScreenImage* si = [UIInitialView ScreenImage];
    _image.image = [UIImage imageNamed:si.name];
}

@end

_CXXVIEW_IMPL_BEGIN(UIInitialView)

- (void)initialViewWork:(UIInitialView*)view {
    [self performSelectorInBackground:@selector(_do_initialViewWork:) withObject:view];
}

- (void)_do_initialViewWork:(UIInitialView*)view {
    ((::wsi::ui::IInitialView*)self._cxxobj)->work();
}

_CXXVIEW_IMPL_END

NNT_END_OBJC
