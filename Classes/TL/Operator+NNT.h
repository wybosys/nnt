
# ifndef __NNT_WTL_OPERATOR_BA53114A3CBA4B6992CEC3B1F0FD7E97_H_INCLUDED
# define __NNT_WTL_OPERATOR_BA53114A3CBA4B6992CEC3B1F0FD7E97_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

template <typename valT>
class op_delete
{
public:

    void operator () (valT* ptr) const
    {
        delete ptr;
    }

};

template <typename valT>
static const op_delete<valT> delete_p();

template <typename valT>
class op_new
{
public:

    void operator () (valT*& ptr) const
    {
        ptr = new valT;
    }

};

template <typename valT>
static const op_new<valT> new_p();

template <typename valT>
class op_grab
{
public:
    void operator () (valT* ptr) const
    {
        ptr->grab();
    }
};

template <typename valT>
static const op_grab<valT> grab_p();

template <typename valT>
class op_drop
{
public:
    void operator () (valT*& ptr) const
    {
        if (ptr->drop())
            ptr = NULL;
    }
};

template <typename valT>
static const op_drop<valT> drop_p();

template <typename ConT>
struct op_push_back
{
    void operator () (ConT& con, typename ConT::value_type const& v) const
    {
        con.push_back(v);
    }
};

template <typename ConT>
struct op_insert
{
    void operator () (ConT& con, typename ConT::value_type const& v) const
    {
        con.insert(v);
    }
};

template <typename ValT>
inline_impl ValT const* up_const(ValT* p)
{
    return (ValT const*)p;
}

template <typename ValT>
inline_impl ValT const* up_const(ValT const* p)
{
    return (ValT const*)p;
}

template <typename valT>
inline_impl valT const& up_const(valT& o)
{
    return o;
}

template <typename valT>
inline_impl valT const& up_const(valT const& o)
{
    return o;
}

template <typename ValT>
inline_impl ValT* down_const(ValT* p)
{
    return p;
}

template <typename ValT>
inline_impl ValT* down_const(ValT const* p)
{
    return const_cast<ValT*>(p);
}

template <typename valT>
inline_impl valT& down_const(valT const& o)
{
    return *const_cast<valT*>(&o);
}

template <typename valT>
inline_impl valT& down_const(valT& o)
{
    return o;
}

template <typename valT>
inline_impl valT& ref(valT& o)
{
	return o;
}

template <typename valT>
inline_impl valT& ref(valT const& o)
{
	return down_const(o);
}

template <typename valT>
inline_impl bool between(valT const& v, valT const& l, valT const& r)
{
    return (l < v) && (r > v);
}

template <typename valT>
inline_impl bool between_le(valT const& v, valT const& l, valT const& r)
{
    return (l <= v) && (r > v);
}

template <typename valT>
inline_impl bool between_re(valT const& v, valT const& l, valT const& r)
{
    return (l < v) && (r >= v);
}

template <typename valT>
inline_impl bool between_e(valT const& v, valT const& l, valT const& r)
{
    return (l <= v) && (r >= v);
}

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
