
# import "Core.h"
# import "UINavigationDialView.h"
# import "UINavigationDial.h"
# import "Graphic+NNT.h"

NNT_BEGIN_OBJC

@interface UINavigationDialView ()

- (void)updateLayout;

@end

@implementation UINavigationDialView

@synthesize contentView;
@synthesize dial, dialPosition;

- (id)initWithFrame:(CGRect)frame {
    dialPosition = UINavigationDialPositionCustom;
    
    self = [super initWithFrame:frame];       
    
    dial = [[UINavigationDial alloc] initWithZero];
    [self addSubview:dial];
    [dial release];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)setContentView:(UIView *)__contentView {
    [contentView removeFromSuperview];
    
    //[self addSubview:__contentView];
    
    contentView = __contentView;    
    contentView.frame = self.bounds;        
    
    [self addSubview:__contentView];
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    [self updateLayout];
}

//- (void)setBounds:(CGRect)bounds {
//    [super setBounds:bounds];
//}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    contentView.frame = self.bounds;
    
    [self updateLayout];
}

- (void)updateLayout {
    if (dialPosition != UINavigationDialPositionCustom) {
        [self setPositionByEnum:dialPosition];
    }
}

- (void)addSubview:(UIView *)view {
    [super addSubview:view];

    [self bringSubviewToFront:dial];
}

- (void)setPositionByEnum:(UINavigationDialPosition)position {    
    CGRect rc = self.bounds;
    CGPoint pt = CGPointZero;
    BOOL update = YES;    
    
    switch (position) {
        case UINavigationDialPositionLeftTop: pt = rc.origin; break;
        case UINavigationDialPositionLeftCenter: pt = CGRectLeftCenter(&rc); break;
        case UINavigationDialPositionLeftBottom: pt = CGRectLeftBottom(&rc); break;
        case UINavigationDialPositionRightTop: pt = CGRectRightTop(&rc); break;
        case UINavigationDialPositionRightCenter: pt = CGRectRightCenter(&rc); break;
        case UINavigationDialPositionRightBottom: pt = CGRectRightBottom(&rc); break;
        case UINavigationDialPositionTopCenter: pt = CGRectTopCenter(&rc); break;
        case UINavigationDialPositionBottomCenter: pt = CGRectBottomCenter(&rc); break;
        case UINavigationDialPositionCenter: pt = CGRectCenterPoint(&rc); break;
        case UINavigationDialPositionCustom: update = NO; break;
    }
    
    dialPosition = position;

    if (update)
        [dial moveToCenter:pt];
}

@end

NNT_END_OBJC