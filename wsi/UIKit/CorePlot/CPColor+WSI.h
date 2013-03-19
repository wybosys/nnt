
# ifndef __WSI_UIKIT_COREPLOT_COLOR_1F14007E6F1445FC95CDCA798C3CD95F_H_INCLUDED
# define __WSI_UIKIT_COREPLOT_COLOR_1F14007E6F1445FC95CDCA798C3CD95F_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface CPColor (WSI)

+ (CPColor*)colorWithARGB:(int)__value;
+ (CPColor*)colorWithRGBA:(int)__value;
+ (CPColor*)colorWithRGB:(int)__value;

+ (CPColor*)multiWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (CPColor*)multiWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;
+ (CPColor*)addWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (CPColor*)addWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

@end

typedef CPColor UICPColor;

WSIDECL_CATEGORY(CPColor, WSI);

WSI_END_HEADER_OBJC

# endif