
# import "Foundation+NNT.h"
# import "BBTabBarInternal.h"
# import "BBTabBar.h"
# import "BBTab.h"
# import "UIViewAdditions.h"

WSI_BEGIN_OBJC

CGFloat   mTabMargin       = 10.0f;
const   NSInteger kMaxBadgeNumber  = 99.0f;
static  CGFloat   kPadding         = 10.0f;

@implementation BBTabBar (BBInternal)

- (CGSize)layoutTabs {
    CGFloat x = mTabMargin;
    
    if (self.contentMode == UIViewContentModeScaleToFill) {
        CGFloat maxTextWidth = self.frame.size.width - (mTabMargin*2 + kPadding*2*_tabViews.count);
        CGFloat totalTextWidth = 0.0f;
        CGFloat totalTabWidth = mTabMargin*2;
        CGFloat maxTabWidth = 0.0f;
        for (int i = 0; i < _tabViews.count; ++i) {
            BBTab *tab = [_tabViews objectAtIndex:i];
            [tab sizeToFit];
            totalTextWidth += tab.width - kPadding*2;
            totalTabWidth  += tab.width;
            if (tab.frame.size.width > maxTabWidth) {
                maxTabWidth = tab.width;
            }
        }
        
        if (totalTextWidth > maxTextWidth) {
            CGFloat shrinkFactor = maxTextWidth/totalTextWidth;
            for (int i = 0; i < _tabViews.count; ++i) {
                BBTab *tab = [_tabViews objectAtIndex:i];
                CGFloat textWidth = tab.frame.size.width - kPadding*2;
                tab.frame = CGRectMake(x, 0, ceil(textWidth * shrinkFactor) + kPadding*2, self.height);
                x += tab.frame.size.width;
            }
        } else {
            CGFloat averageTabWidth = ceil((self.frame.size.width - mTabMargin*2)/_tabViews.count);
            if (maxTabWidth > averageTabWidth && self.width - totalTabWidth < mTabMargin) {
                for (int i = 0; i < _tabViews.count; ++i) {
                    BBTab *tab = [_tabViews objectAtIndex:i];
                    tab.frame = CGRectMake(x, 0, tab.width, self.height);
                    x += tab.frame.size.width;
                }
            } else {
                for (int i = 0; i < _tabViews.count; ++i) {
                    BBTab *tab = [_tabViews objectAtIndex:i];
                    tab.frame = CGRectMake(x, 0, averageTabWidth, self.height);
                    x += tab.frame.size.width;
                }
            }
            
        }
    } 
    
    else {
        for (int i = 0; i < _tabViews.count; ++i) {
            BBTab *tab = [_tabViews objectAtIndex:i];
            [tab sizeToFit];
            tab.frame = CGRectMake(x, 0, tab.width, self.height);
            x += tab.width + kPadding;
        }
    }
    trace_float(x);
    return CGSizeMake(x, self.height);
}

@end


WSI_END_OBJC