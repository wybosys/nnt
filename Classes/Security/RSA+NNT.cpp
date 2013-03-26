
# include "Core.h"
# include "RSA+NNT.h"

NNT_BEGIN_HEADER_C

# include <openssl/rsa.h>
# include <openssl/pem.h>

NNT_END_HEADER_C

NNT_BEGIN_CXX

NNTDECL_PRIVATE_BEGIN_CXX(rsa)

void init()
{
    env = NULL;
}

void dealloc()
{
    free();
}

void free()
{
    if (env == NULL)
        return;
    
    RSA_free(env);
    env = NULL;
}

self_type& operator = (RSA* rsa)
{
    free();
    env = rsa;
    return *this;
}

operator RSA* ()
{
    return env;
}

core::vector<byte> pubkey, prvkey;

protected:

RSA* env;

NNTDECL_PRIVATE_END_CXX

rsa::rsa()
{
    NNTDECL_PRIVATE_CONSTRUCT(rsa);
}

rsa::~rsa()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool rsa::generate(uint bits)
{    
    RSA* rsa = RSA_new();
    
    BIGNUM* bg = BN_new();    
    BN_set_word(bg, RSA_F4);
    RSA_generate_key_ex(rsa, bits, bg, NULL);
    BN_free(bg);
    
    // read private key.
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, 0, 0, 0, 0, 0);
    d_ptr->prvkey.resize(BIO_number_written(bio));
    BIO_read(bio, core::pointer(d_ptr->prvkey), (int)d_ptr->prvkey.size());
    BIO_free(bio);
    
    // read public key.
    bio = BIO_new(BIO_s_mem());
    //PEM_write_bio_RSAPublicKey(bio, rsa);
    PEM_write_bio_RSA_PUBKEY(bio, rsa);
    d_ptr->pubkey.resize(BIO_number_written(bio));
    BIO_read(bio, core::pointer(d_ptr->pubkey), (int)d_ptr->pubkey.size());
    BIO_free(bio);
    
    // set rsa.
    d_ptr->env = rsa;
    
    return true;
}

bool rsa::set_public_key(const byte * key, usize klen)
{
    RSA* rsa = RSA_new();
    
    // write public key.
    BIO* bio = BIO_new(BIO_s_mem());
    BIO_write(bio, key, (int)klen);
    
    // read key.
    RSA* re = PEM_read_bio_RSA_PUBKEY(bio, &rsa, NULL, NULL);
    BIO_free(bio);
    
    if (re != rsa)
    {
        RSA_free(rsa);
        return false;
    }
    
    *d_ptr = rsa;

    return true;
}

bool rsa::encrypt(core::data const& in, core::vector<byte>& out) const
{
    int sz_rsa = RSA_size(*d_ptr);
    
    if (sz_rsa - 11 < (int)in.length()) 
    {
        const int sz = sz_rsa - 11;
        int left = in.length();
        out.clear();
        
        core::vector<byte> tmp;
        tmp.resize(sz_rsa);
        
        while (left > 0)
        {
            int eatn = MIN(left, sz);            
            
            int sta = RSA_public_encrypt(eatn,
                                         in.bytes() + in.length() - left,
                                         core::pointer(tmp),
                                         *d_ptr,
                                         RSA_PKCS1_PADDING);
			if (sta == -1)
				return false;
            
            core::append(out, core::pointer(tmp), sta);
            
            left -= eatn;
        }
        
        return true;
    }
    
    out.resize(sz_rsa);
    int sta = RSA_public_encrypt((int)in.length(),
                                 in.bytes(),
                                 core::pointer(out),
                                 *d_ptr,
                                 RSA_PKCS1_PADDING);
    if ((sta != -1) && (sta != out.size()))
        out.resize(sta);
    return sta != -1;
}

bool rsa::decrypt(core::data const& in, core::vector<byte>& out) const
{
    int sz_rsa = RSA_size(*d_ptr);
    
    if (sz_rsa < (int)in.length())
    {
        out.clear();
        core::vector<byte> tmp;
        tmp.resize(sz_rsa);
        
        int left = in.length();
        
        while (left > 0)
        {
            int eatn = MIN(left, sz_rsa);
            
            int sta = RSA_private_decrypt(eatn,
                                          in.bytes() + in.length() - left,
                                          core::pointer(tmp),
                                          *d_ptr,
                                          RSA_PKCS1_PADDING);
            
			if (sta == -1)
				return false;
            
            core::append(out, core::pointer(tmp), sta);
            
            left -= sz_rsa;
        }
        
        return true;
    }
    
    out.resize(sz_rsa);
    int sta = RSA_private_decrypt((int)in.length(), 
                                  in.bytes(), 
                                  core::pointer(out), 
                                  *d_ptr,
                                  RSA_PKCS1_PADDING);
    if ((sta != -1) && (sta != out.size()))
        out.resize(sta);
    return sta != -1;
}

core::vector<byte> rsa::public_key() const
{
    return d_ptr->pubkey;
}

core::vector<byte> rsa::private_key() const
{
    return d_ptr->prvkey;
}

NNT_END_CXX
