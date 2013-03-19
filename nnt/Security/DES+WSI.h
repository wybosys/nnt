
# ifndef __WSI_SEC_DES_96EB9B4EDDBA49189B7098BB77440FC6_H_INCLUDED
# define __WSI_SEC_DES_96EB9B4EDDBA49189B7098BB77440FC6_H_INCLUDED

WSI_BEGIN_HEADER_CXX

WSICLASS(des);

class des
{
public:
    static void encrypt(char const* key, core::string const& in, core::vector<byte>& out);
    static void decrypt(char const* key, core::vector<byte> const& in, core::string& out);
};

WSI_END_HEADER_CXX

# endif