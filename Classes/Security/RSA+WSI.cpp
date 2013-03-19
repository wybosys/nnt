
# include "Core.h"
# include "RSA+WSI.h"

WSI_BEGIN_HEADER_C

# include <openssl/rsa.h>
# include <openssl/pem.h>

WSI_END_HEADER_C

WSI_BEGIN_CXX

rsa::rsa()
:_env(NULL)
{
    PASS;
}

rsa::~rsa()
{
    _free();
}

void rsa::_free()
{
    RSA_free((RSA*)_env);
    _env = NULL;
}

bool rsa::generate()
{    
    RSA* rsa = RSA_new();
    
    BIGNUM* bg = BN_new();    
    BN_set_word(bg, RSA_F4);
    RSA_generate_key_ex(rsa, DEFAULT_BITS, bg, NULL);
    BN_free(bg);
    
    // read private key.
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, 0, 0, 0, 0, 0);
    this->_prvkey.resize(BIO_number_written(bio));
    BIO_read(bio, core::pointer(this->_prvkey), (int)this->_prvkey.size());
    BIO_free(bio);
    
    // read public key.
    bio = BIO_new(BIO_s_mem());
    //PEM_write_bio_RSAPublicKey(bio, rsa);
    PEM_write_bio_RSA_PUBKEY(bio, rsa);
    this->_pubkey.resize(BIO_number_written(bio));
    BIO_read(bio, core::pointer(this->_pubkey), (int)this->_pubkey.size());
    BIO_free(bio);
    
    // set rsa.
    this->_env = rsa;
    
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
    
    this->_env = rsa;
    return true;
}

bool rsa::encrypt(core::data const& in, core::vector<byte>& out) const
{
    int sz_rsa = RSA_size((RSA*)this->_env);
    
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
                                         (RSA*)this->_env,
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
                                 (RSA*)this->_env,
                                 RSA_PKCS1_PADDING);
    if ((sta != -1) && (sta != out.size()))
        out.resize(sta);
    return sta != -1;
}

bool rsa::decrypt(core::data const& in, core::vector<byte>& out) const
{
    int sz_rsa = RSA_size((RSA*)this->_env);    
    
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
                                          (RSA*)this->_env,
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
                                  (RSA*)this->_env, 
                                  RSA_PKCS1_PADDING);
    if ((sta != -1) && (sta != out.size()))
        out.resize(sta);
    return sta != -1;
}

WSI_END_CXX
