
# ifndef __WSI_WSICG__WCGFILLGRADIENT_5FB2F5007125437094044011B4C93538_H_INCLUDED
# define __WSI_WSICG__WCGFILLGRADIENT_5FB2F5007125437094044011B4C93538_H_INCLUDED

# import "WCGFill.h"

WSI_BEGIN_HEADER_OBJC

@class WCGGradient;

@interface WCGFillGradient : WCGFill <NSCopying, NSCoding> {
@protected
	WCGGradient *_fillGradient;
}

/// @name Initialization
/// @{
-(id)initWithGradient:(WCGGradient *)aGradient;
///	@}

/// @name Drawing
/// @{
-(void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
-(void)fillPathInContext:(CGContextRef)theContext;
///	@}

@end

WSI_END_HEADER_OBJC

# endif