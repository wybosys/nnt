
# ifndef __WSI_SEC_RSA_CCC79B0E259B48A28EA22F822E945D42_H_INCLUDED
# define __WSI_SEC_RSA_CCC79B0E259B48A28EA22F822E945D42_H_INCLUDED

WSI_BEGIN_HEADER_CXX

WSICLASS(rsa);

class rsa
{
public:
    enum
    {
        DEFAULT_BITS = 2048,
        RSA_3 = 0x3L,
        RSA_F4 = 0x10001L,
    };
    
public:
    
    rsa();
    ~rsa();
    
    //! generate private key and public key.
    bool generate();
    
    //! get key.
    core::vector<byte> public_key() const;
    core::vector<byte> private_key() const;    
    
    //! set key.
    bool set_public_key(byte const*, usize);
    
    //! encrypt & decrypt.
    bool encrypt(core::data const& in, core::vector<byte>& out) const;
    bool decrypt(core::data const& in, core::vector<byte>& out) const;
    
protected:
    
    void _free();
    
    void* _env;
    core::vector<byte> _pubkey, _prvkey;
    
};

inline core::vector<byte> rsa::public_key() const
{
    return this->_pubkey;
}

inline core::vector<byte> rsa::private_key() const
{
    return this->_prvkey;
}

WSI_END_HEADER_CXX

# endif