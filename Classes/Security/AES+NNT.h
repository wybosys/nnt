
# ifndef __NNT_SEC_AES_0EFA914D5C0D4AEAA8B12C688DDE632A_H_INCLUDED
# define __NNT_SEC_AES_0EFA914D5C0D4AEAA8B12C688DDE632A_H_INCLUDED

NNT_BEGIN_HEADER_CXX

NNTCLASS(aes);

class aes
{
public:
    static void encrypt(core::data const& key, core::data const& in, core::vector<byte>& out);
    static void decrypt(core::data const& key, core::data const& in, core::vector<byte>& out);
};

NNT_END_HEADER_CXX

# endif
