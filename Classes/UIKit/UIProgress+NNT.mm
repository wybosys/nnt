
# import "Core.h"
# import "UIProgress+NNT.h"

NNT_BEGIN_OBJC

@implementation UIProgressControl

@synthesize progressViewStyle;
@dynamic progress;
@synthesize max = _max, value = _value;
@dynamic progressTintColor, trackTintColor, progressImage, trackImage;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    progressViewStyle = UIProgressViewStyleDefault;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalValueChanged)
NNTEVENT_END

- (UIProgressView*)progressView {
    if (_progressView == nil) {
        _progressView = [[UIProgressView alloc] initWithProgressViewStyle:progressViewStyle];
        [self addSubview:_progressView];
        safe_release(_progressView);
    }
    return _progressView;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    [self progressView].frame = self.bounds;
}

- (float)progress {
    return [self progressView].progress;
}

- (void)setProgress:(float)val {
    if (self.progress == val)
        return;
    
    [self progressView].progress = val;
    [self emit:kSignalValueChanged];
}

- (void)setMax:(float)max {
    _max = max;
    
    if (_value != 0) {
        self.progress = _value / _max;
    } else {
        self.progress = 0;
    }
}

- (void)setValue:(float)value {
    _value = value;
    
    if (_value != 0) {
        self.progress = _value / _max;
    } else {
        self.progress = 0;
    }
}

- (void)setProgressTintColor:(UIColor*)colr {
    [self progressView].progressTintColor = colr;
}

- (UIColor*)progressTintColor {
    return [self progressView].progressTintColor;
}

- (void)setTrackTintColor:(UIColor*)colr {
    [self progressView].trackTintColor = colr;
}

- (UIColor*)trackTintColor {
    return [self progressView].trackTintColor;
}

- (void)setProgressImage:(UIImage*)img {
    [self progressView].progressImage = img;
}

- (UIImage*)progressImage {
    return [self progressView].progressImage;
}

- (void)setTrackImage:(UIImage*)img {
    [self progressView].trackImage = img;
}

- (UIImage*)trackImage {
    return [self progressView].trackImage;
}

@end

_CXXCONTROL_IMPL(UIProgressControl);

NNT_END_OBJC
