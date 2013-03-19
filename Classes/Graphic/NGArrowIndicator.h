
# ifndef __NNT_UIKIT_WCAARROWINDICATOR_F9B2045754BF412998B79B5961FBB10A_H_INCLUDED
# define __NNT_UIKIT_WCAARROWINDICATOR_F9B2045754BF412998B79B5961FBB10A_H_INCLUDED

# import "WCALayer.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgLineStyle);

enum {
    WCAArrowIndicatorStyle6, // like ^ on keyboard show.
};

typedef uint WCAArrowIndicatorStyle;

@interface WCAArrowIndicator : WCALayer {
    
    NgLineStyle* lineStyle;
    WCAArrowIndicatorStyle arrowStyle;
    
}

@property (nonatomic, retain) NgLineStyle* lineStyle;
@property (nonatomic, assign) WCAArrowIndicatorStyle arrowStyle;

@end

NNT_END_HEADER_OBJC

# endif