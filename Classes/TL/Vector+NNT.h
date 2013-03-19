
# ifndef __NNT_CORE_VECTOR_56FAB19464A7411FAD0AFBC152A4AD2E_H_INCLUDED
# define __NNT_CORE_VECTOR_56FAB19464A7411FAD0AFBC152A4AD2E_H_INCLUDED

# ifdef NNT_CXX

# include <vector>
# include <stack>

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

using std::stack;

template <typename valT>
class _vector
{
    typedef ::std::vector<valT> stl_type;
    
public:
    
    typedef typename stl_type::const_iterator const_iterator;
    typedef typename stl_type::iterator iterator;
    typedef valT value_type;
    typedef typename stl_type::size_type size_type;
    typedef typename stl_type::reference reference;
    typedef typename stl_type::const_reference const_reference;
    typedef typename stl_type::reverse_iterator reverse_iterator;
    typedef typename stl_type::const_reverse_iterator const_reverse_iterator;
    
    const_iterator begin() const
    {
        return _stl.begin();
    }
    
    iterator begin()
    {
        return _stl.begin();
    }
    
    const_reverse_iterator rbegin() const
    {
        return _stl.rbegin();
    }
    
    reverse_iterator rbegin()
    {
        return _stl.rbegin();
    }
    
    const_iterator end() const
    {
        return _stl.end();
    }
    
    iterator end()
    {
        return _stl.end();
    }
    
    const_reverse_iterator rend() const
    {
        return _stl.rend();
    }
    
    reverse_iterator rend()
    {
        return _stl.rend();
    }
    
    void push_back(value_type const& r)
    {
        _stl.push_back(r);
    }
    
    void push_front(value_type const& r)
    {
        _stl.push_front(r);
    }
    
    template <typename val2T>
    void push_back(val2T const& r)
    {
        _stl.push_back(value_type(r));
    }
    
    template <typename val2T>
    void push_front(val2T const& r)
    {
        _stl.push_front(value_type(r));
    }
    
    iterator erase(iterator __position)
    {
        return _stl.erase(__position);
    }
    
    iterator erase(iterator __first, iterator __last)
    {
        return _stl.erase(__first, __last);
    }
    
    void erase(value_type const& obj)
    {
        iterator found = ::std::find(_stl.begin(), _stl.end(), obj);
        if (found != _stl.end())
            _stl.erase(found);
    }
    
    bool exist(value_type const& obj) const
    {
        iterator found = ::std::find(_stl.begin(), _stl.end(), obj);
        return found != _stl.end();
    }
    
    size_type size() const
    {
        return _stl.size();
    }
    
    size_type count() const
    {
        return _stl.size();
    }
    
    size_type length() const
    {
        return _stl.size();
    }
    
    void clear()
    {
        _stl.clear();
    }
    
    void resize(size_type sz, value_type v = value_type())
    {
        _stl.resize(sz, v);
    }
    
    reference operator [] (size_type __n)
    { 
        return _stl[__n];
    }
    
    const_reference operator [] (size_type __n) const
    {
        return _stl[__n];
    }
    
    reference at(size_type __n)
    {
        return _stl.at(__n);
    }
    
    const_reference at(size_type __n) const
    {
        return _stl.at(__n);
    }
    
    reference front()
    {
        return _stl.front();
    }
    
    const_reference front() const
    {
        return _stl.front();
    }
    
    reference back()
    {
        return _stl.back();
    }
    
    const_reference back() const
    {
        return _stl.back();
    }
    
    void reserve(size_type __n)
    {
        _stl.reserve(__n);
    }
    
    iterator insert(iterator __position, const value_type& __x)
    {
        return _stl.insert(__position, __x);
    }
    
    operator stl_type& ()
    {
        return _stl;
    }
    
    operator stl_type const& () const
    {
        return _stl;
    }
    
protected:
    
    stl_type _stl;
    
};

template <typename valT>
class vector
: public _vector<valT>
{
    
};

template <typename valT>
class vector <valT*>
: public _vector<valT*>
{
    typedef _vector<valT*> super;   
    
public:
    
    typedef typename super::iterator iterator;
    typedef typename super::const_iterator const_iterator;
    typedef typename super::value_type value_type;
    
    void clear_destroy()
    {
        for (iterator iter = this->begin();
             iter != this->end();
             ++iter)
        {
            delete *iter;
        }
        this->clear();
    }
    
    void clear_drop()
    {
        for (iterator iter = this->begin();
             iter != this->end();
             ++iter)
        {
            if (*iter)
                (*iter)->drop();
        }
        this->clear();
    }
    
    template <typename val2T>
    void push_back(val2T const& r, typename is_instance<val2T>::type* trait = NULL)
    {
        this->_push_back(r, trait);
    }
    
    template <typename val2T>
    void push_front(val2T const& r, typename is_instance<val2T>::type* trait = NULL)
    {
        this->_push_front(new valT(r));
    }
    
    template <typename iterT>
    void erase_destroy(iterT const& iter)
    {
        delete (*iter);
        this->_stl.erase(iter);
    }
    
    template <typename iterT>
    void erase_drop(iterT const& iter)
    {
        if (*iter)
            (*iter)->drop();
        this->_stl.erase(iter);
    }
    
protected:
    
    template <typename val2T>
    void _push_back(val2T const& r, instance_type*)
    {
        this->_stl.push_back(new valT(r));
    }
    
    template <typename val2T>
    void _push_back(val2T const& r, pointer_type*)
    {
        this->_stl.push_back(r);        
    }
    
    template <typename val2T>
    void _push_front(val2T const& r, instance_type*)
    {
        this->_stl.push_front(new valT(r));
    }
    
    template <typename val2T>
    void _push_front(val2T const& r, pointer_type*)
    {
        this->_stl.push_front(r);        
    }
    
};

template <typename valT>
class pointer_vector
: public vector<valT*>
{
    typedef vector<valT*> super;
    
public:
    
    typedef typename super::size_type size_type;
    typedef typename super::iterator iterator;
    typedef valT value_type;
    
    pointer_vector()
    : clear_on_destroy(true)
    {
        PASS;
    }
    
    ~pointer_vector()
    {
        if (clear_on_destroy)
            this->clear();
    }
    
    bool clear_on_destroy;
    
    void clear()
    {
        this->clear_destroy();
    }
    
    void resize(size_type sz, bool mem = true)
    {
        size_type const cur = this->size();
        if (cur > sz)
        {
            if (mem)
            {                
                iterator iter = this->begin();
                ::std::advance(iter, sz);            
                while(iter != this->end())
                {
                    delete *iter;
                    ++iter;
                }
            }
            super::resize(sz, NULL);            
        }
        else if (cur < sz)
        {
            super::resize(sz, NULL);
            if (mem)
            {
                iterator iter = this->begin();
                ::std::advance(iter, cur);  
                while (iter != this->end())
                {
                    *iter = new value_type;
                    ++iter;
                }
            }
        }
    }
    
private:
    
    void reserve(size_type __n);
    
};

template <typename valT>
class refpointer_vector
: public vector<valT*>
{
    typedef vector<valT*> super;
    
public:
    
    typedef typename super::size_type size_type;
    typedef typename super::iterator iterator;
    typedef typename super::const_iterator const_iterator;
    typedef typename super::reference reference;
    typedef typename super::const_reference const_reference;
    
    typedef valT value_type;
    
    refpointer_vector()
    {
        PASS;
    }
    
    ~refpointer_vector()
    {
        this->clear();
    }
    
    void clear()
    {
        this->clear_drop();
    }
    
    void add(value_type const& r)
    {
        this->push_back(r);
        r.grab();
    }
    
    void add(value_type* r)
    {
        this->push_back(r);
        r->grab();
    }
    
    value_type& add()
    {
        value_type* obj = new value_type;
        this->add(obj);
        obj->drop();
        return *obj;
    }
    
    void resize(size_type sz, bool mem = true)
    {
        size_type const cur = this->size();
        if (cur > sz)
        {
            if (mem)
            {                
                iterator iter = this->begin();
                ::std::advance(iter, sz);            
                while(iter != this->end())
                {
                    if (*iter)
                        (*iter)->drop();
                    ++iter;
                }
            }
            super::resize(sz, NULL);            
        }
        else if (cur < sz)
        {
            super::resize(sz, NULL);
            if (mem)
            {
                iterator iter = this->begin();
                ::std::advance(iter, cur);  
                while (iter != this->end())
                {
                    *iter = new value_type;
                    ++iter;
                }
            }
        }
    }
    
    template <typename tgtValT>
    void resize(size_type sz)
    {
        size_type const cur = this->size();
        if (cur > sz)
        {
            iterator iter = this->begin();
            ::std::advance(iter, sz);
            while(iter != this->end())
            {
                if (*iter)
                    (*iter)->drop();
                ++iter;
            }

            super::resize(sz, NULL);
        }
        else if (cur < sz)
        {
            super::resize(sz, NULL);
            iterator iter = this->begin();
            ::std::advance(iter, cur);
            while (iter != this->end())
            {
                *iter = new tgtValT;
                ++iter;
            }
        }

    }
        
};

template <typename valT>
inline_impl usize length(ntl::vector<valT> const& con)
{
    return con.size();
}

template <typename valT>
inline_impl ntl::vector<valT>& append(ntl::vector<valT>& con, valT const* buf, usize len)
{
    usize old = con.size();
    con.resize(old + len);
    memcpy(&con[0] + old, buf, len * sizeof(valT));
    return con;
}

template <typename valT, typename conT>
static ntl::vector<valT> tovector(conT& sck)
{  
}

template <typename valT, typename valT2>
static ntl::vector<valT> tovector(ntl::stack<valT2> sck)
{
    ntl::vector<valT> re;
    while (sck.size())
    {
        re.push_back((valT)sck.top());
        sck.pop();
    }
    return re;
}

template <typename valT, typename valT2>
static ntl::vector<valT> tovector(ntl::stack<valT2> const* psck)
{
    ntl::vector<valT> re;
    if (psck == NULL)
        return re;
    
    ntl::stack<valT2> sck = *psck;
    while (sck.size())
    {
        re.push_back((valT)sck.top());
        sck.pop();
    }
    return re;
}

NNT_END_NS

NNT_BEGIN_NS(core)

using ntl::string;

NNT_END_NS

NNT_END_HEADER_CXX

template <class valT>
inline_impl ::nnt::ntl::vector<valT>& operator << (::nnt::ntl::vector<valT>& left, valT const& right) 
{
    left.push_back(right);
    return left;
}

template <class valT>
inline_impl ::nnt::ntl::vector<valT const*>& operator << (::nnt::ntl::vector<valT const*>& con, valT* p)
{
    con.push_back((valT const*)p);
    return con;
}

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

typedef ::nnt::ntl::vector<id> _NSVector;
typedef _NSVector::iterator NSVectorIterator;
typedef _NSVector::const_iterator NSVectorConstIterator;

@interface NSVector : NNTObject {
    _NSVector *_vector;
}

@property (nonatomic, discard) _NSVector *container;

- (NSVectorIterator)begin;
- (NSVectorIterator)end;

@end

NNT_END_HEADER_OBJC

# endif

# endif

# endif