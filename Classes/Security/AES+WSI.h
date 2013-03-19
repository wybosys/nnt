
# ifndef __WSI_SEC_AES_0EFA914D5C0D4AEAA8B12C688DDE632A_H_INCLUDED
# define __WSI_SEC_AES_0EFA914D5C0D4AEAA8B12C688DDE632A_H_INCLUDED

WSI_BEGIN_HEADER_CXX

WSICLASS(aes);

class aes
{
public:
    static void encrypt(core::data const& key, core::data const& in, core::vector<byte>& out);
    static void decrypt(core::data const& key, core::data const& in, core::vector<byte>& out);
};

WSI_END_HEADER_CXX

# endif