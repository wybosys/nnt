
# ifndef __JUICE_TYPES_02E40398D458408D94B3B31FAF873F46_H_INCLUDED
# define __JUICE_TYPES_02E40398D458408D94B3B31FAF873F46_H_INCLUDED

# include "../../Math/Eigen/Dense.hpp"

JUICE_BEGIN

template <typename valT>
class ColorRGBA
{
public:
    typedef valT value_type;
    enum { COUNT = 4, SIZE = COUNT * sizeof(value_type) };    
    
    ColorRGBA(uint color)
    {
        r = AS_C32P(RGBA_RED(color));
        g = AS_C32P(RGBA_GREEN(color));
        b = AS_C32P(RGBA_BLUE(color));
        a = AS_C32P(RGBA_ALPHA(color)); 
    }
    
    ColorRGBA(value_type _r = 0, value_type _g = 0, value_type _b = 0, value_type _a = 1)
    : r(_r), g(_g), b(_b), a(_a)
    {
        PASS;
    }
    
    ColorRGBA(rgba_t const& _v)
    : r(_v.red()), g(_v.green()), b(_v.blue()), a(_v.alpha())
    {
        PASS;
    }
    
    ColorRGBA(argb_t const& _v)
    : r(_v.red()), g(_v.green()), b(_v.blue()), a(_v.alpha())
    {
        PASS;
    }
    
    void set(value_type _r, value_type _g, value_type _b, value_type _a = 1)
    {
        r = _r; 
        g = _g;
        b = _b;
        a = _a;
    }
    
    void set(uint color)
    {
        r = AS_C32P(RGBA_RED(color));
        g = AS_C32P(RGBA_GREEN(color));
        b = AS_C32P(RGBA_BLUE(color));
        a = AS_C32P(RGBA_ALPHA(color));  
    }
    
    value_type* data ()
    {
        return (value_type*)this;
    }
    
    value_type const* data () const
    {
        return (value_type const*)this;
    }
    
    operator value_type const* () const
    {
        return (value_type const*)this;
    }
    
    operator rgba_t* ()
    {
        return (rgba_t*)this;
    }
    
    operator rgba_t const* () const
    {
        return (rgba_t const*)this;
    }
    
    operator uint () const
    {
        return *((rgba_t const*)this);
    }
    
public:
    
    value_type r, g, b, a;
    
};

template <typename valueT>
class Vertex2d
{
    typedef Vertex2d<valueT> self_type;
    
public:
    typedef valueT value_type;
    enum { COUNT = 3, SIZE = COUNT * sizeof(value_type) };
    
    Vertex2d(value_type _x = 0, value_type _y = 0, value_type _w = 1)
    : x(_x), y(_y), w(_w)
    {
        PASS;
    }
        
    value_type* data()
    {
        return (value_type*)this;
    }
    
    value_type const* data() const
    {
        return (value_type const*)this;
    }
    
    ::std::string to_string() const
    {
        ::std::ostringstream ss;
        ss << x << " " << y << " " << w;
        return ss.str();
    }
    
public:
    
    value_type x, y, w;
    
};

template <typename valueT>
class Vertex3d
{
    typedef Vertex3d<valueT> self_type;
    typedef Eigen::Matrix<valueT, 3, 1> impl_type;
    
public:
    typedef valueT value_type;
    enum { COUNT = 4, SIZE = COUNT * sizeof(value_type) };
    
    Vertex3d(value_type _x = 0, value_type _y = 0, value_type _z = 0, value_type _w = 1)
    : x(_x), y(_y), z(_z), w(_w)
    {
        PASS;
    }
    
    value_type* data()
    {
        return (value_type*)this;
    }
    
    value_type const* data() const
    {
        return (value_type const*)this;
    }
    
    self_type operator - (self_type const& r) const
    {
        self_type ret = *this;
        return ret -= r;
    }
    
    self_type& operator -= (self_type const& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        return *this;
    }
    
    self_type cross(self_type const& r) const
    {
        impl_type* pl = (impl_type*)this->data();
        impl_type const* pr = (impl_type const*)r.data();
        impl_type res = pl->cross(*pr);
        return self_type(res(0), res(1), res(2));
    }
    
    self_type normal() const
    {
        impl_type* pl = (impl_type*)this->data();
        impl_type res = pl->norm();
        return self_type(res(0), res(1), res(2));
    }
    
    void normalize()
    {
        impl_type* pl = (impl_type*)this->data();
        pl->normalize();
    }
    
    ::std::string to_string() const
    {
        ::std::ostringstream ss;
        ss << x << " " << y << " " << z << " " << w;
        return ss.str();
    }
        
public:
    
    value_type x, y, z, w;
    
};

template <class valueT>
class Size2d
{
public:
    
    typedef valueT value_type;
    
    enum { COUNT = 2, SIZE = COUNT * sizeof(value_type) };
        
    Size2d(value_type _w = 0, value_type _h = 0)
    : w(_w), h(_h)
    {
        PASS;
    }
    
public:
    value_type w, h;
};

template <class valueT>
class Size3d
: public Size2d<valueT>
{
    typedef Size2d<valueT> super_type;
    typedef Size3d<valueT> self_type;
    
public:
    
    typedef valueT value_type;
    
    enum { COUNT = 3, SIZE = COUNT * sizeof(value_type) };    
    
    Size3d(value_type _w = 0, value_type _h = 0, value_type _d = 0)
    : super_type(_w, _h),
    d(_d)
    {
        PASS;
    }
    
public:
    value_type d;
};

template <typename vertexT, typename sizeT,
uint dim = sizeT::COUNT
>
class Rect
{
public:
    typedef vertexT vertex_type;
    typedef sizeT size_type;
    vertex_type origin;
    size_type size;
};

template <typename vertexT, typename sizeT>
class Rect<vertexT, sizeT, 2>
{
public:
    
    typedef typename vertexT::value_type value_type;    
    typedef vertexT vertex_type;            
    typedef sizeT size_type;
    
    vertex_type center() const
    {
        vertex_type pt = origin;
        pt.x += size.w * .5f;
        pt.y += size.h * .5f;
        return pt;
    }
    
    vertex_type origin;
    size_type size;
    
};

template <class valueT>
class Box2d
: public Vertex2d<valueT>
{
    typedef Vertex2d<valueT> super_type;
    typedef Box2d<valueT> self_type;
    
public:
    typedef valueT value_type;
    
    Box2d()
    {
        PASS;
    }
    
    Box2d(Size2d<value_type> const& sz)
    : size(sz)
    {
        PASS;
    }
    
    Box2d(Vertex2d<value_type> const& pos, Size2d<value_type> const& sz)
    : super_type(pos),
    size(sz)
    {
        PASS;
    }
    
public:
    
    Size2d<value_type> size;
    
};

template <class valueT>
class Box3d
: public Vertex3d<valueT>
{
    typedef Vertex3d<valueT> super_type;
    typedef Vertex3d<valueT> self_type;
    
public:
    typedef valueT value_type;
    
    Box3d()
    {
        PASS;
    }
    
    Box3d(Size3d<value_type> const& sz)
    : size(sz)
    {
        PASS;
    }
    
    Box3d(Vertex3d<value_type> const& pos, Size3d<value_type> const& sz)
    : super_type(pos),
    size(sz)
    {
        PASS;
    }
    
public:
    
    Size3d<value_type> size;
    
};

template <class vertexT>
class Triangle3d
{
public:
    typedef vertexT vertex_type;
    
    Triangle3d()
    {
        PASS;
    }
    
    Triangle3d(vertex_type const& v0, vertex_type const& v1, vertex_type const& v2)
    {
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
    }
    
    vertex_type normal()
    {
        vertex_type v01 = vertices[1] - vertices[0];
        vertex_type v02 = vertices[2] - vertices[0];
        vertex_type res = v01.cross(v02);
        res.normalize();
        return res;
    }
    
public:
    
    vertex_type vertices[3];
    
};

typedef struct {} empty_axises3d_type;
typedef struct {} empty_axises2d_type;

template <typename valT>
class Matrix3d
{
    typedef Eigen::Matrix<valT, 4, 4> impl_type;
    typedef Matrix3d<valT> self_type;
    
public:
    
    typedef valT value_type;
    typedef Vertex3d<value_type> vertex_type;
    typedef empty_axises3d_type empty_type;
    
    void set_scale(value_type _x, value_type _y, value_type _z, value_type _w = 1)
    {
        impl_type mat;
        mat << 
        _x, 0, 0, 0,
        0, _y, 0, 0,
        0, 0, _z, 0,
        0, 0, 0, _w;
        _mat = _mat * mat;
    }
    
    void set_scale(value_type _p)
    {
        _mat(3, 3) *= 1 / _p;
    }
    
    void set_translate(value_type _x, value_type _y, value_type _z, value_type _w = 1)
    {
        impl_type mat;
        mat <<
        1, 0, 0, _x, 
        0, 1, 0, _y,
        0, 0, 1, _z,
        0, 0, 0, _w;
        
        _mat = _mat * mat;
    }
    
    template <typename vecT>
    void set_translate(vecT const& vec)
    {
        set_translate(vec.x, vec.y, vec.z);
    }
    
    void set_rotate(real angle, value_type _x, value_type _y, value_type _z)
    {
        real c = cos(angle);
        real s = sin(angle);
        real _1c = 1 - c;
        value_type _xx = _x * _x, _yy = _y * _y, _zz = _z * _z;
        value_type _xy = _x * _y, _xz = _x * _z, _yz = _y * _z;
        value_type _sx = s * _x, _sy = s * _y, _sz = s * _z;
        value_type _1c_xx = _1c * _xx, _1c_yy = _1c * _yy, _1c_zz = _1c * _zz;
        value_type _1c_xy = _1c * _xy, _1c_xz = _1c * _xz, _1c_yz = _1c * _yz;
        
        impl_type mat;
        mat << 
        _1c_xx + c,   _1c_xy - _sz, _1c_xz + _sy, 0,
        _1c_xy + _sz, _1c_yy + c,   _1c_yz - _sx, 0,
        _1c_xz - _sy, _1c_yz + _sx, _1c_zz + c,   0,
        0, 0, 0, 1;
        
        _mat = _mat * mat;
    }
    
    void set_inverse()
    {
        _mat = _mat.inverse().eval();
    }
    
    self_type inverse() const
    {
        self_type ret = *this;
        ret.set_inverse();
        return ret;
    }
    
    void set_identity()
    {
        _mat.setIdentity();
    }
    
    value_type* data()
    {
        return _mat.data();
    }
    
    value_type const* data() const
    {
        return _mat.data();
    }
    
    value_type& operator () (uindex r, uindex c)
    {
        return _mat(r, c);
    }
    
    value_type const& operator () (uindex r, uindex c) const
    {
        return _mat(r, c);
    }
    
    ::nnt::core::string to_string() const
    {
        ::nnt::core::stringstream ss;
        ss << _mat;
        return ss.str();
    }
    
    self_type& operator *= (self_type const& r)
    {
        _mat *= r._mat;
        return *this;
    }
    
    self_type operator * (self_type const& r) const
    {
        self_type ret = *this;
        ret *= r;
        return ret;
    }
    
    vertex_type operator * (vertex_type const& vex) const
    {
        vertex_type ret;
        typedef Eigen::Matrix<value_type, 4, 1> impl_vex_type;
        impl_vex_type* impl_vex = (impl_vex_type*)vex.data();
        impl_vex_type res = _mat * *impl_vex;
        ret.x = res[0];
        ret.y = res[1];
        ret.z = res[2];
        ret.w = res[3];
        return ret;
    }
    
protected:
    
    impl_type _mat;
    
};

template <typename vertexT>
class BoundingBox
{
    typedef BoundingBox<vertexT> self_type;
    
public:
    
    enum {
        FRONT_LEFT_TOP = 0,
        FRONT_RIGHT_TOP = 1,
        FRONT_RIGHT_BOTTOM = 2,
        FRONT_LEFT_BOTTOM = 3,
        BACK_LEFT_TOP = 4,
        BACK_RIGHT_TOP = 5,
        BACK_RIGHT_BOTTOM = 6,
        BACK_LEFT_BOTTOM = 7,
    };
    
    typedef vertexT vertex_type;
    
    void reset()
    {
        vertex_type origin;
        for (uint i = 0; i < 8; ++i)
            pts[i] = origin;
    }
    
    void add(vertex_type const& vex)
    {
        if (vex.x < pts[FRONT_LEFT_TOP].x)
        {
            pts[FRONT_LEFT_TOP].x = pts[FRONT_LEFT_BOTTOM].x = pts[BACK_LEFT_TOP].x = pts[BACK_LEFT_BOTTOM].x = vex.x;
        }
        else if (vex.x > pts[FRONT_RIGHT_TOP].x)
        {
            pts[FRONT_RIGHT_TOP].x = pts[FRONT_RIGHT_BOTTOM].x = pts[BACK_RIGHT_TOP].x = pts[BACK_RIGHT_BOTTOM].x = vex.x;
        }
        
        if (vex.y > pts[FRONT_LEFT_TOP].y)
        {
            pts[FRONT_LEFT_TOP].y = pts[FRONT_RIGHT_TOP].y = pts[BACK_LEFT_TOP].y = pts[BACK_RIGHT_TOP].y = vex.y;
        }
        else if (vex.y < pts[FRONT_LEFT_BOTTOM].y)
        {
            pts[FRONT_LEFT_BOTTOM].y = pts[FRONT_RIGHT_BOTTOM].y = pts[BACK_LEFT_BOTTOM].y = pts[BACK_RIGHT_BOTTOM].y = vex.y;
        }
        
        if (vex.z > pts[FRONT_LEFT_TOP].z)
        {
            pts[FRONT_LEFT_TOP].z = pts[FRONT_RIGHT_BOTTOM].z = pts[FRONT_LEFT_BOTTOM].z = pts[FRONT_RIGHT_BOTTOM].z = vex.z;
        }
        else if (vex.z < pts[BACK_LEFT_TOP].z)
        {
            pts[BACK_LEFT_TOP].z = pts[BACK_RIGHT_BOTTOM].z = pts[BACK_LEFT_BOTTOM].z = pts[BACK_RIGHT_BOTTOM].z = vex.z;
        }
    }
    
    void add(self_type const& r)
    {
        if (r.pts[FRONT_LEFT_TOP].x < pts[FRONT_LEFT_TOP].x)
        {
            pts[FRONT_LEFT_TOP].x = pts[FRONT_LEFT_BOTTOM].x = pts[BACK_LEFT_TOP].x = pts[BACK_LEFT_BOTTOM].x = r.pts[FRONT_LEFT_TOP].x;
        }
        else if (r.pts[FRONT_RIGHT_TOP].x > pts[FRONT_RIGHT_TOP].x)
        {
            pts[FRONT_RIGHT_TOP].x = pts[FRONT_RIGHT_BOTTOM].x = pts[BACK_RIGHT_TOP].x = pts[BACK_RIGHT_BOTTOM].x = r.pts[FRONT_RIGHT_TOP].x;
        }
        
        if (r.pts[FRONT_LEFT_TOP].y > pts[FRONT_LEFT_TOP].y)
        {
            pts[FRONT_LEFT_TOP].y = pts[FRONT_RIGHT_TOP].y = pts[BACK_LEFT_TOP].y = pts[BACK_RIGHT_TOP].y = r.pts[FRONT_LEFT_TOP].y;
        }
        else if (r.pts[FRONT_LEFT_BOTTOM].y < pts[FRONT_LEFT_BOTTOM].y)
        {
            pts[FRONT_LEFT_BOTTOM].y = pts[FRONT_RIGHT_BOTTOM].y = pts[BACK_LEFT_BOTTOM].y = pts[BACK_RIGHT_BOTTOM].y = r.pts[FRONT_LEFT_BOTTOM].y;
        }
        
        if (r.pts[FRONT_LEFT_TOP].z > pts[FRONT_LEFT_TOP].z)
        {
            pts[FRONT_LEFT_TOP].z = pts[FRONT_RIGHT_BOTTOM].z = pts[FRONT_LEFT_BOTTOM].z = pts[FRONT_RIGHT_BOTTOM].z = r.pts[FRONT_LEFT_TOP].z;
        }
        else if (r.pts[BACK_LEFT_TOP].z < pts[BACK_LEFT_TOP].z)
        {
            pts[BACK_LEFT_TOP].z = pts[BACK_RIGHT_BOTTOM].z = pts[BACK_LEFT_BOTTOM].z = pts[BACK_RIGHT_BOTTOM].z = r.pts[BACK_LEFT_TOP].z;
        }
    }
    
public:
    
    vertex_type pts[8];
    
};

template <typename vertexT>
class Line
{
    typedef Line<vertexT> self_type;
    
public:
    typedef vertexT vertex_type;
    
    self_type* clone() const
    {
        self_type* ret = new self_type;
        ret->start = this->start;
        ret->end = this->end;
        return ret;
    }
    
    template <typename matrixT>
    self_type& operator *= (matrixT const& mat)
    {
        start = mat * start;
        end = mat * start;
        return *this;
    }
  
    vertex_type start, end;
    
};

template <typename matrixT>
class Orthogonal
{
public:
    typedef matrixT matrix_type;
    
    Orthogonal(real n, real f, real l, real r, real t, real b)
    {
        mat.set_identity();        
        
        real r_l = r - l;
        real t_b = t - b;
        real f_n = f - n;
        
        if (r_l == 0 || t_b == 0 || f_n == 0)
            return;
        
        real rl = r + l;
        real tb = t + b;
        real fn = f + n;
        real _1_r_l = 1 / r_l;
        real _1_t_b = 1 / t_b;
        real _1_f_n = 1 / f_n;
        
        mat(0, 0) = _1_r_l + _1_r_l;
        mat(1, 1) = _1_t_b + _1_t_b;
        mat(2, 2) = _1_f_n + _1_f_n;
        
        mat(0, 3) = - (rl * _1_r_l);
        mat(1, 3) = - (tb * _1_t_b);
        mat(2, 3) = -fn * _1_f_n;
    }
    
    matrix_type mat;
    
};

template <typename matrixT>
class Frustum
{
public:
    typedef matrixT matrix_type;
    
    Frustum(real angle, real n, real f, real l, real r, real t, real b)
    {
        mat.set_identity();
                                
        real r_l = r - l;
        real f_n = f - n;
        real t_b = t - b;
        
        if (r_l == 0 || f_n == 0 || t_b == 0)
            return;                
        
        real fn = f + n;
        real rl = r + l;
        real tb = t + b;
        real _1_f_n = 1 / f_n;
        real _1_r_l = 1 / r_l;
        real _1_t_b = 1 / t_b;
        
        mat(0, 0) = 2 * n * _1_r_l;
        mat(1, 1) = 2 * n * _1_t_b;
        mat(2, 2) = - fn * _1_f_n;
        mat(3, 3) = 0;
        
        mat(0, 2) = rl * _1_r_l;
        mat(1, 2) = tb * _1_t_b;
        mat(2, 3) = -2 * f * n * _1_f_n;
        mat(3, 2) = -1;    
        
        // after make perspective matrix, translate the matrix for contain the target.
        real center = (f - n) * .5f + n;        
        real ratio = f / center;
        mat.set_translate(0, 0, -center);
        mat.set_scale(ratio, ratio, ratio);
    }
    
    matrix_type mat;
    
};

JUICE_END

# endif
