
# include "Core.h"
# include "AES+NNT.h"

NNT_BEGIN_HEADER_C

# include <openssl/aes.h>
# include <openssl/evp.h>

static const unsigned int __gs_salt[] = { 13579, 86420 };

NNT_END_HEADER_C

NNT_BEGIN_CXX

void aes::encrypt(core::data const& key, core::data const& in, core::vector<byte>& out)
{
    EVP_CIPHER_CTX e;
    
    // init key.
    {
        int nrounds = 5;
        unsigned char _key[32], _iv[32];
        
        if (32 != EVP_BytesToKey(EVP_aes_256_cbc(), 
            EVP_sha1(), 
            (uchar*)&__gs_salt, 
            (uchar*)key.bytes(), 
            key.length(), 
            nrounds, 
            _key, 
            _iv))
            return;
        
        EVP_CIPHER_CTX_init(&e);
        EVP_EncryptInit_ex(&e, EVP_aes_256_cbc(), NULL, _key, _iv);
    }
    
    // process.
    
    usize const len_in = in.length();
    uchar *plaintext = (uchar*)in.bytes();
    
    /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
    int c_len = len_in + AES_BLOCK_SIZE, f_len = 0;
    out.resize(c_len);
    uchar *ciphertext = (uchar*)core::pointer(out);
    
    /* allows reusing of 'e' for multiple encryption cycles */
    EVP_EncryptInit_ex(&e, NULL, NULL, NULL, NULL);
    
    /* update ciphertext, c_len is filled with the length of ciphertext generated,
     *len is the size of plaintext in bytes */
    EVP_EncryptUpdate(&e, ciphertext, &c_len, plaintext, len_in);
    
    /* update ciphertext with the final remaining bytes */
    EVP_EncryptFinal_ex(&e, ciphertext + c_len, &f_len);    
    
    out.resize(c_len + f_len);
    
    EVP_CIPHER_CTX_cleanup(&e);
}

void aes::decrypt(core::data const& key, core::data const& in, core::vector<byte>& out)
{
	if (in.length() == 0)
	{
		out.clear();
		return;
	}
    
    EVP_CIPHER_CTX e;
    
    // init key.
    {
        int nrounds = 5;
        unsigned char _key[32], _iv[32];
        
        if (32 != EVP_BytesToKey(EVP_aes_256_cbc(),
                                 EVP_sha1(),
                                 (uchar*)&__gs_salt,
                                 (uchar*)key.bytes(),
                                 key.length(),
                                 nrounds,
                                 _key,
                                 _iv))
            return;
        
        EVP_CIPHER_CTX_init(&e);
        EVP_DecryptInit_ex(&e, EVP_aes_256_cbc(), NULL, _key, _iv);
    }
    
    // process.
    /* plaintext will always be equal to or lesser than length of ciphertext*/
    int p_len = in.length(), f_len = 0;
    out.resize(p_len);
	uchar *plaintext = (uchar*)core::pointer(out);
    uchar *ciphertext = (uchar*)in.bytes();
    
    EVP_DecryptInit_ex(&e, NULL, NULL, NULL, NULL);
    EVP_DecryptUpdate(&e, plaintext, &p_len, ciphertext, in.length());
    EVP_DecryptFinal_ex(&e, plaintext + p_len, &f_len);
    
    out.resize(p_len + f_len);
    
    EVP_CIPHER_CTX_cleanup(&e);
}

NNT_END_CXX

NNT_BEGIN_C

struct _aes_t
{
    EVP_CIPHER_CTX *encrypt;
    EVP_CIPHER_CTX *decrypt;
};

aes_t* aes_new()
{
    _aes_t* ret = (_aes_t*)calloc(1, sizeof(_aes_t));
    ret->encrypt = EVP_CIPHER_CTX_new();
    ret->decrypt = EVP_CIPHER_CTX_new();
    return ret;
}

void aes_free(aes_t* o)
{
    EVP_CIPHER_CTX_free(o->encrypt);
    EVP_CIPHER_CTX_free(o->decrypt);

    free(o);
}

void aes_set_enkey(aes_t* t, aes_t const* r)
{
    if (t->encrypt == NULL)
        t->encrypt = EVP_CIPHER_CTX_new();
    
    if (r)
    {
        EVP_CIPHER_CTX_copy(t->encrypt, r->encrypt);
    }
    else
    {
        EVP_CIPHER_CTX_free(t->encrypt);
        t->encrypt = NULL;
    }
}

void aes_set_dekey(aes_t* t, aes_t const* r)
{
    if (t->decrypt == NULL)
        t->decrypt = EVP_CIPHER_CTX_new();
    
    if (r)
    {
        EVP_CIPHER_CTX_copy(t->decrypt, r->decrypt);
    }
    else
    {
        EVP_CIPHER_CTX_free(t->decrypt);
        t->decrypt = NULL;
    }
}

void aes_swap_rw(aes_t* o)
{
    EVP_CIPHER_CTX* t = o->encrypt;
    o->encrypt = o->decrypt;
    o->decrypt = t;
}

void aes_set_padding(aes_t* o, int b)
{
    if (b == 0)
    {
        if (o->encrypt)
            EVP_CIPHER_CTX_set_flags(o->encrypt, EVP_CIPH_NO_PADDING);
        
        if (o->decrypt)
            EVP_CIPHER_CTX_set_flags(o->decrypt, EVP_CIPH_NO_PADDING);
    }
}

int aes_set_key(aes_t* o, void const* key, size_t lkey)
{
    if (key)
    {
        if (o->encrypt == NULL)
            o->encrypt = EVP_CIPHER_CTX_new();
        if (o->decrypt == NULL)
            o->decrypt = EVP_CIPHER_CTX_new();
    }
    else
    {
        if (o->encrypt)
        {
            EVP_CIPHER_CTX_free(o->encrypt);
            o->encrypt = NULL;
        }
        if (o->decrypt)
        {
            EVP_CIPHER_CTX_free(o->decrypt);
            o->decrypt = NULL;
        }
        return 0;
    }
    
    int nrounds = 5;
    unsigned char _key[32], _iv[32];
    
    if (32 != EVP_BytesToKey(EVP_aes_256_cbc(),
                             EVP_sha1(),
                             (uchar*)&__gs_salt,
                             (uchar*)key,
                             lkey,
                             nrounds,
                             _key,
                             _iv))
        return -1;
    
    EVP_EncryptInit_ex(o->encrypt,
                       EVP_aes_256_cbc(),
                       NULL,
                       _key,
                       _iv);

    EVP_DecryptInit_ex(o->decrypt,
                       EVP_aes_256_cbc(),
                       NULL,
                       _key,
                       _iv);
    
    return 0;
}

int aes_encrypt(aes_t* o, void const* data, size_t ldata, void** outdata, size_t* loutdata)
{
    if (o->encrypt == NULL)
    {
        *outdata = malloc(ldata);
        memcpy(*outdata, data, ldata);
        *loutdata = ldata;
        return ldata;
    }
    
    usize const len_in = ldata;
    uchar *plaintext = (uchar*)data;
    
    /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
    int c_len = len_in + AES_BLOCK_SIZE, f_len = 0;
    *outdata = malloc(c_len);
        
    /* allows reusing of 'e' for multiple encryption cycles */
    EVP_EncryptInit_ex(o->encrypt, NULL, NULL, NULL, NULL);
    
    /* update ciphertext, c_len is filled with the length of ciphertext generated,
     *len is the size of plaintext in bytes */
    EVP_EncryptUpdate(o->encrypt, (uchar*)*outdata, &c_len, plaintext, len_in);
    
    /* update ciphertext with the final remaining bytes */
    EVP_EncryptFinal_ex(o->encrypt, (uchar*)*outdata + c_len, &f_len);
    
    *loutdata = c_len + f_len;
    if (*loutdata == 0) {
        free(*outdata);
        *outdata = NULL;
        return -1;
    }
    
    return 0;
}

int aes_decrypt(aes_t* o, void const* data, size_t ldata, void** outdata, size_t* loutdata)
{
    if (o->decrypt == NULL)
    {
        *outdata = malloc(ldata);
        memcpy(*outdata, data, ldata);
        *loutdata = ldata;
        return ldata;
    }
    
    int p_len = ldata, f_len = 0;
    
    *outdata = malloc(p_len);
    
	uchar *plaintext = (uchar*)*outdata;
    uchar *ciphertext = (uchar*)data;
    
    EVP_DecryptInit_ex(o->decrypt, NULL, NULL, NULL, NULL);
    
    EVP_DecryptUpdate(o->decrypt, plaintext, &p_len, ciphertext, ldata);
    
    EVP_DecryptFinal_ex(o->decrypt, plaintext + p_len, &f_len);
    
    *loutdata = p_len + f_len;
    if (*outdata == 0) {
        free(*outdata);
        *outdata = NULL;
        return -1;
    }
    
    return 0;
}

NNT_END_C

# ifdef NNT_MACH

# include <CommonCrypto/CommonCrypto.h>

NNT_BEGIN_C

struct _ns_aes_t
{
    void* encrypt;
    void* decrypt;
    int padding;
};

nsaes_t* nsaes_new()
{
    nsaes_t* ret = (nsaes_t*)malloc(sizeof(nsaes_t));
    ret->encrypt = calloc(kCCKeySizeAES256, 1);
    ret->decrypt = calloc(kCCKeySizeAES256, 1);
    ret->padding = true;
    return ret;
}

void nsaes_free(nsaes_t* o)
{
    free(o->encrypt);
    free(o->decrypt);
    free(o);
}

void nsaes_set_enkey(nsaes_t* t, nsaes_t const* r)
{
    if (t->encrypt == NULL)
        t->encrypt = malloc(kCCKeySizeAES256);
    
    if (r)
    {
        memcpy(t->encrypt, r->encrypt, kCCKeySizeAES256);
    }
    else
    {
        free(t->encrypt);
        t->encrypt = NULL;
    }
}

void nsaes_set_dekey(nsaes_t* t, nsaes_t const* r)
{
    if (t->decrypt == NULL)
        t->decrypt = malloc(kCCKeySizeAES256);
    
    if (r)
    {
        memcpy(t->decrypt, r->decrypt, kCCKeySizeAES256);
    }
    else
    {
        free(t->decrypt);
        t->decrypt = NULL;
    }
}

void nsaes_set_padding(nsaes_t* o, int b)
{
    if (o)
        o->padding = b;
}

void nsaes_swap_rw(nsaes_t* o)
{
    void* t = o->encrypt;
    o->encrypt = o->decrypt;
    o->decrypt = t;
}

int nsaes_set_key(nsaes_t* o, void const* key, size_t lkey)
{
    if (key)
    {
        if (o->encrypt == NULL)
            o->encrypt = malloc(kCCKeySizeAES256);
        if (o->decrypt == NULL)
            o->decrypt = malloc(kCCKeySizeAES256);
    }
    else
    {
        if (o->encrypt)
        {
            free(o->encrypt);
            o->encrypt = NULL;
        }
        
        if (o->decrypt)
        {
            free(o->decrypt);
            o->decrypt = NULL;
        }
        
        return 0;
    }
    
    memset(o->encrypt, 0, kCCKeySizeAES256);
    memset(o->decrypt, 0, kCCKeySizeAES256);
    
    memcpy(o->encrypt, key, MIN(lkey, kCCKeySizeAES256));
    memcpy(o->decrypt, key, MIN(lkey, kCCKeySizeAES256));
    
    return 0;
}

int nsaes_encrypt(nsaes_t* o, void const* data, size_t ldata, void** outdata, size_t* loutdata)
{
    if (o->encrypt == NULL)
    {
        *outdata = malloc(ldata);
        *loutdata = ldata;
        memcpy(*outdata, data, ldata);
        return 0;
    }
    
    *loutdata = ldata + kCCBlockSizeAES128;
    *outdata = malloc(*loutdata);
    CCOptions opt = kCCModeCBC;
    if (o->padding)
        opt |= kCCOptionPKCS7Padding;
    else
        opt |= ccNoPadding;
    CCCryptorStatus sta = CCCrypt(kCCEncrypt,
                                  kCCAlgorithmAES128,
                                  opt,
                                  o->encrypt,
                                  kCCKeySizeAES256,
                                  NULL,
                                  data,
                                  ldata,
                                  *outdata,
                                  *loutdata,
                                  loutdata);
    if (sta != kCCSuccess)
    {
        free(*outdata);
        *loutdata = 0;
        return -1;
    }
    
    return 0;
}

int nsaes_decrypt(nsaes_t* o, void const* data, size_t ldata, void** outdata, size_t* loutdata)
{
    if (o->decrypt == NULL)
    {
        *outdata = malloc(ldata);
        *loutdata = ldata;
        memcpy(*outdata, data, ldata);
        return 0;
    }
    
    *loutdata = ldata + kCCBlockSizeAES128;
    *outdata = malloc(*loutdata);
    CCOptions opt = kCCModeCBC;
    if (o->padding)
        opt |= kCCOptionPKCS7Padding;
    else
        opt |= ccNoPadding;
    CCCryptorStatus sta = CCCrypt(kCCDecrypt,
                                  kCCAlgorithmAES128,
                                  opt,
                                  o->decrypt,
                                  kCCKeySizeAES256,
                                  NULL,
                                  data,
                                  ldata,
                                  *outdata,
                                  *loutdata,
                                  loutdata);
    if (sta != kCCSuccess)
    {
        free(*outdata);
        *loutdata = 0;
        return -1;
    }
    
    return 0;
}

NNT_END_C

# endif
