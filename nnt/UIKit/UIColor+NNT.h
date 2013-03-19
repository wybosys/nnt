
# ifndef __NNT_UIKIT_UICOLOR_EA856FD3AFCC4F64A38D8C489AD70BC6_H_INCLUDED
# define __NNT_UIKIT_UICOLOR_EA856FD3AFCC4F64A38D8C489AD70BC6_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UIColor (NNT)

- (id)initWithRGBA:(int)val;
- (id)initWithARGB:(int)val;
- (id)initWithRGB:(int)val;

//! color with dword value.
+ (UIColor*)colorWithRGBA:(int)__value;
+ (UIColor*)colorWithARGB:(int)__value;
+ (UIColor*)colorWithRGB:(int)__value;

//! multi.
+ (UIColor*)multiWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (UIColor*)multiWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! add.
+ (UIColor*)addWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (UIColor*)addWith:(UIColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! color with multi.
- (UIColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b;
- (UIColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! get dword value from color.
- (uint)valueRGBA;
- (uint)valueARGB;
- (uint)valueRGB;

@end

NNTDECL_CATEGORY(UIColor, NNT);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "UIImage+NNT.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

# ifdef RGB
#   undef RGB
# endif

# ifdef RGBA
#   undef RGBA
# endif

# ifdef ARGB
#   undef ARGB
# endif

class Color
{
    
    typedef Color self_type;
    
public:
    
    typedef Color color_type;
    
    Color()
    {
        _color = [[UIColor alloc] initWithRGBA:0x000000FF];
    }
    
    Color(uint rgba)
    {
        _color = [[UIColor alloc] initWithRGBA:rgba];
    }
    
    Color(real r, real g, real b, real a = 1.f)
    {
        _color = [[UIColor alloc] initWithRed:r green:g blue:b alpha:a];
    }
    
    Color(int r, int g, int b, int a = 0xFF)
    {
        _color = [[UIColor alloc] initWithRed:AS_C32P(r) green:AS_C32P(g) blue:AS_C32P(b) alpha:AS_C32P(a)];
    }
    
    static Color RGB(int r, int g, int b)
    {
        return Color(r, g, b, 0xFF);
    }
    
    static Color RGB(int val)
    {
        return Color(RGB_RED(val), RGB_GREEN(val), RGB_BLUE(val), 0xFF);
    }
    
    static Color RGBA(int r, int g, int b, int a)
    {
        return Color(r, g, b, a);
    }
    
    static Color RGBA(int val)
    {
        return Color(RGBA_RED(val), RGBA_GREEN(val), RGBA_BLUE(val), RGBA_ALPHA(val));
    }
    
    static Color ARGB(int a, int r, int g, int b)
    {
        return Color(r, g, b, a);
    }
    
    static Color ARGB(int val)
    {
        return Color(ARGB_RED(val), ARGB_GREEN(val), ARGB_BLUE(val), ARGB_ALPHA(val));
    }
    
    Color(self_type const& r)
    {
        _color = [r._color retain];
    }
    
    Color(Image const& img)
    {
        _color = [[UIColor alloc] initWithPatternImage:img];
    }
    
    Color(UIColor* color)
    {
        _color = [color retain];
    }
    
    Color(CGColorRef color)
    {
        _color = [[UIColor alloc] initWithCGColor:color];
    }
    
    ~Color()
    {
        safe_release(_color);
    }
    
    uint rgba() const
    {
        return [_color valueRGBA];
    }
    
    uint argb() const
    {
        return [_color valueARGB];
    }
    
    operator UIColor* () const
    {
        return (UIColor*)_color;
    }
    
    UIColor* operator () () const
    {
        return (UIColor*)_color;
    }
    
    UIColor* operator * () const
    {
        return (UIColor*)_color;
    }
    
    UIColor* self() const
    {
        return (UIColor*)_color;
    }
    
    operator CGColorRef () const
    {
        return (CGColorRef)_color.CGColor;
    }
    
    self_type& operator = (self_type const& r)
    {
        [_color release];
        _color = [r._color retain];
        return *this;
    }
    
    static Color const& Null()
    {
        static Color __gs_color((UIColor*)nil);
        return __gs_color;
    }
    
    static Color const& Gray()
    {
        static Color __gs_color(.5f, .5f, .5f);
        return __gs_color;
    }
    
    static Color const& LightGray()
    {
        static Color __gs_color(.8f, .8f, .8f);
        return __gs_color;
    }
    
    static Color const& Red()
    {
        static Color __gs_color(1.f, 0.f, 0.f);
        return __gs_color;
    }
    
    static Color const& Green()
    {
        static Color __gs_color(0.f, 1.f, 0.f);
        return __gs_color;
    }
    
    static Color const& Blue()
    {
        static Color __gs_color(0.f, 0.f, 1.f);
        return __gs_color;
    }
    
    static Color const& Clear()
    {
        static Color __gs_color(0.f, 0.f, 0.f, 0.f);
        return __gs_color;
    }
    
    static Color const& Black()
    {
        static Color __gs_color(0.f, 0.f, 0.f);
        return __gs_color;
    }
    
    static Color const& Orange()
    {
        static Color __gs_color(1.f, 0.5f, 0.f);
        return __gs_color;
    }
    
    static Color const& White()
    {
        static Color __gs_color(1.f, 1.f, 1.f);
        return __gs_color;
    }
    
protected:
    
    UIColor* _color;
    
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif