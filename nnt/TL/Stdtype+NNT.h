
# ifndef __NNT_TL_STDTYPE_b7a514307d8d4159984abdb56c82d8fc_H_INCLUDED
# define __NNT_TL_STDTYPE_b7a514307d8d4159984abdb56c82d8fc_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNT_BEGIN_NS(cxx)

template <typename implT, typename valT>
class _BaseType
{
    typedef implT impl_type;

public:

    typedef valT value_type;

    _BaseType(value_type v = 0)
        : _val(v)
    {

    }

    impl_type& operator += (impl_type const& r)
    {
        _val += r._val;
        return _ref_impl();
    }

    impl_type operator + (impl_type const& r)
    {
        return _val + r._val;
    }

    impl_type& operator -= (impl_type const& r)
    {
        _val -= r._val;
        return _ref_impl();
    }

    impl_type operator - (impl_type const& r)
    {
        return _val - r._val;
    }

    impl_type& operator *= (impl_type const& r)
    {
        _val *= r._val;
        return _ref_impl();
    }

    impl_type operator * (impl_type const& r)
    {
        return _val * r._val;
    }

    impl_type& operator /= (impl_type const& r)
    {
        _val /= r._val;
        return _ref_impl();
    }

    impl_type operator / (impl_type const& r)
    {
        return _val / r._val;
    }

    impl_type& operator = (impl_type const& r)
    {
        _val = r._val;
        return _ref_impl();
    }

    bool operator == (impl_type const& r) const
    {
        return _val == r._val;
    }

    bool operator != (impl_type const& r) const
    {
        return _val != r._val;
    }

    operator value_type () const
    {
        return _val;
    }

    value_type* operator & ()
    {
        return (value_type*)this;
    }

    value_type const* operator & () const
    {
        return (value_type const*)this;
    }

protected:

    impl_type& _ref_impl()
    {
        return *(impl_type*)this;
    }

    value_type _val;

};

NNT_BEGIN_NS(impl)

template <typename implT, typename intT>
class number_t
    : public cxx::_BaseType<implT, intT>
{

};

NNT_END_NS

NNT_END_NS

class int_t
    : public cxx::impl::number_t<int_t, int>
{

};

class uint_t
    : public cxx::impl::number_t<uint_t, uint>
{

};

class long_t
    : public cxx::impl::number_t<long_t, long>
{

};

class ulong_t
    : public cxx::impl::number_t<ulong_t, ulong>
{

};

class longlong_t
    : public cxx::impl::number_t<longlong_t, longlong>
{

};

class ulonglong_t
    : public cxx::impl::number_t<ulonglong_t, ulonglong>
{

};

class float_t
    : public cxx::impl::number_t<float_t, float>
{

};

class double_t
    : public cxx::impl::number_t<double_t, double>
{

};

NNT_END_HEADER_CXX

# endif

# endif
