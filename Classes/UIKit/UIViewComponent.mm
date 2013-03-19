
# import "Core.h"
# import "UIViewComponent.h"
# import "UILabel+NNT.h"
# import "Layout.h"

NNT_BEGIN_OBJC

@implementation UITitleLabel

@synthesize title, label, ratio;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    NNTUILabel *lbl = nil;
    
    lbl = [[NNTUILabel alloc] initWithZero];
    self.title = lbl;
    [lbl release];
    
    lbl = [[NNTUILabel alloc] initWithZero];
    self.label = lbl;
    [lbl release];

    ratio = .5f;
    
    return self;
}

- (void)dealloc {
    zero_release(title);
    zero_release(label);
    
    [super dealloc];
}

- (void)setTitle:(UIView *)v {
    [title removeFromSuperview];
    [NSObject refobjSet:&title ref:v];
    [self addSubview:title];
}

- (void)setLabel:(UIView *)v {
    [label removeFromSuperview];
    [NSObject refobjSet:&label ref:v];
    [self addSubview:label];
}

- (void)layoutSubviews {
    wsi::CGRectLayoutHBox lyt(self.bounds);
    title.frame = lyt.add_fpercent(ratio);
    label.frame = lyt.fill();
}

@end

NNT_END_OBJC