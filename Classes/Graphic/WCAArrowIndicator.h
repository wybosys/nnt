
# ifndef __WSI_UIKIT_WCAARROWINDICATOR_F9B2045754BF412998B79B5961FBB10A_H_INCLUDED
# define __WSI_UIKIT_WCAARROWINDICATOR_F9B2045754BF412998B79B5961FBB10A_H_INCLUDED

# import "WCALayer.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGLineStyle);

enum {
    WCAArrowIndicatorStyle6, // like ^ on keyboard show.
};

typedef uint WCAArrowIndicatorStyle;

@interface WCAArrowIndicator : WCALayer {
    
    WCGLineStyle* lineStyle;
    WCAArrowIndicatorStyle arrowStyle;
    
}

@property (nonatomic, retain) WCGLineStyle* lineStyle;
@property (nonatomic, assign) WCAArrowIndicatorStyle arrowStyle;

@end

WSI_END_HEADER_OBJC

# endif