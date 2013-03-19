
# ifndef __JUICE_ALGO_B6988B0D29B3410CBBF6954C2E44E22A_H_INCLUDED
# define __JUICE_ALGO_B6988B0D29B3410CBBF6954C2E44E22A_H_INCLUDED

JUICE_BEGIN

template <typename vertex_type>
inline_impl vertex_type normal(vertex_type const& v0, vertex_type const& v1, vertex_type const& v2)
{
    vertex_type v01 = v1 - v0;
    vertex_type v02 = v2 - v0;
    vertex_type res = v01.cross(v02);
    res.normalize();
    return res;
}

template <typename valT>
inline_impl valT const* cast_pointer(valT const& v)
{
    return &v;
}

template <typename valT>
inline_impl valT* cast_pointer(valT& v)
{
    return &v;
}

template <typename valT>
inline_impl valT const* cast_pointer(valT const* v)
{
    return v;
}

template <typename valT>
inline_impl valT* cast_pointer(valT* v)
{
    return v;
}

JUICE_END

# endif