
# ifndef __NNT_UIKIT_UISEGMENTEDCONTROLLER_7911E00418724A6B9E50DEDC0DFE3FB7_H_INCLUDED
# define __NNT_UIKIT_UISEGMENTEDCONTROLLER_7911E00418724A6B9E50DEDC0DFE3FB7_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTUISegmentedControl);

enum {
    UISegmentedControlPositionTop,
    UISegmentedControlPositionBottom
};
typedef uint UISegmentedControlPosition;

@interface UISegmentedController : NNTUIViewController {
    
    //! attach to segmented control.
    NNTUISegmentedControl *segmentedControl;
    
    //! items, accept UIViewController.
    NSArray *itemsViewController;
    
    //! position. default is Top.
    UISegmentedControlPosition segmentedPosition;
    
    //! padding, in percent, default is 0.
    CGPadding segmentedPadding;
    
    //! frame of segmented control. use segmentedFrame instead of segmentedControl.frame;
    CGRect segmentedFrame;
}

@property (nonatomic, readonly) NNTUISegmentedControl *segmentedControl;
@property (nonatomic, readonly) NSArray *itemsViewController;
@property (nonatomic, assign)   UISegmentedControlPosition segmentedPosition;
@property (nonatomic, assign)   CGPadding segmentedPadding;
@property (nonatomic, assign)   CGRect segmentedFrame;

//! init.
- (id)initWithItems:(NSArray*)items;

@end

NNT_END_HEADER_OBJC

# endif