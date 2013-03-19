
# ifndef __NNT_WCG_WCGCONTEXT_B3F232B614E44352AC92986AFFC8F942_H_INCLUDED
# define __NNT_WCG_WCGCONTEXT_B3F232B614E44352AC92986AFFC8F942_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(WCGTextStyle);

//! add text at point with textstyle.
NNT_EXTERN void CGContextAddTextAtPoint(CGContextRef context, CGPoint pt, NSString *str, WCGTextStyle *ts);

//! add text in rect with textstyle.
NNT_EXTERN void CGContextAddTextInRect(CGContextRef context, CGRect rc, NSString *str, WCGTextStyle *ts);

//! add bounds rect.
NNT_EXTERN void CGContextAddBoundsRect(CGContextRef ctx, CGRect rect, CGFloat radius, BOOL lt, BOOL rt, BOOL lb, BOOL rb);

//! add bounds path.
NNT_EXTERN void CGPathAddBoundsRect(CGMutablePathRef path, CGRect rect, CGFloat radius, BOOL lt, BOOL rt, BOOL lb, BOOL rb);

//! draw shadow line.
NNT_EXTERN void CGContextDrawShadowLine(CGContextRef ctx, CGPoint pt0, CGPoint pt1, CGColorRef color, CGFloat len, CGSize offset);

//! draw image in rect.
NNT_EXTERN void CGContextDrawImageOri(CGContextRef c, CGRect rect, CGImageRef image);

//! fill mask of image with color.
NNT_EXTERN void CGContextFillImageMask(CGContextRef c, CGRect rect, CGImageRef image, CGColorRef color);

//! begin bitmap context.
NNT_EXTERN void WCGBeginImageContext(CGSize);
NNT_EXTERN void WCGEndImageContext(void);

//! get current context.
NNT_EXTERN CGContextRef WCGGetCurrentContext(void);

//! get current image.
NNT_EXTERN MAC_IOS_SELECT(NSImage, UIImage)* WCGGetImageFromCurrentImageContext(void);

NNT_END_HEADER_OBJC

# endif