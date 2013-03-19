
# ifndef __NNT_UIKIT_COREPLOT_COLOR_1F14007E6F1445FC95CDCA798C3CD95F_H_INCLUDED
# define __NNT_UIKIT_COREPLOT_COLOR_1F14007E6F1445FC95CDCA798C3CD95F_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface CPColor (NNT)

+ (CPColor*)colorWithARGB:(int)__value;
+ (CPColor*)colorWithRGBA:(int)__value;
+ (CPColor*)colorWithRGB:(int)__value;

+ (CPColor*)multiWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (CPColor*)multiWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;
+ (CPColor*)addWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (CPColor*)addWith:(CPColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

@end

typedef CPColor UICPColor;

NNTDECL_CATEGORY(CPColor, NNT);

NNT_END_HEADER_OBJC

# endif