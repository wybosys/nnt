
# import "Core.h"
# import "UIBanner.h"
# import <QuartzCore/QuartzCore.h>
# import "NGGradient.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

@implementation UIBanner

@synthesize according;
@synthesize delegate;
@synthesize bannerPosition;
@synthesize indicatorEnable;
@synthesize indicatorPosition;
@synthesize textLabel;
@synthesize backgroundFill;
@synthesize height;

- (id)initWithAccording:(UIView*)__view {
    self = [super initWithZero];      
    
    bannerPosition = UIBannerPositionTop;
    indicatorEnable = NO;
    
    textLabel = [[UILabel alloc] initWithZero];
    textLabel.backgroundColor = [UIColor clearColor];
    textLabel.textColor = [UIColor whiteColor];
    [self addSubview:textLabel];
    
    height = 50;
    
    self.according = __view;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)setAccording:(UIView *)__according {
    if (according == __according)
        return;
    [according removeFromSuperview];
    according = __according;
    
    if (according) {
        [according addSubview:self];
        [according bringSubviewToFront:self];
        [self updateShow];
    }
}

- (void)setNeedsDisplay {
    [super setNeedsDisplay];
    [self updateShow];
}

- (void)updateShow {
    if (according == nil)
        return;
    
    CGRect rc = according.bounds;
    switch (bannerPosition) {
        case UIBannerPositionTop: {
            rc.size.height = height;
        } break;
        case UIBannerPositionBottom: {            
            rc.origin.y = rc.origin.y + rc.size.height - height;
            rc.size.height = height;
        } break;
        case UIBannerPositionLeft: {
            rc.size.width = height;
        } break;
        case UIBannerPositionRight: {
            rc.origin.x = rc.origin.x + rc.size.width - height;
            rc.size.width = height;
        } break;
    }
    
    self.frame = rc;    
    textLabel.frame = CGRectMake(0, 0, rc.size.width, rc.size.height);
}

- (void)hide {
    CATransition *trans = [CATransition animation];
    [trans setDuration:1.f];
    [trans setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseOut]];
    [trans setType:kCATransitionFade];
    [self.layer addAnimation:trans forKey:@"Fade"];
    self.hidden = YES;   
}

- (void)show {
    CATransition *trans = [CATransition animation];
    [trans setDuration:.2f];
    [trans setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseIn]];
    [trans setType:kCATransitionFade];
    [self.layer addAnimation:trans forKey:@"Fade"];
    self.hidden = NO;
}

- (void)drawRect:(CGRect)rect {
    CGContextRef context = UIGraphicsGetCurrentContext();  
    
    CGContextSaveGState(context);
    
    if (backgroundFill == nil) {
        switch (bannerPosition) {
            case UIBannerPositionTop: case UIBannerPositionBottom: {
                NgGradient *color = [NgGradient gradientWithBeginningColor:[NgColor colorWithRGB:0x777777] endingColor:[NgColor colorWithRGB:0x000000]];
                color.angle = 90;
                self.backgroundFill = [NgFill fillWithGradient:color];
            } break;
            case UIBannerPositionLeft: case UIBannerPositionRight: {
                self.backgroundFill = [NgFill fillWithColor:[NgColor blackColor]];
            } break;
        }        
    }
    
    [backgroundFill fillRect:rect inContext:context];
    
    CGContextRestoreGState(context);
}

- (void)layoutSubviews {
    if ([delegate respondsToSelector:@selector(bannerLayoutSubViews:)]) {
        [delegate bannerLayoutSubViews:self];
    }
}

@end

NNT_END_OBJC