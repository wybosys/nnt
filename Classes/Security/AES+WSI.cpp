
# include "Core.h"
# include "AES+WSI.h"

WSI_BEGIN_HEADER_C

# include <openssl/aes.h>
# include <openssl/evp.h>

WSI_END_HEADER_C

WSI_BEGIN_CXX

static const unsigned int _gs_salt[] = { 13579, 86420 };

void aes::encrypt(core::data const& key, core::data const& in, core::vector<byte>& out)
{
    EVP_CIPHER_CTX e;
    
    // init key.
    {
        int nrounds = 5;
        unsigned char _key[32], _iv[32];
        
        if (32 != EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (uchar*)&_gs_salt, (uchar*)key.bytes(), key.length(), nrounds, _key, _iv))
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
        
        if (32 != EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (uchar*)&_gs_salt, (uchar*)key.bytes(), key.length(), nrounds, _key, _iv))
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
    EVP_DecryptFinal_ex(&e, plaintext+p_len, &f_len);
    
    out.resize(p_len + f_len);
}

WSI_END_CXX