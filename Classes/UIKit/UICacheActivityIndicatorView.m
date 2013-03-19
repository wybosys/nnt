
# import "Core.h"
# import "UICacheActivityIndicatorView.h"
# import "CoreGraphic+NNT.h"
# import "UIActivityIndicatorView+NNT.h"

NNT_BEGIN_OBJC

@implementation UICacheActivityIndicatorView

@synthesize activityIndicator;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    activityIndicator = [[NNTUIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
    activityIndicator.frame = CGRectMakeSz(CGSizeMake(20, 20));
    [self addSubview:activityIndicator];
    
    self.backgroundColor = [UIColor orangeColor];
    self.layer.cornerRadius = 5;
    self.layer.masksToBounds = YES;
    self.alpha = .6f;
    
    return self;
}

- (void)dealloc {
    zero_release(activityIndicator);
    [super dealloc];
}

- (void)layoutSubviews {
    CGRect rc_client = self.bounds;
    CGPoint pt_center = CGRectCenterPoint(&rc_client);
    [activityIndicator moveToCenter:pt_center];
}

- (void)startAnimating {
    [activityIndicator startAnimating];
}

- (void)stopAnimating {
    [activityIndicator stopAnimating];
}

@end

NNT_END_OBJC