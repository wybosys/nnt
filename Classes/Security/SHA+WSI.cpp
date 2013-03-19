
# include "Core.h"
# include "SHA+WSI.h"

WSI_BEGIN_HEADER_C

# include <openssl/sha.h>

WSI_END_HEADER_C

WSI_BEGIN_CXX

core::data sha1::digest(core::data const& da)
{
    core::data tmp = da.shadow();
    
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    while (tmp.size())
    {
        SHA1_Update(&ctx, tmp.bytes(), tmp.limit(SHA_DIGEST_LENGTH));
        tmp.offset(tmp.limit(SHA_DIGEST_LENGTH));
    }
    
    core::data ret(SHA_DIGEST_LENGTH);
    SHA1_Final((byte*)ret.bytes(), &ctx);
    
    return ret;
}

core::data sha2::digest224(core::data const& da)
{
    core::data tmp = da.shadow();
    
    SHA256_CTX ctx;
    SHA224_Init(&ctx);
    
    while (tmp.size())
    {
        SHA224_Update(&ctx, tmp.bytes(), tmp.limit(SHA224_DIGEST_LENGTH));
        tmp.offset(tmp.limit(SHA224_DIGEST_LENGTH));
    }
    
    core::data ret(SHA224_DIGEST_LENGTH);
    SHA224_Final((byte*)ret.bytes(), &ctx);
    
    return ret;
}

core::data sha2::digest256(core::data const& da)
{
    core::data tmp = da.shadow();
    
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    
    while (tmp.size())
    {
        SHA256_Update(&ctx, tmp.bytes(), tmp.limit(SHA256_DIGEST_LENGTH));
        tmp.offset(tmp.limit(SHA256_DIGEST_LENGTH));
    }
    
    core::data ret(SHA256_DIGEST_LENGTH);
    SHA256_Final((byte*)ret.bytes(), &ctx);
    
    return ret;
}

core::data sha2::digest512(core::data const& da)
{
    core::data tmp = da.shadow();
    
    SHA512_CTX ctx;
    SHA512_Init(&ctx);
    
    while (tmp.size())
    {
        SHA512_Update(&ctx, tmp.bytes(), tmp.limit(SHA512_DIGEST_LENGTH));
        tmp.offset(tmp.limit(SHA512_DIGEST_LENGTH));
    }
    
    core::data ret(SHA512_DIGEST_LENGTH);
    SHA512_Final((byte*)ret.bytes(), &ctx);
    
    return ret;
}

core::data sha2::digest384(core::data const& da)
{
    core::data tmp = da.shadow();
    
    SHA512_CTX ctx;
    SHA384_Init(&ctx);
    
    while (tmp.size())
    {
        SHA384_Update(&ctx, tmp.bytes(), tmp.limit(SHA384_DIGEST_LENGTH));
        tmp.offset(tmp.limit(SHA384_DIGEST_LENGTH));
    }
    
    core::data ret(SHA384_DIGEST_LENGTH);
    SHA384_Final((byte*)ret.bytes(), &ctx);
    
    return ret;
}

WSI_END_CXX
