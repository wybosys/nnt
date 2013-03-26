
# include "Core.h"
# include "EC+NNT.h"
# include "Openssl+NNT.p.h"

NNT_BEGIN_HEADER_C

# include <openssl/ec.h>
# include <openssl/ecdsa.h>
# include <openssl/ecdh.h>
# include <openssl/bio.h>
# include <openssl/err.h>
# include <openssl/evp.h>
# include <openssl/pem.h>

NNT_END_HEADER_C

NNT_BEGIN_CXX

NNTDECL_PRIVATE_BEGIN_CXX(ecc)

void init()
{
    key = NULL;
}

void dealloc()
{
    free();
}

void free()
{
    if (key == NULL)
        return;
    EC_KEY_free(key);
    key = NULL;
}

openssl::Bio in, out;
EC_KEY* key;

NNTDECL_PRIVATE_END_CXX

ecc::ecc()
{
    NNTDECL_PRIVATE_CONSTRUCT(ecc);
}

ecc::~ecc()
{
    NNTDECL_PRIVATE_DESTROY();
}

void ecc::generate(core::data const& pass)
{
    d_ptr->free();
    
    d_ptr->key = PEM_read_bio_ECPrivateKey(d_ptr->in, NULL, NULL, openssl::Bio(pass));
}

NNT_END_CXX
