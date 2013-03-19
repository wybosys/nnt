
# ifndef __NNT_UIKIT_WCAARROWINDICATOR_F9B2045754BF412998B79B5961FBB10A_H_INCLUDED
# define __NNT_UIKIT_WCAARROWINDICATOR_F9B2045754BF412998B79B5961FBB10A_H_INCLUDED

# import "NGLayer.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgLineStyle);

enum {
    NgArrowIndicatorStyle6, // like ^ on keyboard show.
};

typedef uint NgArrowIndicatorStyle;

@interface NgArrowIndicator : NgLayer {
    
    NgLineStyle* lineStyle;
    NgArrowIndicatorStyle arrowStyle;
    
}

@property (nonatomic, retain) NgLineStyle* lineStyle;
@property (nonatomic, assign) NgArrowIndicatorStyle arrowStyle;

@end

NNT_END_HEADER_OBJC

# endif