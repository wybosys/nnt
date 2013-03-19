
# ifndef __WSI_CG_WCGColor_F419DB7711034C0A94F59EFAFEFE825C_H_INCLUDED
# define __WSI_CG_WCGColor_F419DB7711034C0A94F59EFAFEFE825C_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WCGColor : NSObject <NSCopying, NSCoding> {
@private
    CGColorRef cgColor;
}

@property (nonatomic, assign) CGColorRef cgColor;

/// @name Factory Methods
/// @{
+ (WCGColor *)clearColor;
+ (WCGColor *)whiteColor;
+ (WCGColor *)lightGrayColor;
+ (WCGColor *)grayColor;
+ (WCGColor *)darkGrayColor;
+ (WCGColor *)blackColor;
+ (WCGColor *)redColor;
+ (WCGColor *)greenColor;
+ (WCGColor *)blueColor;
+ (WCGColor *)cyanColor;
+ (WCGColor *)yellowColor;
+ (WCGColor *)magentaColor;
+ (WCGColor *)orangeColor;
+ (WCGColor *)purpleColor;
+ (WCGColor *)brownColor;

+ (WCGColor *)colorWithCGColor:(CGColorRef)newCgColor;
+ (WCGColor *)colorWithComponentRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;
+ (WCGColor *)colorWithGenericGray:(CGFloat)gray;
///	@}

/// @name Initialization
/// @{
- (id)initWithCGColor:(CGColorRef)cgColor;
- (id)initWithComponentRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;

- (WCGColor *)colorWithAlphaComponent:(CGFloat)alpha;
///	@}

+ (WCGColor*)colorWithARGB:(int)__value;
+ (WCGColor*)colorWithRGBA:(int)__value;
+ (WCGColor*)colorWithRGB:(int)__value;

- (id)initWithARGB:(int)__value;
- (id)initWithRGBA:(int)__value;
- (id)initWithRGB:(int)__value;

@end

@interface WCGColor (add)

//! multi.
+ (WCGColor*)multiWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (WCGColor*)multiWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! add.
+ (WCGColor*)addWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b;
+ (WCGColor*)addWith:(WCGColor*)color r:(float)__r g:(float)__g b:(float)__b a:(float)__a;

//! color with multi.
- (WCGColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b;
- (WCGColor*)colorByMulti:(float)__r g:(float)__g b:(float)__b a:(float)__a;

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

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cg)

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
: public ns::Object<WCGColor>
{
    typedef Color self_type;
    typedef ns::Object<WCGColor> super;
    
public:
    
    typedef Color color_type;
    
    Color()
    : super(nil)
    {
        _self = [[WCGColor alloc] initWithRGBA:0x000000FF];
    }
    
    Color(uint rgba)
    : super(nil)
    {
        _self = [[WCGColor alloc] initWithRGBA:rgba];
    }
    
    Color(real r, real g, real b, real a = 1.f)
    : super(nil)
    {
        _self = [[WCGColor alloc] initWithComponentRed:r green:g blue:b alpha:a];
    }
    
    Color(real rgba[4])
    : super(nil)
    {
        _self = [[WCGColor alloc] initWithComponentRed:rgba[0] green:rgba[1] blue:rgba[2] alpha:rgba[3]];        
    }
    
    Color(int r, int g, int b, int a = 0xFF)
    : super(nil)
    {
        _self = [[WCGColor alloc] initWithComponentRed:AS_C32P(r) green:AS_C32P(g) blue:AS_C32P(b) alpha:AS_C32P(a)];
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
            _self = [[WCGColor alloc] initWithCGColor:color];
    }
    
    Color(WCGColor* color)
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
        static Color __gs_color((WCGColor*)nil);
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
    
    void _set(WCGColor* color)
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif