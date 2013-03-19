
# ifndef __WSI_UIKIT_RATINGCONTROL_A3FB31A2E91D4E48936725CF15BF459A_H_INCLUDED
# define __WSI_UIKIT_RATINGCONTROL_A3FB31A2E91D4E48936725CF15BF459A_H_INCLUDED

# import "UIControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface UIRatingControl : WSIUIControl {
    
    //! image for star.
    UIImage* img_take;
    UIImage* img_empty;
    
    //! max value.
    uint maxValue;
    
    //! current value.
    uint currentValue;
    
    //! star size.
    CGSize starSize;
}

@property (nonatomic, retain) UIImage *img_take, *img_empty;
@property (nonatomic, assign) uint maxValue, currentValue;
@property (nonatomic, assign) CGSize starSize;

@end

WSI_END_HEADER_OBJC

# endif