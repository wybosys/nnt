
# ifndef __NNT_NNTCG__WCGFILLIMAGE_CED678830BD142759CAC09DDCA230874_H_INCLUDED
# define __NNT_NNTCG__WCGFILLIMAGE_CED678830BD142759CAC09DDCA230874_H_INCLUDED

# import "WCGFill.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(WCGImage);

@interface WCGFillImage : WCGFill <NSCopying, NSCoding> {
    
@protected
	WCGImage *_fillImage;
    
}

@property (nonatomic, readonly) WCGImage* image;

- (id)initWithImage:(WCGImage *)anImage;

- (void)fillRect:(CGRect)theRect inContext:(CGContextRef)theContext;
- (void)fillPathInContext:(CGContextRef)theContext;
- (void)fillPathInContext:(CGContextRef)theContext inRect:(CGRect)theRect;

@end

NNT_END_HEADER_OBJC

# endif
