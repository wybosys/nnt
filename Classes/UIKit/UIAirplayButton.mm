
# import "Core.h"
# import "UIAirplayButton.h"
# import <MediaPlayer/MPVolumeView.h>

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

@implementation UIAirplayButton

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    if ([UIAirplayButton IsSupported]) {
        _volume = [[MPVolumeView alloc] init];
    }
    
    _volume.showsVolumeSlider = NO;
    //_volume.backgroundColor = [UIColor blackColor];
    [_volume sizeToFit];
    
    [self addSubview:_volume];
    
    return self;
}

- (void)dealloc {
    safe_release(_volume);
    [super dealloc];
}

- (void)layoutSubviews {
    cg::Rect rc(self.bounds);
    [_volume moveToCenter:rc.center()];
}

+ (BOOL)IsSupported {
    return [UIDevice currentDevice].systemVersion.doubleValue >= 4.2;
}

/*
- (void)setBackgroundColor:(UIColor *)backgroundColor {
    [super setBackgroundColor:backgroundColor];
    _volume.backgroundColor = backgroundColor;
}
 */

@end

_CXXCONTROL_IMPL(UIAirplayButton);

NNT_END_OBJC
