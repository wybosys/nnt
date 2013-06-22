
# ifndef __NNT_NNTCG__NgFILLIMAGE_CED678830BD142759CAC09DDCA230874_H_INCLUDED
# define __NNT_NNTCG__NgFILLIMAGE_CED678830BD142759CAC09DDCA230874_H_INCLUDED

# import "NGFill.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgImage);

@interface NgFillImage : NgFill <NSCopying, NSCoding> {
    
@protected
	NgImage *_fillImage;
    
}

@property (nonatomic, readonly) NgImage* image;

- (id)initWithImage:(NgImage *)anImage;

- (void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
- (void)fillPathInContext:(CGContextRef)theContext;
- (void)fillPathInContext:(CGContextRef)theContext inRect:(CGRect)theRect;

@end

NNT_END_HEADER_OBJC

# endif
