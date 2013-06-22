
# ifndef __NNT_MATH_STATISTIC_D341DB21870A4E169180A64643394A31_H_INCLUDED
# define __NNT_MATH_STATISTIC_D341DB21870A4E169180A64643394A31_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(stat)

template <typename valT, typename iterT>
struct sum
{
    valT operator () (iterT b, iterT const& e) const
    {
        valT ret;
        core::initial(ret);
        for (; b != e; ++b)
        {
            ret += *b;
        }
        return ret;
    }
    
    static const sum o;
};

template <typename valT, typename iterT>
const sum<valT, iterT> sum<valT, iterT>::o = sum();

template <typename valT, typename iterT>
struct deviation
{
    valT operator () (iterT b, iterT const& e) const
    {
        int dis = core::distance(b, e);
        valT u = sum<valT, iterT>::o(b, e);
        u /= dis;
        valT ret;
        core::initial(ret);
        for (; b != e; ++b)
        {
            valT d = *b - u;
            ret += d * d;
        }
        return ret / dis;
    }
    
    valT operator () (iterT b, iterT const& e, valT const& sum) const
    {
        int dis = core::distance(b, e);
        valT u = sum / dis;
        valT ret;
        core::initial(ret);
        for (; b != e; ++b)
        {
            valT d = *b - u;
            ret += d * d;
        }
        return ret / dis;
    }
    
    static const deviation o;
};

template <typename valT, typename iterT>
const deviation<valT, iterT> deviation<valT, iterT>::o = deviation();

template <typename valT, typename iterT>
struct deviation_standard
{
    valT operator () (iterT b, iterT const& e) const
    {
        valT u = sum<valT, iterT>::o(b, e);
        int dis = core::distance(b, e);
        u /= dis;
        valT ret;
        core::initial(ret);
        for (; b != e; ++b)
        {
            valT d = *b - u;
            ret += d * d;
        }
        return sqrt(ret / dis);
    }
    
    valT operator () (iterT b, iterT const& e, valT const& sum) const
    {
        int dis = core::distance(b, e);
        valT u = sum / dis;
        valT ret;
        core::initial(ret);
        for (; b != e; ++b)
        {
            valT d = *b - u;
            ret += d * d;
        }
        return sqrt(ret / dis);
    }
    
    static const deviation_standard o;
};

template <typename valT, typename iterT>
const deviation_standard<valT, iterT> deviation_standard<valT, iterT>::o = deviation_standard();

NNT_END_NS
NNT_END_HEADER_CXX

# endif
