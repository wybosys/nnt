
# import "WSIFoundation.h"
# import "BBLayouts.h"

WSI_BEGIN_OBJC

@implementation BBGridLayout

@synthesize columnCount = _columnCount;
@synthesize padding     = _padding;
@synthesize spacing     = _spacing;


- (id)init {
    self = [super init];
    if (self) {
        _columnCount = 1;
    }
    return self;
}

- (CGSize)layoutSubviews:(NSArray *)subviews forView:(UIView *)view{
    CGFloat  innerWidth = (view.frame.size.width - _padding*2);
    CGFloat  width = ceil(innerWidth / _columnCount);
    CGFloat  rowHeight = 0.0f;
    
    CGFloat x = _padding, y = _padding;
    CGFloat maxX = 0.0f, lastHeight = 0.f;
    NSInteger column = 0;
    for (UIView *subview in subviews) {
        if (column % _columnCount == 0) {
            x = _padding;
            y += rowHeight + _spacing;
        }
        CGSize size = [subview sizeThatFits:CGSizeMake(width, 0)];
        rowHeight = size.height;
        subview.frame = CGRectMake(x, y, width, size.height);
        x += subview.frame.size.width + _spacing;
        if (x > maxX) {
            maxX = x;
        }
        lastHeight = subview.frame.size.height;
        ++column;
    }
    return CGSizeMake(maxX + _padding, y + lastHeight + _padding);
}

@end



@implementation BBFlowLayout

@synthesize padding = _padding;
@synthesize spacing = _spacing;


- (CGSize)layoutSubviews:(NSArray *)subviews forView:(UIView *)view {
    CGFloat x = _padding, y = _padding;
    CGFloat maxX = 0.0f, rowHeight = 0.0f;
    CGFloat maxWidth = view.frame.size.width - _padding*2;
    for (UIView *subview in subviews) {
        if (x > _padding && x + subview.frame.size.width > maxWidth) {
            x = _padding;
            y += rowHeight + _spacing;
        }
        subview.frame = CGRectMake(x, y, subview.frame.size.width, subview.frame.size.height);
        x += subview.frame.size.width + _spacing;
        if (x > maxX) {
            maxX = x;
        }
        if (subview.frame.size.height > rowHeight) {
            rowHeight = subview.frame.size.height;
        }
    }
    return CGSizeMake(maxX + _padding, y + rowHeight + _padding);
}

@end

WSI_END_OBJC





















































