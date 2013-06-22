
# ifndef __NNT_UIKIT_RATINGCONTROL_A3FB31A2E91D4E48936725CF15BF459A_H_INCLUDED
# define __NNT_UIKIT_RATINGCONTROL_A3FB31A2E91D4E48936725CF15BF459A_H_INCLUDED

# import "UIControl+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface UIRatingControl : NNTUIControl {
    
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

NNT_END_HEADER_OBJC

# endif