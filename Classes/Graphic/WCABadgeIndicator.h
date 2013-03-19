
# ifndef __NNT_UIKIT_WCABADGEINDICATOR_D0BBC7B6A6CE4CE19E7FADDA095C024C_H_INCLUDED
# define __NNT_UIKIT_WCABADGEINDICATOR_D0BBC7B6A6CE4CE19E7FADDA095C024C_H_INCLUDED

# import "WCALayer.h"
# import "WCGColor.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(WCGMutableTextStyle);
NNTDECL_EXTERN_CLASS(WCGLineStyle);

@interface WCABadgeIndicator : WCALayer {
    
    //! value.
    NSString *value;
    
    //! style.
    WCGMutableTextStyle *badgeStyle;
    
    //! badge color.
    WCGColor *badgeColor;
    
    //! line style of badge.
    WCGLineStyle *badgeLineStyle;
    
}

@property (nonatomic, copy) NSString *value;
@property (nonatomic, retain) WCGMutableTextStyle *badgeStyle;
@property (nonatomic, retain) WCGColor *badgeColor;
@property (nonatomic, retain) WCGLineStyle *badgeLineStyle;

//! init.
- (id)init;
- (id)initWithLayer:(id)layer;

@end

NNT_END_HEADER_OBJC

# endif