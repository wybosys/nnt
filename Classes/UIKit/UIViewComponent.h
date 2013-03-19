
# ifndef __NNT_UIKIT_COMPONENT_1109C916E9FF4B338DB32829617256ED_H_INCLUDED
# define __NNT_UIKIT_COMPONENT_1109C916E9FF4B338DB32829617256ED_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UITitleLabel : NNTUIView

@property (nonatomic, assign) real ratio; //! default is .5f . 
@property (nonatomic, retain) UIView* title;
@property (nonatomic, retain) UIView* label;

@end

NNT_END_HEADER_OBJC

# endif