
# ifndef __WSI_UIKIT_COMPONENT_1109C916E9FF4B338DB32829617256ED_H_INCLUDED
# define __WSI_UIKIT_COMPONENT_1109C916E9FF4B338DB32829617256ED_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UITitleLabel : WSIUIView

@property (nonatomic, assign) real ratio; //! default is .5f . 
@property (nonatomic, retain) UIView* title;
@property (nonatomic, retain) UIView* label;

@end

WSI_END_HEADER_OBJC

# endif