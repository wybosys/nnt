
# ifndef __NNT_SEC_RSA_CCC79B0E259B48A28EA22F822E945D42_H_INCLUDED
# define __NNT_SEC_RSA_CCC79B0E259B48A28EA22F822E945D42_H_INCLUDED

NNT_BEGIN_HEADER_CXX

NNTCLASS(rsa);

NNTDECL_PRIVATE_HEAD_CXX(rsa);

class rsa
{
    NNTDECL_PRIVATE_CXX(rsa);
    
public:
    
    enum
    {
        DEFAULT_BITS = 2048,
        RSA_3 = 0x3L,
        RSA_F4 = 0x10001L,
    };
    
    rsa();
    ~rsa();
    
    //! generate private key and public key.
    bool generate(uint bits = DEFAULT_BITS);
    
    //! get key.
    core::vector<byte> public_key() const;
    core::vector<byte> private_key() const;    
    
    //! set key.
    bool set_public_key(byte const*, usize);
    
    //! encrypt & decrypt.
    bool encrypt(core::data const& in, core::vector<byte>& out) const;
    bool decrypt(core::data const& in, core::vector<byte>& out) const;
    
};

NNT_END_HEADER_CXX

# endif
