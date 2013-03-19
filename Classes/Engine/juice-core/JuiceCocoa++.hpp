
# ifndef __JUICE_COCOA_PLUSPLUS_CAB13BF3CAA5490C8A45EAA58DBED08C_H_INCLUDED
# define __JUICE_COCOA_PLUSPLUS_CAB13BF3CAA5490C8A45EAA58DBED08C_H_INCLUDED

# import "JuiceCore.hpp"
# import "JuiceTypes.hpp"
# import "../../Graphic/WCGPath.h"
# import "../../Graphic/WCGColor.h"
# import "../../Graphic/WCGGradient.h"
# import "../../Graphic/WCGImage.h"
# import "../../Graphic/WCGTextStyle.h"
# import "../../Graphic/WCGContext.h"
# import "../../Graphic/WCGFill.h"
# import "../../Graphic/CGShadow.h"

JUICE_BEGIN 
NNT_BEGIN_NS(cocoa)

# ifdef RGB
# undef RGB
# endif

# ifdef RGBA
# undef RGBA
# endif

# ifdef ARGB
# undef ARGB
# endif

class Graphics;

using ::wsi::cg::Rect;
using ::wsi::cg::Size;
using ::wsi::cg::Point;
using ::wsi::cg::Angle;

NNTDECL_BOOLOBJECT(cw, ccw);

enum
{
    PATTERN_GRID_POINT,
};

class Color
: public ::wsi::cg::Color
{
    typedef ::wsi::cg::Color super;
    
public:       
    
    Color()
    {
        PASS;
    }
    
    Color(int r, int g, int b, int a = 255)
    : super(r, g, b, a)
    {
        PASS;
    }
    
    Color(real r, real g, real b, real a = 1.f)
    : super(r, g, b, a)
    {
        PASS;
    }
    
    Color(real rgba[4])
    : super(rgba)
    {
        PASS;
    }
    
    Color(uint rgba)
    : super(rgba)
    {
        PASS;
    }
    
    Color(CGColorRef color)
    : super(color)
    {
        PASS;
    }
    
    Color(Color const& r)
    : super(r)
    {
        PASS;
    }
    
    Color& operator = (Color const& r)
    {
        _set(r);
        return *this;
    }
    
    template <typename colorT>
    Color(colorT const& r, 
          typename colorT::color_type* = NULL)
    {
        ::wsi::ntl::const_pointer<colorT> ptr(r);
        _set((CGColorRef)(*ptr));
    }
    
    ~Color()
    {
        PASS;
    }
    
    static Color RGBA(uint val)
    {
        return Color(val);
    }
    
    static Color ARGB(uint val)
    {
        return Color((int)ARGB_RED(val), ARGB_GREEN(val), ARGB_BLUE(val), ARGB_ALPHA(val));
    }
    
    static Color RGB(uint val)
    {
        return Color((int)RGB_RED(val), RGB_GREEN(val), RGB_BLUE(val));
    }
        
    void fill(Graphics&) const;
    void stroke(Graphics&) const;
        
};

class Pen
{    
public:
    
    Pen()
    : _width(1.f)
    {
        PASS;
    }
    
    Pen(real width, Color const& color = Color::Null())
    : _width(width)
    {
        _color = color;
    }
    
    Pen(Color const& color, real width = 1.f)
    : _width(width)
    {
        _color = color;
    }
    
    Pen(Pen const& r)
    {
        _color = r._color;
        _width = r._width;
    }
    
    Pen& operator = (Pen const& r)
    {
        _color = r._color;
        _width = r._width;
        return *this;
    }
    
    void set(Graphics&) const;
    
    void set_color(Color const& r)
    {
        _color = r;
    }
    
    real width() const
    {
        return _width;
    }
    
    void set_width(real width)
    {
        _width = width;
    }
    
    void stroke(Graphics& gra, CGRect const& rc) const;
    
protected:
    
    Color _color;
    real _width;
    
};

class Gradient
: public ::wsi::cg::Gradient
{
    typedef ::wsi::cg::Gradient super;
    
public:
    
    Gradient()
    {
        PASS;
    }
    
    Gradient(Color const& begin,
             Color const& end,
             real pos_begin,
             real pos_end,
             real angle = 0)
    : super(begin, end, pos_begin, pos_end, angle)
    {
        PASS;
    }
    
};

class Image
: public ::wsi::cg::Image
{
    typedef ::wsi::cg::Image super;
    
public:
    
    Image()
    {
        PASS;
    }
    
    Image(CGImageRef img)
    : super(img)
    {
        PASS;
    }
    
    Image(Image const& r)
    : super(r)
    {
        PASS;
    }
    
    Image(::wsi::ns::String const& named)
    : super(named)
    {
        PASS;
    }
    
    template <typename imgT>
    Image(imgT const& r,
          typename imgT::image_type* = NULL)
    {
        _set(r);
    }
    
    Image& operator = (Image const& r)
    {
        _set(r);
        return *this;
    }
    
    ~Image()
    {
        PASS;
    }
    
    bool operator == (void* ptr) const
    {
        return *this == ptr;
    }
    
    void release()
    {
        _set(nil);
    }
    
    void fill(Graphics& gra, CGRect const& rc) const;
    
};

class Fill
: public ::wsi::cg::Fill
{
    typedef ::wsi::cg::Fill super;
    
public:
    
    Fill()
    {
        PASS;
    }
    
    Fill(WCGFill* r)
    : super(r)
    {
        PASS;
    }
    
    Fill(Color const& color)
    : super(color)
    {
        PASS;
    }
    
    Fill(Gradient const& grad)
    : super(grad)
    {
        PASS;
    }
    
    Fill(Image const& img)
    : super(img)
    {
        PASS;
    }
    
    void fill(Graphics&) const;
    void fill(Graphics&, CGRect const&) const;
    
};

class Brush
{
public:
    
    Brush()
    : _fpattern(NULL)
    {
        PASS;
    }
    
    Brush(Color const& color)
    : _fpattern(NULL)
    {
        _color = color;
    }
    
    Brush(Brush const& r)
    {
        _color = r._color;
        _fpattern = r._fpattern;
    }
    
    Brush& operator = (Brush const& r)
    {
        _color = r._color;
        _fpattern = r._fpattern;
        return *this;
    }
        
    ~Brush()
    {
        PASS;
    }
    
    void set_color(Color const& color)
    {
        _color = color;
    }
    
    void set(Graphics&) const;
    void fill(Graphics& gra, CGRect const& rc) const;
        
protected:
    
    Color _color;
    
    typedef void (Brush::*fpattern_type)(CGContextRef) const;
    fpattern_type _fpattern;
    
};

class GradientBrush
: public Brush
{
public:
    
    GradientBrush()
    {
        PASS;
    }
    
    GradientBrush(Gradient const& br)
    : _gradient(br)
    {
        PASS;
    }
    
    void fill(Graphics& gra, CGRect const& rc) const;
    void fill_path(Graphics& gra) const;
    
protected:
    
    Gradient _gradient;
    
};

class GridPointBrush
: public Brush
{
public:
    
    GridPointBrush(Color const& color, CGSize size, real spacing)
    : Brush(color),
    _pattern(NULL)
    {
        _size = size;
        _spacing = spacing;
        this->_fpattern = (fpattern_type)&GridPointBrush::_set;
    }
    
    ~GridPointBrush()
    {
        CGPatternRelease(_pattern);
    }
    
protected:
        
    friend void drawpattern(void*, CGContextRef);
    static void drawpattern(void* info, CGContextRef ctx)
    {
        GridPointBrush* br = (GridPointBrush*)info;
        CGContextSetFillColorWithColor(ctx, br->_color);
        CGRect rc = CGRectMake(br->_spacing, br->_spacing, br->_size.width, br->_size.height);
        CGContextFillRect(ctx, rc);
    }
    
    void _set(CGContextRef ctx) const
    {
        CGPatternRelease(_pattern);
        
        CGColorSpaceRef patternSpace = CGColorSpaceCreatePattern(NULL);
        CGContextSetFillColorSpace(ctx, patternSpace);
        CGColorSpaceRelease(patternSpace);
        
        static const CGPatternCallbacks callbacks = {0, &drawpattern, NULL}; 
        _pattern = CGPatternCreate((void*)this,
                                   CGRectMake(0, 0, _size.width, _size.height),
                                   CGAffineTransformIdentity,
                                   _size.width + _spacing,
                                   _size.height + _spacing,
                                   kCGPatternTilingConstantSpacing,
                                   true,
                                   &callbacks);
        
        CGFloat alpha = 1.f;
        CGContextSetFillPattern(ctx, _pattern, &alpha);
    }
    
    CGSize _size;
    real _spacing;
    mutable CGPatternRef _pattern;
    
};

class ImageLineBrush
: public Brush
{
public:
    
    ImageLineBrush(Image const& img,
                   Color const& color,
                   CGSize size,
                   real spacing = 0)
    : Brush(color),
    _pattern(NULL),
    _image(img)
    {
        _size = size;
        _spacing = spacing;
        this->_fpattern = (fpattern_type)&ImageLineBrush::_set;
    }
    
    ImageLineBrush(Image const& img,
                   CGSize size,
                   real spacing = 0)
    : Brush(Color((CGColorRef)0)),
    _pattern(NULL),
    _image(img)
    {
        _size = size;
        _spacing = spacing;
        this->_fpattern = (fpattern_type)&ImageLineBrush::_set;        
    }
    
    ~ImageLineBrush()
    {
        CGPatternRelease(_pattern);
    }
    
    void set_size(CGSize const& size)
    {
        _size = size;
    }
    
    void set_image(Image const& img)
    {
        _image = img;
    }
    
protected:
    
    friend void drawpattern(void*, CGContextRef);
    static void drawpattern(void* info, CGContextRef ctx)
    {
        ImageLineBrush* br = (ImageLineBrush*)info;
        CGRect rc = CGRectMake(br->_spacing, br->_spacing, br->_size.width + 2, br->_size.height + 2);
                
        // draw image.
        CGContextDrawImageOri(ctx, rc, br->_image);
        
        // fill color.
        if (!br->_color.is_null())
        {
            CGContextSetBlendMode(ctx, kCGBlendModeColor);
            CGContextSetFillColorWithColor(ctx, br->_color);               
            CGContextFillRect(ctx, rc);                        
        }
    }
    
    void _set(CGContextRef ctx) const
    {
        CGPatternRelease(_pattern);
        
        CGColorSpaceRef patternSpace = CGColorSpaceCreatePattern(NULL);
        CGContextSetFillColorSpace(ctx, patternSpace);
        CGColorSpaceRelease(patternSpace);
        
        static const CGPatternCallbacks callbacks = {0, &drawpattern, NULL}; 
        _pattern = CGPatternCreate((void*)this,
                                   CGRectMake(0, 0, _size.width, _size.height),
                                   CGAffineTransformIdentity,
                                   _size.width + _spacing + 2,
                                   _size.height + _spacing + 2,
                                   kCGPatternTilingConstantSpacing,
                                   true,
                                   &callbacks);
        
        CGFloat alpha = 1.f;
        CGContextSetFillPattern(ctx, _pattern, &alpha);
    }
    
    CGSize _size;
    real _spacing;
    mutable CGPatternRef _pattern;
    Image _image;
    
};

class ImageBrush
: public Brush
{
public:
    
    ImageBrush(Image const& img)
    : _image(img)
    {
        PASS;
    }
    
    void fill(Graphics& gra, CGRect const& rc) const;
    
protected:
    
    Image _image;
    
};

class String
: public ::wsi::ns::String
{
    typedef ::wsi::ns::String super;
    
public:
    
    String()
    {
        PASS;
    }
    
    String(::wsi::ns::String const& str)
    : super(str)
    {
        PASS;
    }
    
    String(String const& r)
    : super(r)
    {
        PASS;
    }
    
    void draw(Graphics& gra, Point const&, bool adjust = true) const;
    void draw(Graphics& gra, Rect const&, bool adjust = true) const;
    
    ::wsi::cg::MutableTextStyle style;
    
};

class Matrix
: public ::wsi::cg::AffineTransform
{
    typedef ::wsi::cg::AffineTransform super;
    
public:
    
    typedef empty_axises2d_type empty_type;
    
    Matrix()
    {
        PASS;
    }    
    
    void set_rotate(real angle)
    {
        _mat = CGAffineTransformRotate(_mat, angle);
    }
    
    void set_translate(real x, real y, real = 0)
    {
        _mat = CGAffineTransformTranslate(_mat, x, y);
    }
    
    template <typename vecT>
    void set_translate(vecT const& vec)
    {
        _mat = CGAffineTransformTranslate(_mat, vec.x, vec.y);
    }
    
    void set_scale(real x, real y, real = 0)
    {
        _mat = CGAffineTransformScale(_mat, x, y);
    }
    
    void set_addscale(real x, real y, real = 0)
    {
        _mat.a += x;
        _mat.d += y;
    }
    
    static Matrix const& Identity()
    {
        static const Matrix mat;
        return mat;
    }
    
    void set_inverse()
    {
        _mat = CGAffineTransformInvert(_mat);
    }
    
    template <typename vertexT>
    vertexT operator * (vertexT const& vex) const
    {
        vertexT ret;
        ret.x = vex.x * _mat.a + vex.y * _mat.b + _mat.tx;
        ret.y = vex.x * _mat.c + vex.y * _mat.d + _mat.ty;
        return ret;
    }

    Matrix& operator *= (Matrix const& r)
    {
        _mat = CGAffineTransformConcat(_mat, r);
        return *this;
    }
    
    Matrix operator * (Matrix const& r) const
    {
        Matrix ret = *this;
        return ret *= r;
    }
    
};

class Shadow
: public ::wsi::cg::Shadow
{
    typedef ::wsi::cg::Shadow super;
    
public:
    
    Shadow()
    {
        PASS;
    }
    
    Shadow(CGShadow* r)
    : super(r)
    {
        PASS;
    }
    
    void set(Graphics&) const;

};

class Path
{
    
    typedef Path self_type;
    typedef ::wsi::cg::MutablePath super;
    
public:
    
    Path()
    {
        _path = CGPathCreateMutable();
    }
    
    Path(Path const& r)
    {
        _path = CGPathCreateMutableCopy(r._path);
    }
    
    ~Path()
    {
        if (_path)
            CGPathRelease(_path);
    }
    
    operator CGMutablePathRef () const
    {
        return (CGMutablePathRef)_path;
    }
    
    Path& operator = (Path const& r)
    {
        release();
        _path = CGPathCreateMutableCopy(r._path);
        return *this;
    }
    
    Path& operator += (Path const& r)
    {
        CGPathAddPath(_path, _transform, r._path);
        return *this;
    }
    
    void reset()
    {
        release();
        _path = CGPathCreateMutable();
        _transform.set_identity();
    }
    
    void clear()
    {
        release();
        _path = CGPathCreateMutable();
    }
    
    void release()
    {
        if (_path)
        {
            CGPathRelease(_path);
            _path = NULL;
        }
    }
    
    Matrix& tranform()
    {
        return _transform;
    }
    
    Matrix const& tranform() const
    {
        return _transform;
    }
    
    bool contain(Point const& pt) const
    {
        return CGPathContainsPoint(_path, _transform, pt, true);
    }
    
    void close()
    {
        CGPathCloseSubpath(_path);
    }
    
    template <typename pointT>
    void move_to(pointT const& pt)
    {
        CGPathMoveToPoint(_path, _transform, pt.x, pt.y);
    }
    
    template <typename pointT>
    void line_to(pointT const& pt)
    {
        CGPathAddLineToPoint(_path, _transform, pt.x, pt.y);
    }
    
    template <typename pathT>
    void add_path(pathT& ph)
    {
        CGPathAddPath(_path, _transform, ph);
    }
    
    template <typename pointsT>
    void add_lines(pointsT const& pts)
    {
        CGPoint* ppts = (CGPoint*)::wsi::core::pointer(pts);
        CGPathAddLines(_path, _transform, ppts, ::wsi::core::size(pts));
    }
    
    template <typename pointT>
    void add_arc(pointT const& pt, real radius, real start, real end, bool clockwise = true)
    {
        CGPathAddArc(_path, _transform, pt.x, pt.y, radius, start, end, clockwise);
    }

    template <typename pointT>
    void add_arc(pointT const& pt0, pointT const& pt1, real radius)
    {
        CGPathAddArcToPoint(_path, _transform, pt0.x, pt0.y, pt1.x, pt1.y, radius);
    }
    
    template <typename pointT>
    void add_curve(pointT const& c1, pointT const& c2, pointT const& pt)
    {
        CGPathAddCurveToPoint(_path, _transform, c1.x, c1.y, c2.x, c2.y, pt.x, pt.y);
    }
    
    template <typename pointT>
    void add_quadcurve(pointT const& c, pointT const& pt)
    {
        CGPathAddQuadCurveToPoint(_path, _transform, c.x, c.y, pt.x, pt.y);
    }
    
    void add_rect(CGRect const& rc)
    {
        CGPathAddRect(_path, _transform, rc);
    }
    
    void add_rect(CGRect const& rc, bool clock);
    
    void add_ellipse(CGRect const& rc)
    {
        CGPathAddEllipseInRect(_path, _transform, rc);
    }
    
    void add_roundsrect(CGRect const& rc, CGFloat radius, bool lt = true, bool rt = true, bool lb = true, bool rb = true)
    {
        CGPathAddBoundsRect(_path, rc, radius, lt, rt, lb, rb);
    }
    
    void place(Graphics&) const;
    void stroke(Graphics&, Pen const& pen) const;
    void stroke(Graphics&, Shadow const& sd) const;
    void fill(Graphics&, Brush const& br) const;
    void fill(Graphics&, GradientBrush const& br) const;
    void fill(Graphics&, Fill const& fl) const;
    
    static self_type Copy(CGPathRef r)
    {
        self_type ret(NULL);
        ret._path = CGPathCreateMutableCopy(r);
        return ret;
    }
    
    static self_type Use(CGMutablePathRef r)
    {
        return self_type(r);
    }
    
protected:
    
    Path(CGMutablePathRef r)
    : _path(r)
    {
        CGPathRetain(_path);
    }
    
    void _set(CGMutablePathRef r)
    {
        release();
        _path = r;
        CGPathRetain(_path);
    }    
    
protected:
    
    CGMutablePathRef _path;
    Matrix _transform;
    
};

class Bezier
{
public:
    
    Bezier()
    {
        _bezier = [[UIBezierPath bezierPath] retain];
    }
    
    Bezier(Path& ph)
    {
        _bezier = [[UIBezierPath bezierPath] retain];
        set_path(ph);
    }
    
    ~Bezier()
    {
        safe_release(_bezier);
    }
    
    void set_path(Path& ph)
    {
        _bezier.CGPath = ph;
    }
    
    void set_rect(Rect const& rc)
    {
        clear();
        _bezier = [[UIBezierPath bezierPathWithRect:rc] retain];
    }
    
    void set_oval(Rect const& rc)
    {
        clear();
        _bezier = [[UIBezierPath bezierPathWithOvalInRect:rc] retain];
    }
    
    void set_rounded(Rect const& rc, Size const& radius, UIRectCorner corner = UIRectCornerAllCorners)
    {
        clear();
        _bezier = [[UIBezierPath bezierPathWithRoundedRect:rc byRoundingCorners:corner cornerRadii:radius] retain];
    }
    
    void set_arc(Point const& center, real radius, Angle const& start, Angle const& end, bool clockwise = true)
    {
        clear();
        _bezier = [[UIBezierPath bezierPathWithArcCenter:center radius:radius startAngle:start endAngle:end clockwise:clockwise] retain];
    }
    
    void clear()
    {
        zero_release(_bezier);
    }
    
    void move_to(Point const& pt)
    {
        [_bezier moveToPoint:pt];
    }
    
    void line_to(Point const& pt)
    {
        [_bezier addLineToPoint:pt];
    }
    
    void curve_to(Point const& pt, Point const& ctlpt1, Point const& ctlpt2)
    {
        [_bezier addCurveToPoint:pt controlPoint1:ctlpt1 controlPoint2:ctlpt2];
    }

    void quadcurve_to(Point const& endpt, Point const& ctlpt)
    {
        [_bezier addQuadCurveToPoint:endpt controlPoint:ctlpt];
    }

    void add_arc(Point const& center, real radius, Angle const& start, Angle const& end, bool clockwise = true)
    {
        [_bezier addArcWithCenter:center radius:radius startAngle:start endAngle:end clockwise:clockwise];
    }

    void close()
    {
        [_bezier closePath];
    }
    
    void remove_points()
    {
        [_bezier removeAllPoints];
    }
    
    void append(Bezier& ph)
    {
        [_bezier appendPath:ph];
    }
    
    void reset()
    {
        safe_release(_bezier);
        _bezier = [[UIBezierPath bezierPath] retain];
    }
    
    operator UIBezierPath* () const
    {
        return (UIBezierPath*)_bezier;
    }
    
    operator CGPathRef () const
    {
        return (CGPathRef)_bezier.CGPath;
    }
    
    operator ::wsi::cg::Path () const
    {
        return ::wsi::cg::Path((CGPathRef)_bezier.CGPath);
    }
    
    void place(Graphics&) const;
    void fill(Graphics&, Brush const&) const;
    void stroke(Graphics&, Pen const&) const;
    
protected:
    
    UIBezierPath* _bezier;
    
};

inline_impl void Path::add_rect(CGRect const& rc, bool clock)
{
    if (clock)
    {
        CGPathMoveToPoint(_path, _transform, rc.origin.x, rc.origin.y);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x + rc.size.width, rc.origin.y);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x + rc.size.width, rc.origin.y + rc.size.height);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x, rc.origin.y + rc.size.height);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x, rc.origin.y);
    }
    else
    {
        CGPathMoveToPoint(_path, _transform, rc.origin.x, rc.origin.y);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x, rc.origin.y + rc.size.height);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x + rc.size.width, rc.origin.y + rc.size.height);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x + rc.size.width, rc.origin.y);
        CGPathAddLineToPoint(_path, _transform, rc.origin.x, rc.origin.y);
    }
}

class Shape
{
public:
    
    Shape()
    {
        PASS;
    }
    
    virtual ~Shape()
    {
        PASS;
    }
            
    void draw(Graphics&) const;
    
protected:
    
    virtual void _dodraw(Graphics&) const = 0;
    
protected:
    
    Matrix _transform;
    
};

class Layer
{
public:
    
    Layer(CGContextRef ctx)
    : _ctx(ctx)
    {
        CGContextRetain(_ctx);
    }
    
    ~Layer()
    {
        CGContextRelease(_ctx);
    }
    
    void begin()
    {
        CGContextBeginTransparencyLayer(_ctx, nil);
    }
    
    void end()
    {
        CGContextEndTransparencyLayer(_ctx);
    }
        
protected:
    
    CGContextRef _ctx;
    
};

class Graphics
{
    typedef Graphics self_type;
    
public:
    
    Graphics()
    : _ctx(NULL)
    {
        _bounds = CGRectZero;
    }
    
    Graphics(CGContextRef ctx, CGRect const& region = CGRectZero)
    {
        _bounds = region;
        _ctx = ctx;
        CGContextRetain(_ctx);
        
        push_state();
    }
        
    Graphics(Graphics const& r)
    {
        _bounds = r._bounds;
        _ctx = r._ctx;
        CGContextRetain(_ctx);
        
        push_state();
    }
    
    Graphics& operator = (Graphics const& r)
    {
        release();
        _ctx = r._ctx;
        _bounds = r._bounds;
        CGContextRetain(_ctx);
        
        push_state();
        return *this;
    }
        
    ~Graphics()
    {
        release();
    }
    
    bool is_null() const
    {
        return _ctx == NULL;
    }
        
    void push_state()
    {
        CGContextSaveGState(_ctx);
    }
    
    void pop_state()
    {
        CGContextRestoreGState(_ctx);
    }
    
    void release()
    {
        if (_ctx)
        {
            pop_state();
            
            CGContextRelease(_ctx);
            _ctx = NULL;
        }
    }
    
    void flush()
    {
        CGContextFlush(_ctx);
    }
    
    void set_blend(CGBlendMode mode)
    {
        CGContextSetBlendMode(_ctx, mode);
    }
    
    Rect const& bounds() const
    {
        return _bounds;
    }
    
    Image to_image() const
    {
        CGImageRef img = CGBitmapContextCreateImage(_ctx);
        Image ret(img);
        CGImageRelease(img);    
        return ret;
    }
    
    bool create_rgba(Size const& sz)
    {
        real width = sz.width();
        real height = sz.height();
        
        release();
        
        _bounds.set_width(width);
        _bounds.set_height(height);
        
        // create new.
        CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
        _ctx = CGBitmapContextCreate(NULL,
                                     width,
                                     height,
                                     8,
                                     0,
                                     colorspace,
                                     kCGImageAlphaPremultipliedLast);
        CGColorSpaceRelease(colorspace);

        if (_ctx)
            push_state();
        
        return _ctx != NULL;
    }
    
    bool crate_gray(Size const& sz)
    {
        real width = sz.width();
        real height = sz.height();
        
        release();
        
        _bounds.set_width(width);
        _bounds.set_height(height);
        
        // create new.
        CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceGray();
        _ctx = CGBitmapContextCreate(NULL,
                                     width,
                                     height,
                                     8,
                                     width,
                                     colorspace,
                                     kCGImageAlphaNone);
        CGColorSpaceRelease(colorspace);
        
        if (_ctx)
            push_state();
        
        return _ctx != NULL;
    }
    
    void reverse()
    {
        CGContextTranslateCTM(_ctx, 0, _bounds.height());
        CGContextScaleCTM(_ctx, 1, -1);
    }
    
    void mult_matrix(Matrix const& mat)
    {
        CGContextConcatCTM(_ctx, mat);
    }
    
    void set_matrix(Matrix const& mat)
    {
        CGAffineTransform cur_mat = CGContextGetCTM(_ctx);
        cur_mat = CGAffineTransformInvert(cur_mat);
        CGContextConcatCTM(_ctx, cur_mat);
        CGContextConcatCTM(_ctx, mat);
    }
    
    void translate(real x, real y)
    {
        CGContextTranslateCTM(_ctx, x, y);
    }
    
    void rotate(real angle)
    {
        CGContextRotateCTM(_ctx, angle);
    }
    
    void scale(real x, real y)
    {
        CGContextScaleCTM(_ctx, x, y);
    }
    
    void clear(CGRect const& rc)
    {
        CGContextClearRect(_ctx, rc);
    }
    
    void resize(Size const& sz)
    {
        CGContextClipToRect(_ctx, Rect(sz));
    }
    
    void resize(Rect const& rc)
    {
        CGContextClipToRect(_ctx, rc);
    }
    
    void clip()
    {
        CGContextClip(_ctx);
    }
    
    operator CGContextRef () const
    {
        return (CGContextRef)_ctx;
    }
    
    static self_type Current(CGRect rc = CGRectZero)
    {
        return self_type(WCGGetCurrentContext(), rc);
    }
    
    Layer layer() const
    {
        return Layer(_ctx);
    }
    
protected:
    
    Rect _bounds;
    CGContextRef _ctx;
    
};

NNT_BEGIN_NS(ui)

class Graphics
{
public:
    
    static void Push(::juice::cocoa::Graphics& gra)
    {
        UIGraphicsPushContext(gra);
    }
    
    static void Pop()
    {
        UIGraphicsPopContext();
    }
    
};

NNT_END_NS

inline_impl void Color::fill(Graphics& gra) const
{
    CGContextSetFillColorWithColor(gra, *this);        
}

inline_impl void Color::stroke(Graphics& gra) const
{
    CGContextSetStrokeColorWithColor(gra, *this);
}

inline_impl void Pen::set(Graphics& gra) const
{
    _color.stroke(gra);
    CGContextSetLineWidth(gra, _width);
}

inline_impl void Shadow::set(Graphics& gra) const
{
    CGContextSetShadowWithColor(gra, offset(), radius(), color());
}

inline_impl void Pen::stroke(Graphics& gra, CGRect const& rc) const
{
    set(gra);
    CGContextStrokeRect(gra, rc);
}

inline_impl void Image::fill(Graphics& gra, CGRect const& rc) const
{
    CGContextDrawImage(gra, rc, *this);
}

inline_impl void Brush::set(Graphics& gra) const
{
    _color.fill(gra);
    
    // set pattern.
    if (_fpattern)
        (this->*_fpattern)(gra);
}

inline_impl void Brush::fill(Graphics& gra, CGRect const& rc) const
{        
    set(gra);    
    CGContextFillRect(gra, rc);
}

inline_impl void GradientBrush::fill(Graphics& gra, CGRect const& rc) const
{
    set(gra);
    _gradient.fill_rect(gra, rc);
}

inline_impl void GradientBrush::fill_path(Graphics& gra) const
{
    set(gra);
    _gradient.fill_path(gra);
}

inline_impl void ImageBrush::fill(Graphics& gra, CGRect const& rc) const
{
    CGContextDrawImageOri(gra, rc, _image);
}

inline_impl void Fill::fill(Graphics& gra) const
{
    super::fill((CGContextRef)gra);
}

inline_impl void Fill::fill(Graphics& gra, CGRect const& rc) const
{
    super::fill(rc, (CGContextRef)gra);
}

inline_impl void Path::place(Graphics& gra) const
{
    CGContextAddPath(gra, _path);
}

inline_impl void Path::stroke(Graphics& gra, Pen const& pen) const
{
    pen.set(gra);
    CGContextAddPath(gra, _path);
    CGContextStrokePath(gra);
}

inline_impl void Path::stroke(Graphics& gra, Shadow const& sd) const
{
    gra.push_state();
    
    //sd.set(gra);
    //Pen pen(sd.shadow_color(), sd.radius());
    //stroke(gra, pen);
    CGContextAddPath(gra, _path);
    sd.stroke(gra);
    
    gra.pop_state();
}

inline_impl void Path::fill(Graphics & gra, Brush const& br) const
{
    br.set(gra);
    CGContextAddPath(gra, _path);
    CGContextFillPath(gra);
}

inline_impl void Path::fill(Graphics& gra, GradientBrush const& br) const
{
    br.set(gra);
    CGContextAddPath(gra, _path);
    br.fill_path(gra);
}

inline_impl void Path::fill(Graphics& gra, Fill const& fl) const
{
    CGContextAddPath(gra, _path);
    fl.fill(gra);
}

inline_impl void Bezier::place(Graphics& gra) const
{
    CGContextAddPath(gra, _bezier.CGPath);
}

inline_impl void Bezier::fill(Graphics& gra, Brush const& br) const
{
    br.set(gra);
    ui::Graphics::Push(gra);
    [_bezier fill];
    ui::Graphics::Pop();
}

inline_impl void Bezier::stroke(Graphics& gra, Pen const& pn) const
{
    pn.set(gra);
    ui::Graphics::Push(gra);
    _bezier.lineWidth = pn.width();
    [_bezier stroke];
    ui::Graphics::Pop();
}

inline_impl void String::draw(Graphics& gra, Point const& pt, bool adjust) const
{
    if (adjust)
    {
        CGContextSaveGState(gra);
        CGContextTranslateCTM(gra, pt.x, pt.y);
        CGContextScaleCTM(gra, 1, -1);
        CGContextAddTextAtPoint(gra, CGPointZero, *this, style);
        CGContextRestoreGState(gra);
    }
    else
    {
        CGContextAddTextAtPoint(gra, pt, *this, style);
    }
}

inline_impl void String::draw(Graphics& gra, Rect const& rc, bool adjust) const
{
    if (adjust)
    {
        CGContextSaveGState(gra);
        CGContextTranslateCTM(gra, rc.x(), rc.y());
        CGContextScaleCTM(gra, 1, -1);
        CGContextAddTextInRect(gra, CGRectMake(0, 0, rc.width(), rc.height()), *this, style);
        CGContextRestoreGState(gra);
    }
    else
    {
        CGContextAddTextInRect(gra, rc, *this, style);
    }
}

inline_impl void Shape::draw(Graphics& gra) const
{
    gra.push_state();
    gra.mult_matrix(_transform);
    this->_dodraw(gra);
    gra.pop_state();
}

NNT_END_NS 

template <typename matrixT>
class Orthogonal;

template <>
class Orthogonal < ::juice::cocoa::Matrix >
{
public:
    typedef ::juice::cocoa::Matrix matrix_type;
    
    Orthogonal(real n, real f, real l, real r, real t, real b)
    {
        mat.set_identity();        
        
        real r_l = r - l;
        real t_b = t - b;
        
        if (r_l == 0 || t_b == 0)
            return;        
        
        mat->tx = r_l * .5f;
        mat->ty = t_b * .5f;
    }
    
    matrix_type mat;
};

JUICE_END

# endif
