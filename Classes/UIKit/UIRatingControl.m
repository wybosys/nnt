
# import "Core.h"
# import "UIRatingControl.h"

WSI_BEGIN_OBJC

@implementation UIRatingControl

@synthesize img_take, img_empty;
@synthesize maxValue, currentValue;
@synthesize starSize;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    self.starSize = CGSizeZero;
    
    return self;
}

- (void)dealloc {
    zero_release(img_take);
    zero_release(img_empty);
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    CGSize sz_item = CGSizeEqualToSize(starSize, CGSizeZero) ? CGSizeMake(rect.size.height, rect.size.height) : starSize;
    CGRect rc_item = CGRectMakeSz(sz_item);
    CGRect rc_take = CGRectMoveCenter(CGRectMakeSz(img_take.size), CGRectCenterPoint(&rc_item));
    CGRect rc_empty = CGRectMoveCenter(CGRectMakeSz(img_empty.size), CGRectCenterPoint(&rc_item)); 
    
    // draw star.
    for (uindex i = 0; i < currentValue; ++i) {
        [img_take drawInRect:rc_take];
        rc_take.origin.x += rc_item.size.width;
    }
    
    rc_empty.origin = rc_take.origin;
    
    // draw empty.
    for (uindex i = currentValue; i < maxValue; ++i) {
        [img_empty drawInRect:rc_empty];
        rc_empty.origin.x += rc_item.size.width;
    }
}

@end

WSI_END_OBJC