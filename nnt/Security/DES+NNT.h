
# ifndef __NNT_SEC_DES_96EB9B4EDDBA49189B7098BB77440FC6_H_INCLUDED
# define __NNT_SEC_DES_96EB9B4EDDBA49189B7098BB77440FC6_H_INCLUDED

NNT_BEGIN_HEADER_CXX

NNTCLASS(des);

class des
{
public:
    static void encrypt(char const* key, core::string const& in, core::vector<byte>& out);
    static void decrypt(char const* key, core::vector<byte> const& in, core::string& out);
};

NNT_END_HEADER_CXX

# endif
