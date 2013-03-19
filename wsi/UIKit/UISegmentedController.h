
# ifndef __WSI_UIKIT_UISEGMENTEDCONTROLLER_7911E00418724A6B9E50DEDC0DFE3FB7_H_INCLUDED
# define __WSI_UIKIT_UISEGMENTEDCONTROLLER_7911E00418724A6B9E50DEDC0DFE3FB7_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSIUISegmentedControl);

enum {
    UISegmentedControlPositionTop,
    UISegmentedControlPositionBottom
};
typedef uint UISegmentedControlPosition;

@interface UISegmentedController : WSIUIViewController {
    
    //! attach to segmented control.
    WSIUISegmentedControl *segmentedControl;
    
    //! items, accept UIViewController.
    NSArray *itemsViewController;
    
    //! position. default is Top.
    UISegmentedControlPosition segmentedPosition;
    
    //! padding, in percent, default is 0.
    CGPadding segmentedPadding;
    
    //! frame of segmented control. use segmentedFrame instead of segmentedControl.frame;
    CGRect segmentedFrame;
}

@property (nonatomic, readonly) WSIUISegmentedControl *segmentedControl;
@property (nonatomic, readonly) NSArray *itemsViewController;
@property (nonatomic, assign)   UISegmentedControlPosition segmentedPosition;
@property (nonatomic, assign)   CGPadding segmentedPadding;
@property (nonatomic, assign)   CGRect segmentedFrame;

//! init.
- (id)initWithItems:(NSArray*)items;

@end

WSI_END_HEADER_OBJC

# endif