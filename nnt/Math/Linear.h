
# ifndef __NNT_MATH_LINEAR_E0F2D3C94F2944D0A8685A19250BE43E_H_INCLUDED
# define __NNT_MATH_LINEAR_E0F2D3C94F2944D0A8685A19250BE43E_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

//! line.
typedef struct _CGLine {
    CGPoint start;
    CGPoint end;
    BOOL isValid;
    BOOL isSegment;
    BOOL isRadial;
} CGLine;

//! rect lines.
typedef struct _CGRectLines {
    CGLine t, l, r, b;
} CGRectLines;

//! line close precision.
static const real kLinearPrecision = .01f;

//! rect intersect.
CGLine CGRectIntersect(CGRect const* rect, CGLine const*);

//! line intersect.
BOOL CGLineIsIntersect(CGLine const*, CGLine const*);

//! line is hov.
BOOL CGLineIsHov(CGLine const*);

//! line is vec.
BOOL CGLineIsVec(CGLine const*);

//! is point on line.
BOOL CGLineIsPointInPrec(CGLine const*, CGPoint const*, real prec);

//! is point in line,
BOOL CGLineIsPointIn(CGLine const*, CGPoint const*);

//! calc k of line.
real CGLineK(CGLine const*);

//! length of line.
real CGLineLength(CGLine const*);

//! q-length of line.
real CGLineLengthQ(CGLine const*);

//! line intersect.
CGPoint CGLineIntersect(CGLine const *src, CGLine const *des);

//! get lines from rect.
CGRectLines CGRectGetLines(CGRect const*);

//! rotate line.
CGLine CGLineRotate(CGLine const*, real rad);

//! get line center point.
CGPoint CGLineCenter(CGLine const*);

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# include "LePoint.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(math)
NNT_BEGIN_NS(linear)

template <typename valT,
uint DIM,
typename pointT = Point<valT, DIM> >
class Line
{
public:
    
};

template <typename valT,
typename pointT>
class Line <valT, 2, pointT>
{
public:
    
    typedef valT value_type;
    typedef pointT point_type;
    typedef Point<valT, 2> mathpoint_type;
    
    Line()
    {
        PASS;
    }
    
    Line(point_type const& _s, point_type const& _e)
    : s(_s), e(_e)
    {
        PASS;
    }
    
    mathpoint_type vector() const
    {
        return mathpoint_type(e) - mathpoint_type(s);
    }
    
    real length_sq() const
    {
        return vector().length_sq();
    }
    
    real length() const
    {
        return vector().length();
    }
    
    real angle() const
    {
        return vector().angle();
    }
    
    point_type s, e; // start, end.
    
};

template <typename valT = real,
typename pointT = Point<valT, 2> >
class Circle
{
public:
    
    typedef valT value_type;
    typedef pointT point_type;
    
    Circle()
    {
        PASS;
    }
    
    Circle(value_type _r, point_type const& _center)
    : radius(_r), center(_center)
    {
        PASS;
    }
    
    point_type at_angle(real angle) const
    {
        point_type ret;
        ret.x = center.x + cos(angle) * radius;
        ret.y = center.y + sin(angle) * radius;
        return ret;
    }
    
    typedef Line<value_type, 2, point_type> line_type;
        
    value_type radius;
    point_type center;
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
