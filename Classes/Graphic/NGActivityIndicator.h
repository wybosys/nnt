
# ifndef __NNT_UIKIT_WCACITVITYINDICATOR_207EF731080546E1973968018B1A9CF5_H_INCLUDED
# define __NNT_UIKIT_WCACITVITYINDICATOR_207EF731080546E1973968018B1A9CF5_H_INCLUDED

# import "WCALayer.h"
# import "NGColor.h"

NNT_BEGIN_HEADER_OBJC

@interface WCAActivityIndicator : WCALayer {
    //! start angle, in rad, default is 0, cw.
    real startAngle;
    
    //! end angle, in rad, default is 0, cw.
    real endAngle;
    
    //! ring width. default 10 on ipad, 5 on iphone.
    real ringWidth;
    
    //! ring color. default is white.
    NgColor* ringColor;
    
    //! ring pattern.
    //NSArray* ringPattern;
    
    //! offset angle. default is -M_PI_2.
    real offsetAngle;
}

@property (nonatomic, assign) real startAngle, endAngle, offsetAngle;
@property (nonatomic, assign) real ringWidth;
//@property (nonatomic, assign) NSArray* ringPattern;
@property (nonatomic, retain) NgColor *ringColor;

@end

NNT_END_HEADER_OBJC

# endif