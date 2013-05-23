
# ifndef __NNT_FOUNDATION_VECTOR_2ec73eaf6fd24c368faba28a3ac145f3_H_INCLUDED
# define __NNT_FOUNDATION_VECTOR_2ec73eaf6fd24c368faba28a3ac145f3_H_INCLUDED

# include "./iterator.hpp"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(foundation)

template <typename valT,
typename memT = ntl::alloc::Heap<valT>,
usize DEFAULT_CAPACITY = 4>
class vector
{
public:

    typedef valT value_type;

    vector()
        : _capacity(DEFAULT_CAPACITY), _cnt(0), _vals(NULL)
    {
        PASS;   
    }

    ~vector()
    {
        clear();
    }

    void clear()
    {
        delete [] _vals;
        _vals = NULL;
    }

    void reserve(usize sz)
    {
        if (_capacity >= val)
            return;

        if (_vals == NULL)
        {
            if (sz)
                _vals = new value_type[sz];
            else
                _vals = new value_type;
        }
        else
        {
            value_type* nvals = new value_type[sz];
            for (uint i = 0; i < _cnt; ++i)
                nvals[i] = _vals[i];
            clear();
            _vals = nvals;
        }

        _capacity = sz;
    }

    void push_back(value_type const& val)
    {
        bool extend = false;
        if (_capacity == _cnt && DEFAULT_CAPACITY)
        {
            _capacity += DEFAULT_CAPACITY;
            extend = true;
        }

        if (_vals == NULL)
        {
            if (_capacity)
                _vals = new value_type[_capacity];
            else
                _vals = new value_type;
        }
        else if (extend)
        {
            value_type* nvals = new value_type[_capacity];
            for (uint i = 0; i < _cnt; ++i)
                nvals[i] = _vals[i];
            clear();
            _vals = nvals;
        }

        value_type& inm = *(_vals + _cnt++);
        inm = val;
    }

    vector& operator << (value_type const& val)
    {
        push_back(val);
        return *this;
    }

    usize capacity() const
    {
        return _capacity;
    }

    usize size() const
    {
        return _cnt;
    }

    value_type& at(uindex idx)
    {
        return _vals[idx];
    }

    value_type const& at(uindex idx) const
    {
        return _vals[idx];
    }

    value_type& operator [] (uindex idx)
    {
        return _vals[idx];
    }

    value_type const& operator [] (uindex idx) const
    {
        return _vals[idx];
    }

protected:

    class _iter_value_type
    {
    public:

        _iter_value_type(value_type** v = NULL, usize o = 0)
            : vals(v), offset(o)
        {
            PASS;
        }

        _iter_value_type next()
        {
            return _iter_value_type(vals, ++offset);
        }

        _iter_value_type previous()
        {
            return _iter_value_type(vals, --offset);
        }

        bool equal(_iter_value_type const* r) const
        {
            return *vals == *r->vals && 
                offset == r->offset;
        }

        value_type **vals;
        usize offset;

    };

public:

    class iterator
        : public basic_iterator<iterator, _iter_value_type>
    {
    public:

        value_type& operator * ()
        {
            return *(*obj.vals + obj.offset);
        }

    };

    iterator begin()
    {
        iterator ret;
        ret.obj.vals = &_vals;
        return ret;
    }

    iterator end()
    {
        iterator ret;
        ret.obj.vals = &_vals;
        ret.obj.offset = _cnt;
        return ret;
    }

protected:

    value_type* _vals;
    usize _capacity, _cnt;    

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
