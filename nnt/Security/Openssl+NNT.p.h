
# ifndef __NNT_OPENSSL_4F27733D97F64233866D4C45E27D779A_H_INCLUDED
# define __NNT_OPENSSL_4F27733D97F64233866D4C45E27D779A_H_INCLUDED

NNT_BEGIN_HEADER_C

# include <openssl/bio.h>

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif
