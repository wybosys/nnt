
# ifndef __NNT_WTL_DATA_1CE93526D82B4B69A7106EF4E31C96F8_H_INCLUDED
# define __NNT_WTL_DATA_1CE93526D82B4B69A7106EF4E31C96F8_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

template <typename _Tp>
class _base_data
{
    typedef _base_data<_Tp> self_type;
    
protected:
    
    template <typename value_type>
    class _iterator
    {
        typedef _iterator<value_type> self_type;
        
    public:
        
        _iterator(value_type* b)
        : _begin(b)
        {
            PASS;
        }
        
        _iterator(self_type const& r)
        : _begin(r._begin)
        {
            PASS;
        }
        
        bool operator == (self_type const& r)
        {
            return _begin == r._begin;
        }
        
        bool operator != (self_type const& r)
        {
            return _begin != r._begin;
        }
        
        self_type& operator ++ ()
        {
            ++_begin;
            return *this;
        }
        
        self_type operator ++ (int) const
        {
            self_type ret = *this;
            return ++ret;
        }
        
        self_type& operator -- ()
        {
            --_begin;
            return *this;
        }
        
        self_type operator -- (int) const
        {
            self_type ret = *this;
            return --ret;
        }
        
        self_type& operator += (usize off)
        {
            _begin += off;
            return *this;
        }
        
        self_type operator + (usize off) const
        {
            self_type ret = *this;
            return ret += off;
        }
        
        self_type& operator -= (usize off)
        {
            _begin += off;
            return *this;
        }
        
        self_type operator - (usize off) const
        {
            self_type ret = *this;
            return ret += off;
        }
        
        usize operator - (self_type const& r) const
        {
            return _begin - r._begin;
        }
        
        value_type& operator * ()
        {
            return *_begin;
        }
        
        value_type* operator -> ()
        {
            return &(*_begin);
        }
        
        value_type* pointer() const
        {
            return (value_type*)_begin;
        }
        
    protected:
        
        value_type *_begin;
        
    };
    
public:

    typedef _Tp value_type;
    typedef value_type const* const_pointer;
    typedef value_type * pointer;
    typedef _iterator<value_type> iterator;
    typedef _iterator<value_type const> const_iterator;
    
    _base_data()
    : _da(NULL), _dl(0), _nrelease(false)
    {
        PASS;
    }
    
    _base_data(usize length)
    : _dl(length), _nrelease(true)
    {
        _da = (pointer)malloc(length * sizeof(value_type));
    }
    
    _base_data(value_type const* d, usize l)
    : _da((pointer)d), _dl(l), _nrelease(false)
    {        
        PASS;
    }
    
    _base_data(const value_type d[])
    : _da((pointer)d), _dl(sizeof(d)), _nrelease(false)
    {
        PASS;
    }
    
    _base_data(value_type const* d, usize l, _bool_copy cpy)
    : _da(NULL), _dl(0), _nrelease(false)
    {        
        if (cpy == ntl::copy)
        {
            this->duplicate((void*)d, l);
        }
        else
        {
            this->_da = (value_type*)d;
            this->_dl = l;
            this->_nrelease = false;   
        }
    }
    
    _base_data(value_type const* d, usize l, usize ext)
    : _da(NULL), _dl(0), _nrelease(false)
    {        
        this->_da = (value_type*)malloc((l + ext) * sizeof(value_type));
        memcpy((void*)this->_da, d, l * sizeof(value_type));
        memset((void*)(this->_da + l * sizeof(value_type)), 0, ext * sizeof(value_type));
        this->_dl = l + ext;
        this->_nrelease = true;
    }
    
    _base_data(iterator const& b, iterator const& end, _bool_copy cpy)
    {
        void* d = (void*)b.pointer();
        usize l = end - b;
        if (cpy == ntl::copy)
        {
            this->duplicate((void*)d, l);
        }
        else
        {
            this->_da = (value_type*)d;
            this->_dl = l;
            this->_nrelease = false;   
        }
    }
    
    _base_data(const_iterator const& b, const_iterator const& end, _bool_copy cpy)
    {
        void* d = (void*)b.pointer();
        usize l = end - b;
        if (cpy == ntl::copy)
        {
            this->duplicate((void*)d, l);
        }
        else
        {
            this->_da = (value_type*)d;
            this->_dl = l;
            this->_nrelease = false;   
        }
    }
    
    _base_data(self_type const& r)
    : _da(NULL), _dl(0), _nrelease(false)
    {        
        *this = r;
    }
    
    self_type& operator = (self_type const& r)
    {
        this->clear();
        
        if (r._nrelease)
        {
            this->duplicate(r._da, r._dl);
        }
        else
        {
            this->_da = r._da;
            this->_dl = r._dl;
            this->_nrelease = false;
        }
        
        return *this;
    }
    
    ~_base_data()
    {
        clear();
    }
    
    void clear()
    {
        if (_nrelease)
        {
            ::free((void*)_da);
            _da = NULL;
            _dl = 0;
            _nrelease = false;
        }
    }
    
    void duplicate(void const* d, usize l)
    {
        clear();

        this->_da = (value_type*)malloc(l * sizeof(value_type));
        memcpy((void*)this->_da, d, l * sizeof(value_type));
        this->_dl = l;
        this->_nrelease = true;
    }

    usize copy(void const* d, usize l)
    {
        usize tgtsz = l;
        if (this->_dl < l)
            tgtsz = this->_dl;
        if (tgtsz == 0)
            return 0;
        memcpy((void*)this->_da, d, tgtsz * sizeof(value_type));
        return tgtsz;
    }

    usize copy(self_type const& r)
    {
        return this->copy(r._da, r._dl);
    }

    void alloc(usize l)
    {
		clear();
        this->_da = (value_type*)malloc(l * sizeof(value_type));
        this->_dl = l;
        this->_nrelease = true;
    }
    
    void append(self_type const& r)
    {
        this->append(r._da, r._dl);
    }
    
    template <typename valT>
    void append(valT const& obj)
    {
        this->append((void*)&obj, (usize)sizeof(obj));
    }

    void append(core::string const& str)
    {
        append((void*)str.c_str(), str.length());
    }    

    void append(char const* str)
    {
        append((void*)str, strlen(str));
    }
    
    void append(void* d, usize l)
    {
        if (l == 0)
            return;
        
        usize nsz = this->_dl + l;
        value_type* da = (value_type*)malloc(nsz * sizeof(value_type));
        if (this->_dl)
            memcpy(da, this->_da, this->_dl * sizeof(value_type));
        memcpy(da + this->_dl * sizeof(value_type), d, l * sizeof(value_type));
        
        // clear.
        this->clear();
        
        // set
        this->_da = da;
        this->_dl = nsz;
        this->_nrelease = true;
    }
    
    byte operator [] (uindex idx) const
    {
        return this->bytes()[idx];
    }
    
    byte& operator [] (uindex idx)
    {
        return *((byte*)_da + idx);
    }
    
    byte* bytes() const
    {
        return (byte*)(byte const*)_da;
    }
    
    char const* c_str() const
    {
        return (char const*)_da;
    }
        
    usize length() const
    {
        return _dl;
    }
    
    usize size() const
    {
        return _dl;
    }
    
    void set_length(usize l)
    {
        _dl = l;
    }
    
    bool operator == (self_type const& r) const
    {
        if (_dl != r._dl)
            return false;
        return ::memcmp(_da, r._da, _dl * sizeof(value_type)) == 0;
    }
    
    bool operator != (self_type const& r) const
    {
        if (_dl != r._dl)
            return true;
        return ::memcmp(_da, r._da, _dl * sizeof(value_type)) != 0;
    }
    
    iterator begin()
    {
        return iterator(_da);
    }
    
    const_iterator begin() const
    {
        return const_iterator(_da);
    }
    
    iterator end()
    {
        return iterator(_da + _dl);
    }
    
    const_iterator end() const
    {
        return const_iterator(_da + _dl);
    }
    
    template <typename valT>
    operator valT const& () const
    {
        return *(valT const*)_da;
    }
    
    operator self_type const& () const
    {
        return *this;
    }
    
    void set_release(bool val)
    {
        _nrelease = val;
    }
    
    void set_bytes(void* da)
    {
        _da = (value_type*)da;
    }
    
    self_type& offset(usize _sz)
    {
        _da += _sz;
        if (_dl < _sz)
            _dl = 0;
        else
            _dl -= _sz;
        return *this;
    }
    
    self_type shadow() const
    {
        return self_type(_da, _dl, core::assign);
    }
    
    usize limit(usize sz) const
    {
        return TRIEXP(_dl < sz, _dl, sz);
    }
    
    bool empty() const
    {
        return _da == NULL || _dl == 0;
    }
    
protected:
    
    //! value.
    value_type* _da;
    
    //! size of buffer.
    usize _dl;
    
    //! buffer is need release.
    bool _nrelease;
    
};

typedef _base_data<byte> data;

static const data null_data = data();

class data_le
: public data
{
public:    
    
    data_le(char c)
    {        
        this->duplicate(&c, 1);
    }
    
    data_le(short c)
    {
        this->alloc(2);
        _da[0] = b16_l(c);
        _da[1] = b16_h(c);
    }
    
    data_le(int c)
    {
        this->alloc(4);
        _da[0] = b32_l0(c);
        _da[1] = b32_l1(c);
        _da[2] = b32_h0(c);
        _da[3] = b32_h1(c);
    }
    
    operator char () const
    {
        return *((char*)_da);        
    }
    
    operator short () const
    {
        return b16_make(_da[1], _da[0]);
    }
    
    operator int () const
    {
        return b32_make(_da[3], _da[2], _da[1], _da[0]);
    }
    
};

class data_be
: public data
{
public:
    
    data_be(char c)
    {        
        this->duplicate(&c, 1);
    }
    
    data_be(short c)
    {
        this->alloc(2);
        _da[0] = b16_h(c);
        _da[1] = b16_l(c);
    }
    
    data_be(int c)
    {
        this->alloc(4);
        _da[0] = b32_h1(c);
        _da[1] = b32_h0(c);
        _da[2] = b32_l1(c);
        _da[3] = b32_l0(c);
    }
    
    operator char () const
    {
        return *((char*)_da);        
    }
    
    operator short () const
    {
        return b16_make(_da[0], _da[1]);
    }
    
    operator int () const
    {
        return b32_make(_da[0], _da[1], _da[2], _da[3]);
    }
    
};

template <typename TIn>
static core::string _type_cast_data_lebe(TIn const& inp)
{
    ::std::ostringstream oss;
    switch (inp.length())
    {
        case 1: oss << (char)inp; break;
        case 2: oss << (short)inp; break;
        case 4: oss << (int)inp; break;
    }
    return oss.str();   
}

template <typename TVal>
class _base_framedata
    : protected _base_data<TVal>
{
    typedef _base_data<TVal> super;

public:

    typedef TVal value_type;

	_base_framedata(TVal* da, usize capacity)
		: _capacity(capacity), _offset(0)
	{
		this->_da = da;
		this->_dl = capacity;
		this->_nrelease = false;
	}

    _base_framedata(usize capacity = 0)
        : _capacity(capacity), _offset(0)
    {
        if (capacity != 0)
        {
            super::alloc(capacity * sizeof(TVal));
        }
    }

    ~_base_framedata()
    {
        PASS;
    }

    char const* c_str() const
    {
        return (char const*)(this->_da + _offset);
    }

    byte* bytes() const
    {
        return (byte*)(byte const*)(this->_da + _offset);
    }

    usize length() const
    {
        return this->_dl - _offset;
    }

    usize size() const
    {
        return this->length();
    }

    void move(usize off)
    {
        _offset += off;
    }

    void seekto(usize pos)
    {
        _offset = pos;
    }

	usize position() const
	{
		return _offset;
	}

	usize space() const
	{
		return _capacity - _offset;
	}

	usize copy(void const* d, usize l)
	{
		usize tgtsz = l;
		usize spa = this->space();
		if (spa < l)
			tgtsz = spa;
		if (tgtsz == 0)
			return 0;
		memcpy(this->bytes(), d, tgtsz * sizeof(value_type));
		return tgtsz;
	}

    using super::set_length;
	using super::alloc;

protected:

    usize _capacity;
    usize _offset;

};

typedef _base_framedata<byte> framedata;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
