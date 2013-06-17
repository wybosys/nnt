
# ifndef __NNT_NG_BASE_C09F5A94FAE54904BBFD82D1926D1F7B_H_INCLUDED
# define __NNT_NG_BASE_C09F5A94FAE54904BBFD82D1926D1F7B_H_INCLUDED

NNT_BEGIN_HEADER_C

typedef struct _point3df
{
    real x, y, z;
} point3df;

typedef struct _point3di
{
    int x, y, z;
} point3di;

// as color-32bit percent

# define AS_C32P(val)        ((val) * 0.00392156862745)

# define RGBA_RED(value)     (((value) >> 24) & 0xFF)
# define RGBA_GREEN(value)   (((value) & 0xFF0000) >> 16)
# define RGBA_BLUE(value)    (((value) & 0xFF00) >> 8)
# define RGBA_ALPHA(value)   ((value) & 0xFF)

# define RGBA_RED_P(value)   AS_C32P(RGBA_RED(value))
# define RGBA_GREEN_P(value) AS_C32P(RGBA_GREEN(value))
# define RGBA_BLUE_P(value)  AS_C32P(RGBA_BLUE(value))
# define RGBA_ALPHA_P(value) AS_C32P(RGBA_ALPHA(value))

# define ARGB_RED(value)     (((value) & 0xFF0000) >> 16)
# define ARGB_GREEN(value)   (((value) & 0xFF00) >> 8)
# define ARGB_BLUE(value)    ((value) & 0xFF)
# define ARGB_ALPHA(value)   (((value) >> 24) & 0xFF)

# define ARGB_RED_P(value)   AS_C32P(ARGB_RED(value))
# define ARGB_GREEN_P(value) AS_C32P(ARGB_GREEN(value))
# define ARGB_BLUE_P(value)  AS_C32P(ARGB_BLUE(value))
# define ARGB_ALPHA_P(value) AS_C32P(ARGB_ALPHA(value))

# define RGB_ALPHA(value)    0xFF
# define RGB_RESTRICT(value) (((value) <= 0xFF) ? (value) : 0xFF)
# define RGB_RED             ARGB_RED
# define RGB_GREEN           ARGB_GREEN
# define RGB_BLUE            ARGB_BLUE

# define RGB_ALPHA_P(value)  1.f
# define RGB_RED_P           ARGB_RED_P
# define RGB_GREEN_P         ARGB_GREEN_P
# define RGB_BLUE_P          ARGB_BLUE_P

# define ARGB2RGBA(value)    (((value) << 8) | ARGB_ALPHA(value))
# define RGBA2ARGB(value)    (((value) >> 8) | (RGBA_ALPHA(value) << 24))

# define RGBA(red, green, blue, alpha) (((int)(red) << 24) | ((int)(green) << 16) | ((int)(blue) << 8) | (int)(alpha))
# define ARGB(red, green, blue, alpha) (((int)(alpha) << 24) | ((int)(red) << 16) | ((int)(green) << 8) | (int)(blue))

# ifndef RGB
#   define RGB(red, green, blue)         (((int)(red) << 16) | ((int)(green) << 8) | (int)(blue))
# endif

# define RGBA_MUL(value, mul) RGBA(RGBA_RED(value) * (mul), RGBA_GREEN(value) * (mul), RGBA_BLUE(value) * (mul), RGBA_ALPHA(value))
# define ARGB_MUL(value, mul) ARGB(ARGB_RED(value) * (mul), ARGB_GREEN(value) * (mul), ARGB_BLUE(value) * (mul), ARGB_ALPHA(value))
# define RGB_MUL              ARGB_MUL

# define RGBA_ADD_RGBA_RED(v0, v1)     RGB_RESTRICT(RGBA_RED(v0) + RGBA_RED(v1))
# define RGBA_ADD_RGBA_GREEN(v0, v1)   RGB_RESTRICT(RGBA_GREEN(v0) + RGBA_GREEN(v1))
# define RGBA_ADD_RGBA_BLUE(v0, v1)    RGB_RESTRICT(RGBA_BLUE(v0) + RGBA_BLUE(v1))
# define RGBA_ADD_RGBA_ALPHA(v0, v1)   RGB_RESTRICT(RGBA_ALPHA(v0) + RGBA_ALPHA(v1))
# define RGBA_ADD_RGBA(v0, v1)         RGBA(RGBA_ADD_RGBA_RED(v0, v1), RGBA_ADD_RGBA_GREEN(v0, v1), RGBA_ADD_RGBA_BLUE(v0, v1),RGBA_ADD_RGBA_ALPHA(v0, v1))

# define ARGB_ADD_ARGB_RED(v0, v1)     RGB_RESTRICT(ARGB_RED(v0)   + ARGB_RED(v1))
# define ARGB_ADD_ARGB_GREEN(v0, v1)   RGB_RESTRICT(ARGB_GREEN(v0) + ARGB_GREEN(v1))
# define ARGB_ADD_ARGB_BLUE(v0, v1)    RGB_RESTRICT(ARGB_BLUE(v0)  + ARGB_BLUE(v1))
# define ARGB_ADD_ARGB_ALPHA(v0, v1)   RGB_RESTRICT(ARGB_ALPHA(v0) + ARGB_ALPHA(v1))
# define ARGB_ADD_ARGB(v0, v1)         ARGB(ARGB_ADD_ARGB_RED(v0, v1), ARGB_ADD_ARGB_GREEN(v0, v1), ARGB_ADD_ARGB_BLUE(v0, v1),ARGB_ADD_ARGB_ALPHA(v0, v1))

# define RGBA_SET_RED(value, val)    RGBA(val, RGBA_GREEN(value), RGBA_BLUE(value), RGBA_ALPHA(value))
# define RGBA_SET_GREEN(value, val)  RGBA(RGBA_RED(value), val, RGBA_BLUE(value), RGBA_ALPHA(value))
# define RGBA_SET_BLUE(value, val)   RGBA(RGBA_RED(value), RGBA_GREEN(value), val, RGBA_ALPHA(value))
# define RGBA_SET_ALPHA(value, val)  RGBA(RGBA_RED(value), RGBA_GREEN(value), RGBA_BLUE(value), val)

# define ARGB_SET_RED(value, val)    ARGB(val, ARGB_GREEN(value), ARGB_BLUE(value), ARGB_ALPHA(value))
# define ARGB_SET_GREEN(value, val)  ARGB(ARGB_RED(value), val, ARGB_BLUE(value), ARGB_ALPHA(value))
# define ARGB_SET_BLUE(value, val)   ARGB(ARGB_RED(value), ARGB_GREEN(value), val, ARGB_ALPHA(value))
# define ARGB_SET_ALPHA(value, val)  ARGB(ARGB_RED(value), ARGB_GREEN(value), ARGB_BLUE(value), val)

# define RGB_SET_RED                 ARGB_SET_RED
# define RGB_SET_GREEN               ARGB_SET_GREEN
# define RGB_SET_BLUE                ARGB_SET_BLUE
# define RGB_SET_ALPHA(value, val)   (value)

# define RGB_COMP_INV(value)         (0xff - (value))
# define ARGB_INV(value)             ARGB(RGB_COMP_INV(ARGB_RED(value)), RGB_COMP_INV(ARGB_GREEN(value)), RGB_COMP_INV(ARGB_BLUE(value)), ARGB_ALPHA(value))
# define RGBA_INV(value)             RGBA(RGB_COMP_INV(RGBA_RED(value)), RGB_COMP_INV(RGBA_GREEN(value)), RGB_COMP_INV(RGBA_BLUE(value)), RGBA_ALPHA(value))

typedef union {
    struct {
        byte r;
        byte g;
        byte b;
    } d;
    uint v:24;
    int sv:24;
} _rgb_ct;

# ifdef NNT_CXX

class _rgb_cxxt
{
public:
    
    _rgb_cxxt(uint v = 0)
    {
        val.v = v;
    }
    
    _rgb_cxxt(_rgb_ct const& r)
    : val(r)
    {
        PASS;
    }
    
    operator uint () const
    {
        return val.v;
    }
    
    _rgb_cxxt& operator = (uint v)
    {
        val.v = v;
        return *this;
    }
    
    byte red() const
    {
        return val.d.r;
    }
    
    byte green() const
    {
        return val.d.g;
    }
    
    byte blue() const
    {
        return val.d.b;
    }
    
    _rgb_ct val;
};

typedef _rgb_cxxt rgb_t;

# else

typedef _rgb_ct rgb_t;

# endif

inline_impl _rgb_ct rgb(uint v)
{
    _rgb_ct r;
    r.v = v;
    return r;
}

typedef union {
    struct {
        byte r;
        byte g;
        byte b;
        byte a;
    } d;
    uint v;
    int sv;
} _rgba_ct;

# ifdef NNT_CXX

class _rgba_cxxt
{
public:
    
    _rgba_cxxt(uint v = 0)
    {
        val.v = v;
    }
    
    _rgba_cxxt(_rgba_ct const& r)
    : val(r)
    {
        PASS;
    }
    
    operator uint () const
    {
        return val.v;
    }
    
    _rgba_cxxt& operator = (uint v)
    {
        val.v = v;
        return *this;
    }
    
    byte red() const
    {
        return val.d.r;
    }
    
    byte green() const
    {
        return val.d.g;
    }
    
    byte blue() const
    {
        return val.d.b;
    }
    
    byte alpha() const
    {
        return val.d.a;
    }
    
    _rgba_ct val;
};

typedef _rgba_cxxt rgba_t;

# else

typedef _rgba_ct rgba_t;

# endif

inline_impl _rgba_ct rgba(uint v)
{
    _rgba_ct r;
    r.v = v;
    return r;
}

typedef union {
    struct {
        byte a;
        byte r;
        byte g;
        byte b;
    } d;
    uint v;
    int sv;
} _argb_ct;

# ifdef NNT_CXX

class _argb_cxxt
{
public:
    
    _argb_cxxt(uint v = 0)
    {
        val.v = v;
    }
    
    _argb_cxxt(_argb_ct const& r)
    : val(r)
    {
        PASS;
    }
    
    operator uint () const
    {
        return val.v;
    }
    
    _argb_cxxt& operator = (uint v)
    {
        val.v = v;
        return *this;
    }
    
    byte red() const
    {
        return val.d.r;
    }
    
    byte green() const
    {
        return val.d.g;
    }
    
    byte blue() const
    {
        return val.d.b;
    }
    
    byte alpha() const
    {
        return val.d.a;
    }
    
    _argb_ct val;
};

typedef _argb_cxxt argb_t;

# else

typedef _argb_ct argb_t;

# endif

inline_impl _argb_ct argb(uint v)
{
    _argb_ct r;
    r.v = v;
    return r;
}

NNT_END_HEADER_C

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

typedef struct {
    CGRect rect;
    CGAffineTransform transform;
} CGTransformRect;

static CGTransformRect CGTransformRectMake(CGRect rc, CGAffineTransform mat) {
    return (CGTransformRect){rc, mat};
}

typedef enum _CGRectPositionType {
    CGRectPositionTypeLeft = 0x1,
    CGRectPositionTypeRight = 0x2,
    CGRectPositionTypeTop = 0x4,
    CGRectPositionTypeBottom = 0x8,
    CGRectPositionTypeLeftTop = CGRectPositionTypeLeft | CGRectPositionTypeTop,
    CGRectPositionTypeRightTop = CGRectPositionTypeRight | CGRectPositionTypeTop,
    CGRectPositionTypeLeftBottom = CGRectPositionTypeLeft | CGRectPositionTypeBottom,
    CGRectPositionTypeRightBottom = CGRectPositionTypeRight | CGRectPositionTypeBottom
} CGRectPositionType;

CGPoint CGRectCenterPoint(CGRect const*);
CGPoint CGRectCenterPoint2(CGRect);

typedef struct _CGPadding {
    real top, bottom, left, right;
} CGPadding;

typedef struct _CGMargin {
    real top, bottom, left, right;
} CGMargin;

# define CGPADDING_DEFINED 1
# define CGMARGIN_DEFINED 1

extern const CGPadding CGPaddingZero;
extern const CGMargin CGMarginZero;

extern CGPadding CGPaddingMake(real t, real b, real l, real r);
extern CGMargin CGMarginMake(real t, real b, real l, real r);

extern real CGPaddingGetWidth(CGPadding const*);
extern real CGPaddingGetHeight(CGPadding const*);

# ifdef NNT_CXX

inline_impl bool CGPaddingEqualToPadding(CGPadding const& l, CGPadding const& r)
{
    return memcmp(&l, &r, sizeof(CGPadding)) == 0;
}

inline_impl CGRect operator << (CGRect rc, CGMargin const& mrg)
{
    rc.origin.x += mrg.left;
    rc.origin.y += mrg.top;
    rc.size.width -= mrg.left + mrg.right;
    rc.size.height -= mrg.top + mrg.bottom;
    return rc;
}

# endif

CGPoint CGRectRightTop(CGRect const*);
CGPoint CGRectLeftBottom(CGRect const*);
CGPoint CGRectRightBottom(CGRect const*);
CGPoint CGRectLeftCenter(CGRect const*);
CGPoint CGRectRightCenter(CGRect const*);
CGPoint CGRectTopCenter(CGRect const*);
CGPoint CGRectBottomCenter(CGRect const*);
CGRect  CGRectSwap(CGRect const*);
CGFloat CGRectBottom(CGRect);

CGRect CGRectMakeRectByCenter(CGRect const*, CGFloat width, CGFloat height);
CGRect CGRectMakeRectByCenter2(CGRect, CGFloat width, CGFloat height);

CGPoint CGRectRightTop2(CGRect);
CGPoint CGRectLeftBottom2(CGRect);
CGPoint CGRectRightBottom2(CGRect);
CGPoint CGRectLeftCenter2(CGRect);
CGPoint CGRectRightCenter2(CGRect);
CGPoint CGRectTopCenter2(CGRect);
CGPoint CGRectBottomCenter2(CGRect);
CGRect  CGRectSwap2(CGRect);

CGRect  CGRectAddWidth2(CGRect, CGFloat);
CGRect  CGRectAddHeight2(CGRect, CGFloat);
CGRect  CGRectAddX2(CGRect, CGFloat);
CGRect  CGRectAddY2(CGRect, CGFloat);
CGRect  CGRectAdd2(CGRect, CGFloat, CGFloat, CGFloat, CGFloat);

CGRect  CGRectSetRatioPadding(CGRect, CGPadding);

CGRect  CGRectToSquare(CGRect const*);
CGRect  CGRectToSquare2(CGRect);

CGRect CGRectContract(CGRect rect, CGFloat dx, CGFloat dy);
CGRect CGRectShift(CGRect rect, CGFloat dx, CGFloat dy);

CGRect CGRectOffsetR(CGRect rect, CGFloat rw, CGFloat rh);
CGRect CGRectBound(CGRect rect, BOOL max);

MACEXPRESS(typedef NSEdgeInsets UIEdgeInsets);

CGRect CGRectInsetWithInset(CGRect rect, UIEdgeInsets insets);

BOOL CGPointEqualWithPrecise(CGPoint l, CGPoint r, int precise);

# define CGRectAddWidth(rc, val)      CGRectMake(rc.origin.x, rc.origin.y, rc.size.width + (val), rc.size.height)
# define CGRectAddHeight(rc, val)     CGRectMake(rc.origin.x, rc.origin.y, rc.size.width, rc.size.height + (val))
# define CGRectAddX(rc, val)          CGRectMake(rc.origin.x + (val), rc.origin.y, rc.size.width, rc.size.height)
# define CGRectAddY(rc, val)          CGRectMake(rc.origin.x, rc.origin.y + (val), rc.size.width, rc.size.height)
# define CGRectAdd(rc, xv, yv, wv, hv)    CGRectMake(rc.origin.x + xv, rc.origin.y + yv, rc.size.width + wv, rc.size.height + hv)
# define CGRectSub(rc, xv, yv, wv, hv)    CGRectAdd(rc, -(xv), -(yv), -(wv), -(hv));

# define CGRectMakePtSz(pt, sz)       CGRectMake(pt.x, pt.y, sz.width, sz.height)
# define CGRectMakePt(pt)             CGRectMake(pt.x, pt.y, 0, 0)
# define CGRectMakeSz(sz)             CGRectMake(0, 0, sz.width, sz.height)
# define CGRectMakeWH(wv, hv)         CGRectMake(0, 0, wv, hv)
# define CGRectMakeXY(xv, yv)         CGRectMake(xv, yv, 0, 0)

# define CGPointAddPoint(pt0, pt1)    CGPointMake(pt0.x + pt1.x, pt0.y + pt1.y)
# define CGPointAddX(pt, v)           CGPointMake(pt.x + v, pt.y)
# define CGPointAddY(pt, v)           CGPointMake(pt.x, pt.y + v)
# define CGPointAddXY(pt, v, z)       CGPointMake(pt.x + v, pt.y + z)
# define CGPointSetX(pt, v)           CGPointMake(v, pt.y)
# define CGPointSetY(pt, v)           CGPointMake(pt.x, v)
# define CGPointMakeX(x)              CGPointMake(x, 0)
# define CGPointMakeY(y)              CGPointMake(0, y)

//! deflate in pixel.
NNT_EXTERN CGRect CGRectDeflateCenter(CGRect src, CGFloat x, CGFloat y);

//! deflate in ratio.
NNT_EXTERN CGRect CGRectDeflateCenterR(CGRect src, CGFloat rx, CGFloat ry);
NNT_EXTERN CGRect CGRectDeflateR(CGRect src, CGFloat l, CGFloat r, CGFloat t, CGFloat b);

//! move rect to center.
NNT_EXTERN CGRect CGRectMoveCenter(CGRect src, CGPoint pt);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "../Math/Math+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

class Angle
: public core::uml::composition<Angle, real>
{
public:
    
    Angle(real val = 0)
    {
        _obj = ANGLE2RAD(val);
    }
    
    static Angle Rad(real val)
    {
        Angle ret;
        ret._obj = val;
        return ret;
    }
    
    real angle() const
    {
        return RAD2ANGLE(_obj);
    }
    
    real rad() const
    {
        return _obj;
    }
    
};

class ratio
{
public:
    
    ratio(real _val)
    : value(_val)
    {}
    
    operator real& ()
    {
        return value;
    }
    
    operator real () const
    {
        return value;
    }
    
    real value;
    
};

class pixel
{
public:
    
    pixel(int _val)
    : value(_val)
    {}
    
    operator int& ()
    {
        return value;
    }
    
    operator real () const
    {
        return value;
    }
    
    int value;
    
};

class Insets
{
public:
    
    Insets(CGFloat t = 0, CGFloat l = 0, CGFloat b = 0, CGFloat r = 0)
    : top(t), left(l), bottom(b), right(r)
    {
        PASS;
    }
    
    ~Insets()
    {
        PASS;
    }
    
    operator UIEdgeInsets& ()
    {
        return *(UIEdgeInsets*)this;
    }
    
    operator UIEdgeInsets const& () const
    {
        return *(UIEdgeInsets const*)this;
    }
    
    static Insets const& Zero()
    {
        static const Insets _zero;
        return _zero;
    }
    
    CGFloat top, left, bottom, right;
    
};

class Padding
{
public:
    
    Padding(CGPadding const& pad = CGPaddingZero)
    : _pad(pad)
    {
        PASS;
    }
    
    Padding(real top, real bottom, real left, real right)
    {
        set(top, bottom, left, right);
    }
    
    void set(real top, real bottom, real left, real right)
    {
        _pad.top = top;
        _pad.bottom = bottom;
        _pad.left = left;
        _pad.right = right;
    }
    
    operator CGPadding& ()
    {
        return _pad;
    }
    
    operator CGPadding const& () const
    {
        return _pad;
    }
    
    Padding& operator = (CGPadding const& r)
    {
        _pad = r;
        return *this;
    }
    
    real top() const
    {
        return _pad.top;
    }
    
    void set_top(real val)
    {
        _pad.top = val;
    }

    real bottom() const
    {
        return _pad.bottom;
    }
    
    void set_bottom(real val)
    {
        _pad.bottom = val;
    }
    
    real left() const
    {
        return _pad.left;
    }
    
    void set_left(real val)
    {
        _pad.left = val;
    }
    
    real right() const
    {
        return _pad.right;
    }
    
    void set_right(real val)
    {
        _pad.right = val;
    }
    
protected:
    
    CGPadding _pad;
    
};

class Point
{
public:
    
    Point()
    : x(0), y(0)
    {
        
    }
    
    Point(CGPoint const& pt)
    {
        x = pt.x;
        y = pt.y;
    }
    
    Point(real _x, real _y)
    : x(_x), y(_y)
    {
        PASS;
    }
    
    void set(CGPoint const& r)
    {
        x = r.x;
        y = r.y;
    }
    
    void set(real _x, real _y)
    {
        x = _x;
        y = _y;
    }
    
    void set_x(real v)
    {
        x = v;
    }
    
    void set_y(real v)
    {
        y = v;
    }
    
    operator CGPoint const& () const
    {
        return *(CGPoint*)this;
    }
    
    operator CGPoint& ()
    {
        return *(CGPoint*)this;
    }
    
    Point operator + (CGPoint const& r) const
    {
        Point ret = *this;
        ret.x += r.x;
        ret.y += r.y;
        return ret;
    }
    
    Point& operator += (CGPoint const& r)
    {
        x += r.x;
        y += r.y;
        return *this;
    }
    
    Point operator - (CGPoint const& r) const
    {
        Point ret = *this;
        ret.x -= r.x;
        ret.y -= r.y;
        return ret;
    }
    
    Point& operator -= (CGPoint const& r)
    {
        x -= r.x;
        y -= r.y;
        return *this;
    }
    
    Point& operator = (CGPoint const& r)
    {
        set(r);
        return *this;
    }
    
    bool is_equal(CGPoint const& r, int prec = 0) const
    {
        return CGPointEqualWithPrecise((CGPoint const&)*this, r, prec);
    }
    
    bool operator == (CGPoint const& r) const
    {
        return CGPointEqualToPoint(*this, r);
    }
    
    static Point const& Zero()
    {
        static const Point ze;
        return ze;
    }
    
    Point& operator *= (CGAffineTransform const& mat)
    {
        *this = CGPointApplyAffineTransform(*this, mat);
        return *this;
    }
    
    Point operator * (CGAffineTransform const& mat) const
    {
        Point ret = *this;
        ret *= mat;
        return ret;
    }
    
    real length_sq() const
    {
        return x*x + y*y;
    }
    
    real length() const
    {
        return sqrt(length_sq());
    }
    
public:
    
    CGFloat x, y;
        
};

class Line
{
public:
    
    Line()
    {
        PASS;
    }
    
    Line(Point const& _s, Point const& _e)
    : s(_s), e(_e)
    {
        PASS;
    }
    
    real length() const
    {
        return (e - s).length();
    }
    
    Point center() const
    {
        Point pt;
        pt.x = (e.x - s.x) * .5f + s.x;
        pt.y = (e.y - s.y) * .5f + s.y;
        return pt;
    }
    
    Point s, e;
    
};

class Size
{
public:
    
    Size()
    {
        _size = CGSizeZero;
    }
    
    Size(CGSize const& sz)
    {
        _size = sz;
    }
    
    Size(CGRect const& rc)
    {
        _size = rc.size;
    }
    
    Size(real w, real h)
    {
        _size.width = w;
        _size.height = h;
    }
    
    void set(CGSize const& sz)
    {
        _size = sz;
    }
    
    Size& operator = (CGSize const& sz)
    {
        _size = sz;
        return *this;
    }
    
    void set(CGRect const& rc)
    {
        _size = rc.size;
    }
    
    Size& operator = (CGRect const& rc)
    {
        _size = rc.size;
        return *this;
    }
    
    void set(real w, real h)
    {
        _size.width = w;
        _size.height = h;
    }
    
    void set_width(real w)
    {
        _size.width = w;
    }
    
    void set_height(real h)
    {
        _size.height = h;
    }
    
    static Size const& zero()
    {
        static const Size ze;
        return ze;
    }
    
    real width() const
    {
        return _size.width;
    }
    
    real height() const
    {
        return _size.height;
    }
    
    operator CGSize const& () const
    {
        return _size;
    }
    
    operator CGSize& ()
    {
        return _size;
    }
    
    CGSize const* operator -> () const
    {
        return &_size;
    }
    
    CGSize* operator -> ()
    {
        return &_size;
    }
    
    Size& operator *= (CGAffineTransform const& mat)
    {
        _size = CGSizeApplyAffineTransform(_size, mat);
        return *this;
    }
    
    Size operator * (CGAffineTransform const& mat) const
    {
        Size ret = *this;
        ret *= mat;
        return ret;
    }
    
protected:
    
    CGSize _size;
    
};

class Rect
{
public:
    
    Rect()
    {
        _rect = CGRectZero;
    }
    
    Rect(CGSize const& sz)
    {
        _rect = CGRectZero;
        _rect.size = sz;
    }
    
    Rect(Size const& sz)
    {
        _rect = CGRectZero;
        _rect.size = sz;
    }
    
    Rect(Point const& pt)
    {
        _rect = CGRectZero;
        _rect.origin = pt;
    }
    
    Rect(CGPoint const& pt)
    {
        _rect = CGRectZero;
        _rect.origin = pt;
    }
    
    Rect(CGRect const& rc)
    : _rect(rc)
    {
        PASS;
    }
    
    Rect(real x, real y = 0, real width = 0, real height = 0)
    {
        _rect = CGRectMake(x, y, width, height);
    }
    
    Rect(CGPoint const& pt, CGSize const& sz = CGSizeZero)
    {
        _rect.origin = pt;
        _rect.size = sz;
    }
    
    void set_zero()
    {
        _rect = CGRectZero;
    }
    
    static Rect const& Zero()
    {
        static Rect ze;
        return ze;
    }
    
    void set_integral()
    {
        _rect = CGRectIntegral(_rect);
    }
    
    Rect integral() const
    {
        return CGRectIntegral(_rect);
    }
    
    real x() const
    {
        return _rect.origin.x;
    }
    
    real y() const
    {
        return _rect.origin.y;
    }
    
    void set_pos(real x, real y)
    {
        _rect.origin = CGPointMake(x, y);
    }
    
    void set_pos(CGPoint const& pt)
    {
        _rect.origin = pt;
    }
    
    void set_x(real x)
    {
        _rect.origin.x = x;
    }
    
    void set_y(real y)
    {
        _rect.origin.y = y;
    }
    
    CGPoint const& pos() const
    {
        return _rect.origin;
    }
    
    Point center() const
    {
        return CGRectCenterPoint(&_rect);
    }
    
    real width() const
    {
        return _rect.size.width;
    }
    
    void set_width(real w)
    {
        _rect.size.width = w;
    }
    
    real height() const
    {
        return _rect.size.height;
    }
    
    void set_height(real h)
    {
        _rect.size.height = h;
    }
    
    Size size() const
    {
        return _rect.size;
    }
    
    void set_size(real w, real h)
    {
        _rect.size = CGSizeMake(w, h);
    }
    
    void set_size(CGSize const& sz)
    {
        _rect.size = sz;
    }
    
    Rect& operator = (CGRect const& rc)
    {
        _rect = rc;
        return *this;
    }
    
    Rect& operator = (Rect const& rc)
    {
        _rect = rc._rect;
        return *this;
    }
    
    bool operator == (Rect const& rc) const
    {
        return CGRectEqualToRect(_rect, rc._rect);
    }
    
    bool operator != (Rect const& rc) const
    {
        return !(*this == rc);
    }
    
    operator CGRect const& () const
    {
        return _rect;
    }
    
    operator CGRect& ()
    {
        return _rect;
    }
    
    /*
    operator CGSize const& () const
    {
        return _rect.size;
    }
    
    operator CGPoint const& () const
    {
        return _rect.origin;
    }
     */
    
    Rect& operator *= (CGAffineTransform const& mat)
    {
        _rect = CGRectApplyAffineTransform(_rect, mat);
        return *this;
    }

    Rect operator * (CGAffineTransform const& mat) const
    {
        Rect ret = *this;
        return ret * mat;
    }
    
    Rect deflate(ratio const& l, ratio const& r = 0, ratio const& t = 0, ratio const& b = 0) const
    {
        return CGRectDeflateR(_rect, l, r, t, b);
    }
    
    Rect deflate(pixel const& l, pixel const& r = 0, pixel const& t = 0, pixel const& b = 0) const
    {
        CGRect ret = _rect;
        ret.origin.x += l;
        ret.origin.y += t;
        ret.size.width -= l + r;
        ret.size.height -= t + b;
        return ret;
    }
    
    bool is_intersect(Rect const& r) const
    {
        return (Line(center(), r.center()).length() * 2) < (width() + r.width());
    }
    
    bool is_contain(Rect const& r) const
    {
        return (Line(center(), r.center()).length() * 2) < MIN(width(), r.width());
    }
    
    Point lt() const
    {
        return _rect.origin;
    }
    
    Point rt() const
    {
        return CGRectRightTop(&_rect);
    }
    
    Point rb() const
    {
        return CGRectRightBottom(&_rect);
    }
    
    Point lb() const
    {
        return CGRectLeftBottom(&_rect);
    }
    
    cg::Rect location(cg::Rect const& rc) const
    {
        CGRect ret = _rect;
        ret.origin.x += rc.x();
        ret.origin.y += rc.y();
        ret.size.width = rc.width();
        ret.size.height = rc.height();
        return ret;
    }
    
    cg::Rect& move_to(cg::Point const& pt)
    {
        _rect.origin = pt;
        return *this;
    }
    
    cg::Rect& center_to(cg::Point const& pt)
    {
        CGPoint pos = pt;
        pos.x -= _rect.size.width * .5f;
        pos.y -= _rect.size.height * .5f;
        _rect.origin = pos;
        return *this;
    }
    
protected:
    
    CGRect _rect;
    
};

class AffineTransform;

class Transform
{
    
public:
    
    Transform()
    {
        _mat = CATransform3DIdentity;
    }
    
    Transform(CATransform3D const& mat)
    : _mat(mat)
    {
        PASS;
    }
    
    static Transform const& Identity()
    {
        static const Transform idy;
        return idy;
    }
    
    bool is_identity() const
    {
        return CATransform3DIsIdentity(_mat);
    }
    
    void set_identity()
    {
        _mat = CATransform3DIdentity;
    }
    
    bool is_affine() const
    {
        return CATransform3DIsAffine(_mat);
    }
    
    AffineTransform affine() const;
    
    Transform invert() const
    {
        return CATransform3DInvert(_mat);
    }
    
    Transform translate(real x, real y = 1, real z = 1)
    {
        return CATransform3DTranslate(_mat, x, y, z);
    }
    
    static Transform Translate(real x, real y = 1, real z = 1)
    {
        return CATransform3DMakeTranslation(x, y, z);
    }
    
    Transform scale(real x, real y = 1, real z = 1)
    {
        return CATransform3DScale(_mat, x, y, z);
    }
    
    static Transform Scale(real x, real y = 1, real z = 1)
    {
        return CATransform3DMakeScale(x, y, z);
    }
    
    Transform rotate(cg::Angle const& ag, real x, real y = 1, real z = 1)
    {
        return CATransform3DRotate(_mat, ag.rad(), x, y, z);
    }
    
    static Transform Rotate(cg::Angle const& ag, real x, real y = 1, real z = 1)
    {
        return CATransform3DMakeRotation(ag.rad(), x, y, z);
    }
    
    operator CATransform3D& ()
    {
        return _mat;
    }
    
    operator CATransform3D const& () const
    {
        return _mat;
    }
    
    Transform& operator *= (CATransform3D const& r)
    {
        _mat = CATransform3DConcat(_mat, r);
        return *this;
    }
    
    Transform operator * (CATransform3D const& r) const
    {
        return CATransform3DConcat(_mat, r);
    }
    
protected:
    
    CATransform3D _mat;
    
};

class AffineTransform
{
    
public:
    
    AffineTransform()
    {
        _mat = CGAffineTransformIdentity;
    }
    
    AffineTransform(CGAffineTransform const& mat)
    : _mat(mat)
    {
        PASS;
    }
    
    static AffineTransform const& Identity()
    {
        static const AffineTransform idy;
        return idy;
    }
    
    void set_identity()
    {
        _mat = CGAffineTransformIdentity;
    }
    
    void clear()
    {
        _mat = CGAffineTransformIdentity;
    }
    
    bool is_identity() const
    {
        return CGAffineTransformIsIdentity(_mat);
    }
    
    bool is_equal(AffineTransform const& r) const
    {
        return CGAffineTransformEqualToTransform(_mat, r._mat);
    }
    
    bool operator == (AffineTransform const& r) const
    {
        return CGAffineTransformEqualToTransform(_mat, r._mat);
    }
    
    operator CGAffineTransform const& () const
    {
        return _mat;
    }
    
    operator CGAffineTransform& ()
    {
        return _mat;
    }
    
    operator CGAffineTransform const* () const
    {
        return &_mat;
    }
    
    operator CGAffineTransform* ()
    {
        return &_mat;
    }
    
    
    CGAffineTransform* operator -> ()
    {
        return &_mat;
    }
    
    CGAffineTransform const* operator -> () const
    {
        return &_mat;
    }
    
    AffineTransform invert() const
    {
        return CGAffineTransformInvert(_mat);
    }
    
    AffineTransform& operator = (AffineTransform const& r)
    {
        _mat = r._mat;
        return *this;
    }
    
    AffineTransform& operator *= (AffineTransform const& r)
    {
        _mat = CGAffineTransformConcat(_mat, r);
        return *this;
    }
    
    AffineTransform operator * (AffineTransform const& r) const
    {
        AffineTransform ret = *this;
        return ret *= r;
    }
    
    cg::Rect operator * (cg::Rect const& r) const
    {
        return CGRectApplyAffineTransform(r, _mat);
    }
    
    cg::Point operator * (cg::Point const& r) const
    {
        return CGPointApplyAffineTransform(r, _mat);
    }
    
    cg::Size operator * (cg::Size const& r) const
    {
        return CGSizeApplyAffineTransform(r, _mat);
    }
    
    AffineTransform translate(cg::Point pt) const
    {
        return CGAffineTransformTranslate(_mat, pt.x, pt.y);
    }
    
    AffineTransform scale(real x, real y = 1)
    {
        return CGAffineTransformScale(_mat, x, y);
    }
    
    AffineTransform rotate(cg::Angle const& ag)
    {
        return CGAffineTransformRotate(_mat, ag.rad());
    }
    
    static AffineTransform Translate(cg::Point const& pt)
    {
        return CGAffineTransformMakeTranslation(pt.x, pt.y);
    }
    
    static AffineTransform Scale(real x, real y = 1)
    {
        return CGAffineTransformMakeScale(x, y);
    }
    
    static AffineTransform Rotate(cg::Angle const& ag)
    {
        return CGAffineTransformMakeRotation(ag.rad());
    }
  
protected:
    
    CGAffineTransform _mat;
    
};

inline_impl AffineTransform Transform::affine() const
{
    return CATransform3DGetAffineTransform(_mat);
}

class TransformRect
{
    
public:
    
    TransformRect(CGTransformRect const& _rc)
    : _rect(_rc)
    {
        _update();
    }
    
    TransformRect(CGRect const& _rc, CGAffineTransform const& _af)
    {
        _rect.rect = _rc;
        _rect.transform = _af;
        
        _update();
    }
    
    operator CGTransformRect const& () const
    {
        _flush();
        return _rect;
    }
    
    CGFloat x() const
    {
        return _trect.rect.origin.x;
    }
    
    CGFloat y() const
    {
        return _trect.rect.origin.y;
    }
    
    CGFloat width() const
    {
        return _trect.rect.size.width;
    }
    
    CGFloat height() const
    {
        return _trect.rect.size.height;
    }
    
    TransformRect& set_x(CGFloat val)
    {
        _trect.rect.origin.x = val;
        _changed = true;
        return *this;
    }
    
    TransformRect& set_y(CGFloat val)
    {
        _trect.rect.origin.y = val;
        _changed = true;
        return *this;
    }
    
    TransformRect& set(Point const& pt)
    {
        _trect.rect.origin = pt;
        _changed = true;
        return *this;
    }
    
    TransformRect& set_width(CGFloat val)
    {
        _trect.rect.size.width = val;
        _changed = true;
        return *this;
    }
    
    TransformRect& set_height(CGFloat val)
    {
        _trect.rect.size.height = val;
        _changed = true;
        return *this;
    }
    
    TransformRect& set(Size const& sz)
    {
        _trect.rect.size = sz;
        _changed = true;
        return *this;
    }
    
    TransformRect& operator += (cg::Point const& pt)
    {
        _trect.rect.origin.x += pt.x;
        _trect.rect.origin.y += pt.y;
        _changed = true;
        return *this;
    }
    
    TransformRect& operator -= (cg::Point const& pt)
    {
        _trect.rect.origin.x -= pt.x;
        _trect.rect.origin.y -= pt.y;
        _changed = true;
        return *this;
    }
        
    TransformRect& operator += (cg::Size const& sz)
    {
        cg::Size tsz = sz * _rect.transform;
        _trect.rect.size.width += tsz.width();
        _trect.rect.size.height += tsz.height();
        _changed = true;
        return *this;
    }
    
    TransformRect& operator -= (cg::Size const& sz)
    {
        cg::Size tsz = sz * _rect.transform;
        _trect.rect.size.width -= tsz.width();
        _trect.rect.size.height -= tsz.height();
        _changed = true;
        return *this;
    }
        
protected:
    
    void _update()
    {
        _trect.transform = CGAffineTransformInvert(_rect.transform);
        _trect.rect = CGRectApplyAffineTransform(_rect.rect, _trect.transform);
        _changed = false;
    }
    
    void _flush()
    {
        if (_changed == false)
            return;
        
        _rect.rect = CGRectApplyAffineTransform(_trect.rect, _rect.transform);
        _changed = false;
    }
    
    void _flush() const
    {
        core::down_const(this)->_flush();
    }
    
    CGTransformRect _rect;
    CGTransformRect _trect;
    bool _changed;
    
};

inline_impl cg::Rect rand(cg::Rect rc)
{
    rc.set_x(rand01() * rc.width() + rc.x());
    rc.set_y(rand01() * rc.height() + rc.y());
    rc.set_width(rand01() * rc.width());
    rc.set_height(rand01() * rc.height());
    return rc;
}

NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif // objc

# endif
