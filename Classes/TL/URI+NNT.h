
# ifndef __NNT_TL_URI_791DDEB295274772A7E5B2D76AE1E31C_H_INCLUDED
# define __NNT_TL_URI_791DDEB295274772A7E5B2D76AE1E31C_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ntl)

template <typename valT>
static usize length_of(valT const* buf)
{
    usize ret = 0;
    while (*buf++ != 0) ++ret;
    return ret;
}

NNT_BEGIN_NS(impl)

template <typename elemT>
class buffer_parse
{
public:

    buffer_parse(elemT const* b, usize l)
    : buf(b), length(l), position(0)
    {
        
    }
    
    bool seek(elemT const& c)
    {
        for (usize i = position; i < length; ++i)
            if (buf[i] == c)
            {
                position = i;
                return true;
            }
        return false;
    }
    
    bool next(elemT const& c)
    {
        if (position + 1 >= length)
            return false;
        
        if (buf[position + 1] == c)
        {
            ++position;
            return true;
        }
        
        return false;
    }
    
    void forward(uint o = 1)
    {
        position += o;
    }
        
    elemT const* buf;
    usize length, position;
    
};

template <typename strT>
class uri
{
public:
    
    typedef strT string_type;
    typedef typename string_type::value_type char_type;
    
    typedef core::list<string_type> components_type;
    
    uri(char_type const* str)
    {
        set(str, length_of(str));
    }
    
    uri(string_type const& str)
    {
        set(str.c_str(), str.length());
    }
    
    uri()
    {
        PASS;
    }
    
    void set(char_type const* buf, usize len)
    {
        _parse_scheme(buf, len);
        _parse_components(buf, len);
    }
    
    uri& operator = (char_type const* str)
    {
        set(str, length_of(str));
        return *this;
    }
    
    uri& operator = (string_type const& str)
    {
        set(str.c_str(), str.length());
        return *this;
    }
    
    bool operator == (uri const& r)
    {
        return equal(r);
    }
    
    bool operator != (uri const& r)
    {
        return !equal(r);
    }
    
    bool equal(uri const& r)
    {
        if (scheme != r.scheme)
            return false;
        if (slice != r.slice)
            return false;
        if (components.size() != r.components.size())
            return false;
        typename components_type::const_iterator i = components.begin();
        typename components_type::const_iterator j = r.components.begin();
        while (i != components.end())
        {
            if (*i != *j)
                return false;
            
            ++i;
            ++j;
        }
        
        return true;
    }
        
    void add_extension(string_type const& str)
    {
        if (components.size() == 0)
            components.push_back(str);
        else
        {
            *components.rbegin() += str;
        }
    }
    
    string_type const& filename() const
    {
        return *components.rbegin();
    }
    
    operator string_type () const
    {
        return combine();
    }
    
    string_type combine() const
    {
        string_type ret;
        if (!scheme.empty())
            ret = scheme + "://";
        typename components_type::const_iterator each = components.begin();
        while (each != components.end())
        {
            ret += *each;
            if (++each != components.end())
                ret += '/';
        }
        if (!slice.empty())
        {
            ret += '#';
            ret += slice;
        }        
        return ret;
    }
    
    string_type scheme, slice;    
    components_type components;
    
protected:
    
    bool _parse_scheme(char_type const*& buf, usize& len)
    {
        buffer_parse<char_type> bp(buf, len);
        if (!bp.seek(':'))
            return false;
        if (!(bp.next('/') && bp.next('/')))
            return false;
        bp.forward();
        scheme = string_type(buf, bp.position - 3);
        buf += bp.position;
        len -= bp.position;
        return true;
    }
    
    void _parse_components(char_type const*& buf, usize& len)
    {
        slice.clear();
        components.clear();
        
        string_type tmp;
        while (_parse_component(buf, len, tmp))
            if (!tmp.empty())
                components.push_back(tmp);
    }
    
    bool _parse_component(char_type const*& buf, usize& len, string_type& ret)
    {
        if (len == 0)
            return false;
        buffer_parse<char_type> bp(buf, len);
        if (bp.seek('/'))
        {
            bp.forward();
            ret = string_type(buf, bp.position - 1);
            buf += bp.position;
            len -= bp.position;
        }
        else
        {
            if (bp.seek('#'))
            {
                bp.forward();
                
                ret = string_type(buf, bp.position - 1);
                slice = string_type(buf + bp.position, len);
            }
            else
            {
                ret = string_type(buf, len);
            }
            
            len = 0;
        }
        
        return true;
    }
      
};

NNT_END_NS

typedef impl::uri<string> uri;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
