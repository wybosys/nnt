
# ifndef __WSI_WSICG__WCGFILLIMAGE_CED678830BD142759CAC09DDCA230874_H_INCLUDED
# define __WSI_WSICG__WCGFILLIMAGE_CED678830BD142759CAC09DDCA230874_H_INCLUDED

# import "WCGFill.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGImage);

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

WSI_END_HEADER_OBJC

# endif
