
# include "Core.h"
# include "EC+NNT.h"
# include "Openssl+NNT.p.h"

NNT_BEGIN_HEADER_C

# include <openssl/dsa.h>
# include <openssl/dh.h>
# include <openssl/ec.h>
# include <openssl/ecdsa.h>
# include <openssl/ecdh.h>
# include <openssl/bio.h>
# include <openssl/err.h>
# include <openssl/pem.h>
# include <openssl/engine.h>
# include <openssl/rc4.h>

NNT_END_HEADER_C

NNT_BEGIN_CXX

class EcKey
: public openssl::Object<EcKey, EC_KEY, EC_KEY_free>
{
};

class EcDSA
: public openssl::Object<EcDSA, ECDSA_SIG, ECDSA_SIG_free>
{
};

NNTDECL_PRIVATE_BEGIN_CXX(ecc)

void init()
{
    
}

void dealloc()
{
    
}

openssl::Bio in, out;
EcKey key;

NNTDECL_PRIVATE_END_CXX

ecc::ecc()
{
    NNTDECL_PRIVATE_CONSTRUCT(ecc);
}

ecc::~ecc()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool ecc::generate()
{
    d_ptr->key.set(EC_KEY_new());
    
    if (d_ptr->key.null())
        return false;
    
    int sta = 0;
    
    // set group.
    EC_GROUP* group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    sta = EC_KEY_set_group(d_ptr->key, group);
    if (sta != 1)
    {
        d_ptr->key.set(NULL);
        return false;
    }
    
    // gen key.
    sta = EC_KEY_generate_key(d_ptr->key);
    if (sta != 1)
    {
        d_ptr->key.set(NULL);
        return false;
    }
        
    return true;
}

NNT_END_CXX
