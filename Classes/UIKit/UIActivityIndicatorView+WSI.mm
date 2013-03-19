
# import "Core.h"
# import "UIActivityIndicatorView+NNT.h"
# import "WCAActivityIndicator.h"
# import "Math+NNT.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

@interface NNTUIActivityIndicatorView ()

- (real)progressAngle;
- (void)setRingColorWithStyle:(UIActivityIndicatorViewStyle)style;

@end

@implementation NNTUIActivityIndicatorView

@synthesize indicatorActivity, progressValue, progressMax, showProgressRing, activityView;

- (void)activityIndicatorInitView {
    showProgressRing = NO;
    progressValue = 0;
    progressMax = 1;
}

- (id)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style {
    self = [super initWithZero];
    
    [self activityIndicatorInitView];
    
    activityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:style];
    [self addSubview:activityView];
    [activityView release];
    
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];

    [self activityIndicatorInitView];
    
    activityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
    [self addSubview:activityView];
    [activityView release];
    
    return self;
}

- (id)initWithFrame:(CGRect)frame activityIndicatorStyle:(UIActivityIndicatorViewStyle)style {
    self = [super initWithFrame:frame];
    
    [self activityIndicatorInitView];
    
    activityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:style];
    [self addSubview:activityView];
    [activityView release];
    
    return self;
}

- (void)dealloc {
    activityView = nil;
    zero_release(indicatorActivity);
    [super dealloc];
}

- (void)setRingColorWithStyle:(UIActivityIndicatorViewStyle)style {
    WCGColor *color = nil;
    switch (style) {
        case UIActivityIndicatorViewStyleGray: color = [WCGColor grayColor]; break;
        case UIActivityIndicatorViewStyleWhite:
        case UIActivityIndicatorViewStyleWhiteLarge:
            color = [WCGColor whiteColor]; break;
    }
    
    if (color && indicatorActivity) {
        indicatorActivity.ringColor = color;
    }
}

- (void)setProgressValue:(real)val {    
    if (progressValue == val)
        return;
    progressValue = val;
    
    if (indicatorActivity && !indicatorActivity.hidden) {        
        indicatorActivity.endAngle = self.progressAngle;
        [indicatorActivity performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:NO];
    }
}

- (real)progressAngle {
    real ang = progressValue / progressMax;
    ang *= M_2PI;
    ang = M_2PI_RESTRICT2(ang);
    return ang;
}

- (void)setShowProgressRing:(BOOL)val {
    if (showProgressRing == val)
        return;
    showProgressRing = val;
    
    if (showProgressRing)
        [self performSelectorOnMainThread:@selector(_showProgressRing) withObject:nil waitUntilDone:YES];
    else
        [self performSelectorOnMainThread:@selector(_hideProgressRing) withObject:nil waitUntilDone:YES];
}

- (void)_showProgressRing {
    // create indicator.
    if (indicatorActivity == nil) {
        indicatorActivity = [[WCAActivityIndicator alloc] init];
        indicatorActivity.startAngle = 0;
        indicatorActivity.endAngle = self.progressAngle;
        [self.layer addSublayer:indicatorActivity];
        [self setRingColorWithStyle:activityView.activityIndicatorViewStyle];
    }
    
    indicatorActivity.hidden = NO;
}

- (void)_hideProgressRing {
    indicatorActivity.hidden = YES;
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
}

- (void)layoutSubviews {        
    CGRect rc_client = self.bounds;

    // layout activity.
    CGRect rc_activity = rc_client;
    if (showProgressRing) {
        rc_activity = CGRectDeflateCenter(rc_client, 
                                          indicatorActivity.ringWidth + indicatorActivity.ringWidth, 
                                          indicatorActivity.ringWidth + indicatorActivity.ringWidth);
    }
    activityView.frame = rc_activity;
    
    // layout progress ring.
    if (showProgressRing) {
        indicatorActivity.frame = CGRectDeflateCenter(rc_client, 2, 2);
    }
}

- (void)startAnimating {
    [activityView startAnimating];
}

- (void)stopAnimating {
    [activityView stopAnimating];
}

@end

_CXXVIEW_IMPL(NNTUIActivityIndicatorView);

NNT_END_OBJC
