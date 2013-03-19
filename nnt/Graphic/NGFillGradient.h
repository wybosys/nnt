
# ifndef __NNT_NNTCG__NgFILLGRADIENT_5FB2F5007125437094044011B4C93538_H_INCLUDED
# define __NNT_NNTCG__NgFILLGRADIENT_5FB2F5007125437094044011B4C93538_H_INCLUDED

# import "NGFill.h"

NNT_BEGIN_HEADER_OBJC

@class NgGradient;

@interface NgFillGradient : NgFill <NSCopying, NSCoding> {
@protected
	NgGradient *_fillGradient;
}

/// @name Initialization
/// @{
-(id)initWithGradient:(NgGradient *)aGradient;
///	@}

/// @name Drawing
/// @{
-(void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
-(void)fillPathInContext:(CGContextRef)theContext;
///	@}

@end

NNT_END_HEADER_OBJC

# endif