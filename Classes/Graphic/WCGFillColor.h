
# ifndef __NNT_NNTCG__WCGFILLCOLOR_FA6304E3B4AE4133BA43652813EE6A32_H_INCLUDED
# define __NNT_NNTCG__WCGFILLCOLOR_FA6304E3B4AE4133BA43652813EE6A32_H_INCLUDED

# import "WCGFill.h"

NNT_BEGIN_HEADER_OBJC

@interface WCGFillColor : WCGFill <NSCopying, NSCoding> {
    @protected
	WCGColor *_fillColor;
}

/// @name Initialization
/// @{
-(id)initWithColor:(WCGColor *)aCcolor;
///	@}

/// @name Drawing
/// @{
-(void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
-(void)fillPathInContext:(CGContextRef)theContext;
///	@}

@end

NNT_END_HEADER_OBJC

# endif