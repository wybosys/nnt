
# ifndef __NNT_UIKIT_UIDIALNAVIGATIONVIEW_7CD2D29C8CCD4540A11D6BDDAA26E7E5_H_INCLUDED
# define __NNT_UIKIT_UIDIALNAVIGATIONVIEW_7CD2D29C8CCD4540A11D6BDDAA26E7E5_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

enum {
    UINavigationDialPositionCustom = 1,
    UINavigationDialPositionLeftTop,
    UINavigationDialPositionTopCenter,
    UINavigationDialPositionRightTop,
    UINavigationDialPositionLeftCenter,
    UINavigationDialPositionLeftBottom,
    UINavigationDialPositionBottomCenter,
    UINavigationDialPositionRightBottom,
    UINavigationDialPositionRightCenter,
    UINavigationDialPositionCenter
};
typedef uint UINavigationDialPosition;

NNTDECL_EXTERN_CLASS(UINavigationDial);

@interface UINavigationDialView : NNTUIView {
    
    //! content view.
    UIView *contentView;
    
    //! dial view.
    UINavigationDial *dial;
 
    //! position type, default is custom.
    UINavigationDialPosition dialPosition;
}

@property (nonatomic, assign) UIView *contentView;
@property (nonatomic, readonly) UINavigationDial *dial;
@property (nonatomic, assign) UINavigationDialPosition dialPosition;

//! set position by type.
- (void)setPositionByEnum:(UINavigationDialPosition)position;

@end

NNT_END_HEADER_OBJC

# endif