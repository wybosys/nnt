
# import "Core.h"
# import "UIFlowView.h"

NNT_BEGIN_OBJC

@interface UIFlowView ()

- (void)__init;

//! update layout.
- (void)_updateLayout;

@end

@implementation UIFlowView

@synthesize margin;

- (void)__init {
    margin = CGMarginZero;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self __init];
    return self;
}

- (NSArray*)viewsForFlow {
    return self.subviews;
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    [self _updateLayout];
}

- (void)addSubview:(UIView *)view {
    [super addSubview:view];
    //[self _updateLayout];
}

- (void)updateLayout {
    [self _updateLayout];
}

- (void)_updateLayout {
    CGRect rc_client = self.rectForLayout;
    CGPoint pt_cur = rc_client.origin;
    real row_height = 0;
    real row_width = rc_client.size.width;
    real sum_widht = row_width;
    real sum_height = row_height;
    
    pt_cur.y += margin.top;
    for (UIView* each in [self viewsForFlow]) {
        CGRect rc_each = each.frame;
        
        pt_cur.x += margin.left;
        
        if ((pt_cur.x + rc_each.size.width + margin.right ) > row_width) {
            sum_height += row_height + margin.top;
            pt_cur.y += row_height + margin.top;
            row_height = margin.top + rc_each.size.height + margin.bottom;
            pt_cur.x = margin.left;
        } else {
            row_height = MAX(row_height, (margin.top + rc_each.size.height + margin.bottom));
        }
        
        rc_each.origin = pt_cur;
        each.frame = rc_each;
        
        pt_cur.x += rc_each.size.width + margin.right;
    }
    
    sum_height += row_height;
    
    self.contentSize = CGSizeMake(sum_widht, sum_height);
}

@end

NNT_END_OBJC