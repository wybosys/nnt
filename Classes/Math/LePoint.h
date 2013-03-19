
# ifndef __NNTMATH_POINT_94F09D7041034A179A65AAA181622AB1_H_INCLUDED
# define __NNTMATH_POINT_94F09D7041034A179A65AAA181622AB1_H_INCLUDED

# include "Math+NNT.h"

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

template <typename valT, uint dim>
class Point
{
public:
    
    typedef valT value_type;
    
    template <typename otherT>
    operator otherT const& () const
    {
        return *(otherT const*)(void const*)this;
    }
    
    static const Point<valT, dim> Zero;
};

template <typename valT, uint dim>
const Point<valT, dim> Point<valT, dim>::Zero = Point<valT, dim>();

template <typename valT>
class Point <valT, 1>
: public Point <valT, 0>
{
    typedef Point <valT, 0> super;
    typedef Point <valT, 1> self_type;
    
public:
    
    typedef typename super::value_type value_type;
    
    Point(value_type const& _x = 0)
    : x(_x)
    {
        PASS;
    }
    
    self_type& operator += (self_type const& r)
    {
        x += r.x;
        return *this;
    }
    
    self_type& operator -= (self_type const& r)
    {
        x -= r.x;
        return *this;
    }
    
    value_type x;
    
    static const Point<valT, 1> Zero;
};

template <typename valT>
const Point<valT, 1> Point<valT, 1>::Zero = Point<valT, 1>();

template <typename valT>
class Point <valT, 2>
: public Point <valT, 1>
{
    typedef Point <valT, 1> super;
    typedef Point <valT, 2> self_type;
    
public:
    
    typedef typename super::value_type value_type;
    
    Point(value_type const& _x = 0, value_type const& _y = 0)
    : super(_x), y(_y)
    {
        PASS;
    }
    
    template <typename T>
    Point(T const& r)
    : super(r.x), y(r.y)
    {
        PASS;
    }
    
    value_type length_sq() const
    {
        return super::x*super::x + y*y;
    }
    
    value_type length() const
    {
        return sqrt(super::x*super::x + y*y);
    }
    
    self_type& operator += (self_type const& r)
    {
        super::x += r.x;
        y += r.y;
        return *this;
    }
    
    self_type operator + (self_type const& r) const
    {
        self_type ret = *this;
        return ret += r;
    }
    
    self_type& operator -= (self_type const& r)
    {
        super::x -= r.x;
        y -= r.y;
        return *this;
    }
    
    self_type operator - (self_type const& r) const
    {
        self_type ret = *this;
        return ret -= r;
    }
    
    real angle() const
    {
        real ret = atan2(y, super::x);
        if (ret < 0)
            ret += M_2PI;
        return ret;
    }

    value_type y;
    
    static const Point<valT, 2> Zero;
};

template <typename valT>
const Point<valT, 2> Point<valT, 2>::Zero = Point<valT, 2>();

template <typename valT>
class Point <valT, 3>
: public Point <valT, 2>
{
    typedef Point <valT, 2> super;
    
public:
    
    typedef typename super::value_type value_type;
    
    Point(value_type const& _x = 0, value_type const& _y = 0, value_type const& _z = 0)
    : super(_x, _y), z(_z)
    {
        PASS;
    }

    value_type z;
    
    static const Point<valT, 3> Zero;
};

template <typename valT>
const Point<valT, 3> Point<valT, 3>::Zero = Point<valT, 3>();

NNT_END_HEADER_CXX

# endif

# endif
