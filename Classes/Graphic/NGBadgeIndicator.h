
# ifndef __NNT_UIKIT_WCABADGEINDICATOR_D0BBC7B6A6CE4CE19E7FADDA095C024C_H_INCLUDED
# define __NNT_UIKIT_WCABADGEINDICATOR_D0BBC7B6A6CE4CE19E7FADDA095C024C_H_INCLUDED

# import "WCALayer.h"
# import "NGColor.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgMutableTextStyle);
NNTDECL_EXTERN_CLASS(NgLineStyle);

@interface WCABadgeIndicator : WCALayer {
    
    //! value.
    NSString *value;
    
    //! style.
    NgMutableTextStyle *badgeStyle;
    
    //! badge color.
    NgColor *badgeColor;
    
    //! line style of badge.
    NgLineStyle *badgeLineStyle;
    
}

@property (nonatomic, copy) NSString *value;
@property (nonatomic, retain) NgMutableTextStyle *badgeStyle;
@property (nonatomic, retain) NgColor *badgeColor;
@property (nonatomic, retain) NgLineStyle *badgeLineStyle;

//! init.
- (id)init;
- (id)initWithLayer:(id)layer;

@end

NNT_END_HEADER_OBJC

# endif