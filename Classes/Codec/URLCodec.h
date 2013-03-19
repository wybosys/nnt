
# ifndef __NNT_CODEC_URLENCODEC_D4E5F5B854FB490EB880EBC8F41F9111_H_INCLUDED
# define __NNT_CODEC_URLENCODEC_D4E5F5B854FB490EB880EBC8F41F9111_H_INCLUDED

# ifdef NNT_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

NNTDECL_BOOLOBJECT(encoded, unencoded);

class URLEncode
{
public:
    
    static ns::String encode(ns::String const&);
    static ns::String encode(ns::Dictionary const&, bool encoded);
    
};

class URLDecode
{
public:
    
    URLDecode();
    URLDecode(String const& str);
    
public:
    
    //! clear.
    void clear();
    
    //! decode string.
    void decode(String const& str);
    
    //! is array.
    bool is_array(String const& key) const;
    
    //! get value.
    String value(String const& key) const;
    
    //! get array.
    Array array(String const& key) const;
    
protected:
    
    MutableDictionary _data;
    ns::String _base;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif
