
# ifndef __WSI_WCG_WCGCONTEXT_B3F232B614E44352AC92986AFFC8F942_H_INCLUDED
# define __WSI_WCG_WCGCONTEXT_B3F232B614E44352AC92986AFFC8F942_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGTextStyle);

//! add text at point with textstyle.
WSI_EXTERN void CGContextAddTextAtPoint(CGContextRef context, CGPoint pt, NSString *str, WCGTextStyle *ts);

//! add text in rect with textstyle.
WSI_EXTERN void CGContextAddTextInRect(CGContextRef context, CGRect rc, NSString *str, WCGTextStyle *ts);

//! add bounds rect.
WSI_EXTERN void CGContextAddBoundsRect(CGContextRef ctx, CGRect rect, CGFloat radius, BOOL lt, BOOL rt, BOOL lb, BOOL rb);

//! add bounds path.
WSI_EXTERN void CGPathAddBoundsRect(CGMutablePathRef path, CGRect rect, CGFloat radius, BOOL lt, BOOL rt, BOOL lb, BOOL rb);

//! draw shadow line.
WSI_EXTERN void CGContextDrawShadowLine(CGContextRef ctx, CGPoint pt0, CGPoint pt1, CGColorRef color, CGFloat len, CGSize offset);

//! draw image in rect.
WSI_EXTERN void CGContextDrawImageOri(CGContextRef c, CGRect rect, CGImageRef image);

//! fill mask of image with color.
WSI_EXTERN void CGContextFillImageMask(CGContextRef c, CGRect rect, CGImageRef image, CGColorRef color);

//! begin bitmap context.
WSI_EXTERN void WCGBeginImageContext(CGSize);
WSI_EXTERN void WCGEndImageContext(void);

//! get current context.
WSI_EXTERN CGContextRef WCGGetCurrentContext(void);

//! get current image.
WSI_EXTERN MAC_IOS_SELECT(NSImage, UIImage)* WCGGetImageFromCurrentImageContext(void);

WSI_END_HEADER_OBJC

# endif