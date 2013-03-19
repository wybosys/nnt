
# ifndef __BBTABGRID_19A7FD3A8B58476A9525A21D47164912_H_INCLUDED
# define __BBTABGRID_19A7FD3A8B58476A9525A21D47164912_H_INCLUDED

# import "BBTabBar.h"

WSI_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(BBTabBar);

@interface BBTabGrid : BBTabBar {

    NSInteger _columCount;
}

@property (nonatomic) NSInteger columnCount;

@end


@interface BBTabStrip : BBTabBar {

@private
    UIView         *_overLeft;
    UIView         *_overRight;
    UIScrollView   *_scrollView;
    
    BOOL           _contentSizeCached;
    CGSize         _contentSize;
}

@end

WSI_END_HEADER_OBJC

# endif