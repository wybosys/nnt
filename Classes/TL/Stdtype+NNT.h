
# ifndef __NNT_TL_STDTYPE_b7a514307d8d4159984abdb56c82d8fc_H_INCLUDED
# define __NNT_TL_STDTYPE_b7a514307d8d4159984abdb56c82d8fc_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNT_BEGIN_NS(ntl)

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
    : public _BaseType<implT, intT>
{

};

template <typename valT>
class mask_t
{
public:

    mask_t(valT v = 0)
        : _val(v)
    {

    }

    template <typename posT>
    bool checked() const
    {
        return ((0x1 << posT::VALUE) & _val) != 0;
    }

    template <typename posT>
    mask_t& on()
    {
        _val |= 0x1 << posT::VALUE;
        return*this;
    }

    template <typename posT>
    mask_t& off()
    {
        _val &= ~(0x1 << posT::VALUE);
        return *this;
    }

    template <typename posT>
    mask_t& toggle()
    {
        _val ^= 0x1 << posT::VALUE;
        return *this;
    }

    template <typename posT>
    mask_t& set(bool val)
    {
        if (val)
            on<posT>();
        else
            off<posT>();
        return *this;
    }

    void set(valT val)
    {
        MASK_SET(val, _val);
    }

    void unset(valT val)
    {
        MASK_UNSET(val, _val);
    }

    bool checked(valT val)
    {
        return MASK_CHECK(val, _val);
    }

    mask_t& operator = (mask_t const& r)
    {
        _val = r._val;
        return *this;
    }

    bool operator == (mask_t const& r) const
    {
        return _val == r._val;
    }

    bool operator != (mask_t const& r) const
    {
        return _val != r._val;
    }

protected:

    valT _val;

};

NNT_END_NS

NNT_BEGIN_NS(mpl)

template <ubyte valT>
class position
{
public:

    enum { VALUE = valT };

    operator ubyte () const
    {
        return VALUE;
    }

    template <typename R>
    struct add
    {
        typedef position<VALUE + R::VALUE> type;
        enum { VALUE = type::VALUE };
    };

    template <typename R>
    struct sub
    {
        typedef position<VALUE - R::VALUE> type;
        enum { VALUE = type::VALUE };
    };

    template <typename R>
    struct mul
    {
        typedef position<VALUE * R::VALUE> type;
        enum { VALUE = type::VALUE };
    };

    template <typename R>
    struct div
    {
        typedef position<VALUE / R::VALUE> type;
        enum { VALUE = type::VALUE };
    };

};

NNT_END_NS

NNT_END_NS

typedef ntl::impl::mask_t<uint> mask32_t;
typedef ntl::impl::mask_t<ulonglong> mask64_t;

# ifdef NNT_X32
typedef mask32_t mask_t;
# else
typedef mask64_t mask_t;
# endif

class int_t
    : public ntl::impl::number_t<int_t, int>
{

};

class uint_t
    : public ntl::impl::number_t<uint_t, uint>
{

};

class long_t
    : public ntl::impl::number_t<long_t, long>
{

};

class ulong_t
    : public ntl::impl::number_t<ulong_t, ulong>
{

};

class longlong_t
    : public ntl::impl::number_t<longlong_t, longlong>
{

};

class ulonglong_t
    : public ntl::impl::number_t<ulonglong_t, ulonglong>
{

};

class float_t
    : public ntl::impl::number_t<float_t, float>
{

};

class double_t
    : public ntl::impl::number_t<double_t, double>
{

};

NNT_END_HEADER_CXX

# endif

# endif
