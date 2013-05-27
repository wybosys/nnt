
# ifndef __NNT_FOUNDATION_ITERATOR_fbd21ce0001a4b21b418996370d1d104_H_INCLUDED
# define __NNT_FOUNDATION_ITERATOR_fbd21ce0001a4b21b418996370d1d104_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

template <typename T>
inline void initial(T&)
{}

template <typename T>
inline void initial(T*& ptr)
{
    ptr = NULL;
}

template <typename lT, typename rT>
class pair
{
public:

    typedef lT first_type;
    typedef rT second_type;

    first_type first;
    second_type second;

};

template <typename lT, typename rT>
static pair<lT, rT> make_pair(lT const& l, rT const& r)
{
    pair<lT, rT> ret;
    ret.first = l;
    ret.second = r;
    return ret;
}

template <typename pairT>
static pairT make_pair(typename pairT::first_type const& l, typename pairT::second_type const& r)
{
    pairT ret;
    ret.first = l;
    ret.second = r;
    return ret;
}

NNT_TL_CLASS_HAS_FUNC(next, basic_iterator_check_next);
NNT_TL_CLASS_HAS_FUNC(previous, basic_iterator_check_previous);
NNT_TL_CLASS_HAS_FUNC(equal, basic_iterator_check_equal);

template <typename implT, typename>
class basic_iterator_has_next
{
};

template <typename implT>
class basic_iterator_has_next<implT, ntl::true_type>
{
public:

    implT& operator ++ ()
    {
        ((implT*)this)->obj = ntl::as_pointer(((implT*)this)->obj)->next();
        return *((implT*)this);
    }

    implT operator ++ (int)
    {
        implT ret = *(implT*)this;
        ++(*(implT*)this);
        return ret;
    }

};

template <typename implT, typename>
class basic_iterator_has_previous
{
};

template <typename implT>
class basic_iterator_has_previous<implT, ntl::false_type>
{
public:

    implT& operator -- ()
    {
        ((implT*)this)->obj = ntl::as_pointer(((implT*)this)->obj)->previous();
        return *((implT*)this);
    }

    implT operator -- (int)
    {
        implT ret = *(implT*)this;
        --(*(implT*)this);
        return ret;
    }

};

template <typename implT, typename>
class basic_iterator_has_equal
{
public:

    bool operator == (implT const& r) const
    {
        return ((implT*)this)->obj == r.obj;
    }

    bool operator != (implT const& r) const
    {
        return ((implT*)this)->obj != r.obj;
    }

};

template <typename implT>
class basic_iterator_has_equal<implT, ntl::true_type>
{
public:

    bool operator == (implT const& r) const
    {
        return ntl::as_pointer(((implT*)this)->obj)->equal(&r.obj);
    }

    bool operator != (implT const& r) const
    {
        return !ntl::as_pointer(((implT*)this)->obj)->equal(&r.obj);
    }

};

template <typename implT, typename objT,
typename objOT = typename ntl::cxx_type<objT>::type
>
class basic_iterator
    : public basic_iterator_has_next<implT, typename basic_iterator_check_next<objOT, objT (objOT::*)() >::type >,
    public basic_iterator_has_previous<implT, typename basic_iterator_check_previous<objOT, objT (objOT::*)() >::type >,
    public basic_iterator_has_equal<implT, typename basic_iterator_check_equal<objOT, bool (objOT::*)(objOT const*) const >::type >
{
public:

    typedef objT object_type;

    basic_iterator()
    {
        initial(obj);
    }

    static implT Instance(objT const& o)
    {
        implT ret;
        ret.obj = o;
        return ret;
    }

    static implT const& Nil()
    {
        static const implT iter_nil;
        return iter_nil;
    }

    basic_iterator& operator -- ();
    basic_iterator operator -- (int);    
    basic_iterator operator - (usize) const;

    objT obj;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
