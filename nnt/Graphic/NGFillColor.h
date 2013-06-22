
# ifndef __NNT_NNTCG__NgFILLCOLOR_FA6304E3B4AE4133BA43652813EE6A32_H_INCLUDED
# define __NNT_NNTCG__NgFILLCOLOR_FA6304E3B4AE4133BA43652813EE6A32_H_INCLUDED

# import "NGFill.h"

NNT_BEGIN_HEADER_OBJC

@interface NgFillColor : NgFill <NSCopying, NSCoding> {
    @protected
	NgColor *_fillColor;
}

/// @name Initialization
/// @{
-(id)initWithColor:(NgColor *)aCcolor;
///	@}

/// @name Drawing
/// @{
-(void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
-(void)fillPathInContext:(CGContextRef)theContext;
///	@}

@end

NNT_END_HEADER_OBJC

# endif