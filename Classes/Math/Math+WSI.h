
# ifndef __WSI_MATH_99CB3BD0A23F45378EC765DA4E2F242C_H_INCLUDED
# define __WSI_MATH_99CB3BD0A23F45378EC765DA4E2F242C_H_INCLUDED

WSI_BEGIN_HEADER_C

# ifdef REAL_IS_DOUBLE
#   define roundr     round
#   define cosr       cos
#   define sinr       sin
#   define sqrtr      sqrt
#   define tanr       tan
#   define atanr      atan
#   define atan2r     atan2
#   define powr       pow
# else
#   define roundr     roundf
#   define cosr       cosf
#   define sinr       sinf
#   define sqrtr      sqrtf
#   define tanr       tan
#   define atanr      atanf
#   define atan2r     atan2f
#   define powr       powf
# endif

# ifdef CGFLOAT_IS_DOUBLE
# if CGFLOAT_IS_DOUBLE
#   define cg_round     round
#   define cg_cos       cos
#   define cg_sin       sin
#   define cg_sqrt      sqrt
#   define cg_tan       tan
#   define cg_atan2     atan2
# else
#   define cg_round     roundf
#   define cg_cos       cosf
#   define cg_sin       sinf
#   define cg_sqrt      sqrtf
#   define cg_tan       tanf
#   define cg_atan2     atan2f
# endif
# endif

# define M_PI_360                0.00872664625997
# define M_2PI                   6.28318530717959
# define M_2PI_360               0.01745329251994
# define M_360_2PI               57.2957795130823
# define M_1_360                 0.00277777777778
# define M_1_2PI                 0.1591549430919
# define M_1_360_MUL_1_2PI       4.42097064144154e-4
# define M_1_360_MUL_PI_360      2.42406840554768e-5
# define M_3_2_PI                4.71238898038469

# ifndef M_1_PI
#   define M_1_PI                0.31830988618379
# endif

# define M_1_3                   0.33333333333333
# define M_1_7                   0.14285714285714
# define M_1_11                  0.09090909090909
# define M_1_13                  0.07692307692308
# define M_1_17                  0.05882352941176

# define M_COS_PI4               0.70710678118655
# define M_SIN_PI4               0.70710678118655
# define M_TAN_PI4               1

# define M_1_MINUS_COS_PI4       0.29289321881345
# define M_1_MINUS_SIN_PI4       0.29289321881345

# define M_1_60                  1.66666666666667e-2

# define ANGLE2RAD(angle)   ( (angle) * M_2PI_360 )
# define RAD2ANGLE(rad)     ( (rad) * M_360_2PI )

//! real compare.
# define real_equal(val, right, precise) (((val + precise) > right) && ((val - precise) < right))

// calc distance.
WSI_EXTERN real distance_points2d(real x0, real y0, real x1, real y1);

// value in region (-2PI, 2PI).
# define M_2PI_RESTRICT(val) ((val) - ((int)((val) * M_1_2PI) * M_2PI))
# define M_2PI_RESTRICT2(val) restrict_value(val, M_2PI, 0.0001f)

inline_impl real M_2PI_RESTRICT_P(real ang)
{
	double ret = ang;
    ret = M_2PI_RESTRICT(ret);
    if (ang < 0)
        ret += M_2PI;
    return (real)ret;
}

// ret in region [0, region].
WSI_EXTERN real restrict_value(real val, real region, real precise);

WSI_END_HEADER_C

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

template <typename valueT>
inline_impl valueT closure_region_value(valueT val, valueT reg)
{
    if (val > reg)
        return reg;
    if (val < -reg)
        return -reg;
    return val;
}

WSI_END_HEADER_CXX

# endif

# endif
