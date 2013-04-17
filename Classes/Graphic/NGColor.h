
# ifndef __NNT_CG_NgColor_F419DB7711034C0A94F59EFAFEFE825C_H_INCLUDED
# define __NNT_CG_NgColor_F419DB7711034C0A94F59EFAFEFE825C_H_INCLUDED

# import "NGBase.h"

NNT_BEGIN_HEADER_OBJC

@interface NgColor : NSObject <NSCopying, NSCoding> {
@private
    CGColorRef cgColor;
}

@property (nonatomic, assign) CGColorRef cgColor;

/// @name Factory Methods
/// @{
+ (NgColor *)clearColor;
+ (NgColor *)whiteColor;
+ (NgColor *)lightGrayColor;
+ (NgColor *)grayColor;
+ (NgColor *)darkGrayColor;
+ (NgColor *)blackColor;
+ (NgColor *)redColor;
+ (NgColor *)greenColor;
+ (NgColor *)blueColor;
+ (NgColor *)cyanColor;
+ (NgColor *)yellowColor;
+ (NgColor *)magentaColor;
+ (NgColor *)orangeColor;
+ (NgColor *)purpleColor;
+ (NgColor *)brownColor;

+ (NgColor *)colorWithCGColor:(CGColorRef)newCgColor;
+ (NgColor *)colorWithComponentRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;
+ (NgColor *)colorWithGenericGray:(CGFloat)gray;
///	@}

/// @name Initialization
/// @{
- (id)initWithCGColor:(CGColorRef)cgColor;
- (id)initWithComponentRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;

- (NgColor *)colorWithAlphaComponent:(CGFloat)alpha;
///	@}

+ (NgColor*)colorWithARGB:(int)__value;
+ (NgColor*)colorWithRGBA:(int)__value;
+ (NgColor*)colorWithRGB:(int)__value;

- (id)initWithARGB:(int)__value;
- (id)initWithRGBA:(int)__value;
- (id)initWithRGB:(int)__value;

@end

@interface NgColor (add)

//! multi.
+ (NgColor*)multiWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (NgColor*)multiWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! add.
+ (NgColor*)addWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (NgColor*)addWith:(NgColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! color with multi.
- (NgColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b;
- (NgColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! get dword value from color.
- (uint)valueRGBA;
- (uint)valueARGB;
- (uint)valueRGB;

//! component.
- (CGFloat)redComponent;
- (CGFloat)greenComponent;
- (CGFloat)blueComponent;
- (CGFloat)alphaComponent;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

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
: public ns::Object<NgColor>
{
    typedef Color self_type;
    typedef ns::Object<NgColor> super;
    
public:
    
    typedef Color color_type;
    
    Color()
    : super(nil)
    {
        _self = [[NgColor alloc] initWithRGBA:0x000000FF];
    }
    
    Color(uint rgba)
    : super(nil)
    {
        _self = [[NgColor alloc] initWithRGBA:rgba];
    }
    
    Color(real r, real g, real b, real a = 1.f)
    : super(nil)
    {
        _self = [[NgColor alloc] initWithComponentRed:r green:g blue:b alpha:a];
    }
    
    Color(real rgba[4])
    : super(nil)
    {
        _self = [[NgColor alloc] initWithComponentRed:rgba[0] green:rgba[1] blue:rgba[2] alpha:rgba[3]];        
    }
    
    Color(int r, int g, int b, int a = 0xFF)
    : super(nil)
    {
        _self = [[NgColor alloc] initWithComponentRed:AS_C32P(r) green:AS_C32P(g) blue:AS_C32P(b) alpha:AS_C32P(a)];
    }
    
    Color(self_type const& r)
    : super(r)
    {
        PASS;
    }    
    
    Color(CGColorRef color)
    : super(nil)
    {
        if (color)
            _self = [[NgColor alloc] initWithCGColor:color];
    }
    
    Color(NgColor* color)
    : super(color)
    {
        PASS;
    }
    
    Color& operator *= (real v)
    {
        objc_type* color = [_self colorByMulti:v g:v b:v];
        _set(color);
        return *this;
    }
    
    Color operator * (real v) const
    {
        return [_self colorByMulti:v g:v b:v];
    }
    
    Color& multi(real r, real g, real b, real a)
    {
        objc_type* color = [_self colorByMulti:r g:g b:b a:a];
        _set(color);
        return *this;
    }
    
    Color multi(real r, real g, real b, real a) const
    {
        return [_self colorByMulti:r g:g b:b a:a];
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
    
    ~Color()
    {
        PASS;
    }
    
    bool is_null() const
    {
        return _self == nil || _self.cgColor == nil;
    }
    
    uint rgba() const
    {
        return [_self valueRGBA];
    }
    
    uint argb() const
    {
        return [_self valueARGB];
    }
        
    operator CGColorRef () const
    {
        return _self.cgColor;
    }
    
    self_type& operator = (self_type const& r)
    {
        _set(r);
        return *this;
    }
    
    static Color const& Null()
    {
        static Color __gs_color((NgColor*)nil);
        return __gs_color;
    }
    
    static Color const& Gray()
    {
        static Color __gs_color(.5f, .5f, .5f);
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
    
    void _set(NgColor* color)
    {
        _self.cgColor = color.cgColor;
    }
    
    void _set(self_type const& r)
    {
        _self.cgColor = r._self.cgColor;
    }
    
    void _set(CGColorRef color)
    {
        _self.cgColor = color;
    }
        
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif