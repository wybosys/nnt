
# ifndef __NNT_OPENSSL_4F27733D97F64233866D4C45E27D779A_H_INCLUDED
# define __NNT_OPENSSL_4F27733D97F64233866D4C45E27D779A_H_INCLUDED

NNT_BEGIN_HEADER_C

# include <openssl/bio.h>
# include <openssl/evp.h>

NNT_END_HEADER_C

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(openssl)

class Bio
{
    Bio(Bio const&);
    
public:
    
    Bio();
    Bio(BIO_METHOD*);
    Bio(core::data const&);
    ~Bio();
    
    void clear();
    
    Bio& operator = (core::data const&);
    void set(core::data const&);
    
    operator BIO* () const;    
    BIO* bio;
    
};

template <typename implT, typename keyT, void (*freeFunc)(keyT*)>
class Object
: public core::uml::composition<implT, keyT*>
{
    typedef core::uml::composition<implT, keyT*> super;
    typedef typename super::impl_type impl_type;
    
public:
    
    typedef typename super::value_type value_type;
    
    Object(value_type obj = NULL)
    {
        super::_obj = obj;
    }
    
    ~Object()
    {
        clear();
    }
    
    void clear()
    {
        if (super::_obj == NULL)
            return;
        (*freeFunc)(super::_obj);
        super::_obj = NULL;
    }
    
    impl_type& set(value_type obj)
    {
        clear();
        super::_obj = obj;
        return super::_impl();
    }

    
};

class EvpKey
: public Object<EvpKey, EVP_PKEY, EVP_PKEY_free>
{
};

class EvpKeyContext
: public Object<EvpKeyContext, EVP_PKEY_CTX, EVP_PKEY_CTX_free>
{
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
