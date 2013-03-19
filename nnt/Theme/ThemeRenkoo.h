
# ifndef __WSI_THEME_RENKOO_3C1EFEF102774E178F46D87C70CFD36A_H_INCLUDED
# define __WSI_THEME_RENKOO_3C1EFEF102774E178F46D87C70CFD36A_H_INCLUDED

# import "WCALayerTheme.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGFill);

@interface ThemeRenkoo : WCALayerTheme <WCALayerTheme> {
    WCGFill *img_indicator, *img_background;
}

@property (nonatomic, assign) CGColorRef borderColor;

//! init with color pattele.
- (id)initWith:(byte const*[2])data len:(usize const [2])len;

@end

@interface ThemeRenkooGreen : ThemeRenkoo

@end

WSI_END_HEADER_OBJC

# endif