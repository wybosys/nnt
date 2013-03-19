
# ifndef __WSI_CODEC_URLENCODEC_D4E5F5B854FB490EB880EBC8F41F9111_H_INCLUDED
# define __WSI_CODEC_URLENCODEC_D4E5F5B854FB490EB880EBC8F41F9111_H_INCLUDED

# ifdef WSI_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

WSIDECL_BOOLOBJECT(encoded, unencoded);

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

# endif
