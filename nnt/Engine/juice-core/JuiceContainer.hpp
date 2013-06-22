
# ifndef __JUICE_CONTAINER_441421825E764CABA28618BEC542B83A_H_INCLUDED
# define __JUICE_CONTAINER_441421825E764CABA28618BEC542B83A_H_INCLUDED

# include <vector>
# include <list>
# include <set>
# include <stack>
# include <deque>

JUICE_BEGIN

template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
class vector
: public ::std::vector<_Tp, _Alloc>
{
    
};

template <typename containerT, typename valueT>
inline_impl containerT& operator << (containerT& con, valueT& val)
{
    con.push_back(val);
    val->grab();
    return con;
}

template <typename valueT>
static void drop(valueT val)
{
    val->drop();
}

template <typename containerT>
inline_impl void clear(containerT& con)
{
    ::std::for_each(con.begin(), con.end(), drop<typename containerT::value_type>);
}

JUICE_END

# endif