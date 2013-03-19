
# ifndef __NNT_SEC_BASEN_7C47E365ABD34EB496D2CDFDA3BF5E8C_H_INCLUDED
# define __NNT_SEC_BASEN_7C47E365ABD34EB496D2CDFDA3BF5E8C_H_INCLUDED

NNT_BEGIN_HEADER_CXX

NNTCLASS(base64);

class base64
{
public:
    
    static void encode(void* data, usize dlen, core::vector<byte>& out);
    static void decode(void* data, usize dlen, core::vector<byte>& out);
    
    static void encode(core::string const&, core::string&);
    static core::string encode(core::string const&);
    
    static void decode(core::string const&, core::string&);
    static void decode(core::data const&, core::string&);
    static void decode(core::string const&, core::data&);
    
    static core::data encode(core::data const&);
    static core::data decode(core::data const&);
    
};

NNT_END_HEADER_CXX

# endif