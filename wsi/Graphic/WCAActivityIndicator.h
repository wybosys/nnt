
# ifndef __WSI_UIKIT_WCACITVITYINDICATOR_207EF731080546E1973968018B1A9CF5_H_INCLUDED
# define __WSI_UIKIT_WCACITVITYINDICATOR_207EF731080546E1973968018B1A9CF5_H_INCLUDED

# import "WCALayer.h"
# import "WCGColor.h"

WSI_BEGIN_HEADER_OBJC

@interface WCAActivityIndicator : WCALayer {
    //! start angle, in rad, default is 0, cw.
    real startAngle;
    
    //! end angle, in rad, default is 0, cw.
    real endAngle;
    
    //! ring width. default 10 on ipad, 5 on iphone.
    real ringWidth;
    
    //! ring color. default is white.
    WCGColor* ringColor;
    
    //! ring pattern.
    //NSArray* ringPattern;
    
    //! offset angle. default is -M_PI_2.
    real offsetAngle;
}

@property (nonatomic, assign) real startAngle, endAngle, offsetAngle;
@property (nonatomic, assign) real ringWidth;
//@property (nonatomic, assign) NSArray* ringPattern;
@property (nonatomic, retain) WCGColor *ringColor;

@end

WSI_END_HEADER_OBJC

# endif