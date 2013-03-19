
# ifndef __NNT_SECURITY_SHA_0F4841FFECF44A05B2AEA96715ADAFA3_H_INCLUDED
# define __NNT_SECURITY_SHA_0F4841FFECF44A05B2AEA96715ADAFA3_H_INCLUDED

NNT_BEGIN_HEADER_CXX

NNTCLASS(sha0);
NNTCLASS(sha1);
NNTCLASS(sha2);

class sha0
{
    
};

class sha1
{
public:
    
    static core::data digest(core::data const&);
    
};

class sha2
{
public:
    
    static core::data digest224(core::data const&);
    static core::data digest256(core::data const&);
    static core::data digest512(core::data const&);
    static core::data digest384(core::data const&);
    
};

NNT_END_HEADER_CXX

# endif
