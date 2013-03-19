
# include "Core.h"
# include "DES+WSI.h"

WSI_BEGIN_HEADER_C

# include <openssl/des.h>
# include <math.h>

WSI_END_HEADER_C

WSI_BEGIN_CXX

void des::encrypt(char const* key, core::string const& in, core::vector<byte>& out)
{
    DES_cblock key_block;
    DES_key_schedule schedule;
    DES_string_to_key(key, &key_block);
    DES_set_key_checked(&key_block, &schedule);
    
    usize sz = (usize)ceil((double)in.size() / sizeof(DES_cblock)) * sizeof(DES_cblock);
    out.resize(sz);
    
    core::string::const_iterator iter = in.begin();
    DES_cblock* output = (DES_cblock*)core::pointer(out);
    
    DES_cblock input;
    while (iter != in.end())
    {
        usize sz = in.end() - iter;
        if (sz >= 8)
            sz = 8;
        else 
            memset(input, 0, sizeof(DES_cblock));
        memcpy(input, &*iter, sz);
        DES_ecb_encrypt(&input, output, &schedule, DES_ENCRYPT);
        iter += sz;
        output += 1;
    }
}

void des::decrypt(char const* key, core::vector<byte> const& in, core::string& out)
{
    DES_cblock key_block;
    DES_key_schedule schedule;
    DES_string_to_key(key, &key_block);
    DES_set_key_checked(&key_block, &schedule);
    
    char* buf = (char*)malloc(in.size());
    
    core::vector<byte>::const_iterator iter = in.begin();
    DES_cblock* output = (DES_cblock*)buf;
    
    DES_cblock input;
    while (iter != in.end())
    {
        usize sz = in.end() - iter;
        if (sz >= 8)
            sz = 8;
        else 
            memset(input, 0, sizeof(DES_cblock));        
        memcpy(input, &*iter, sz);
        DES_ecb_encrypt(&input, output, &schedule, DES_DECRYPT);
        iter += sz;
        output += 1;
    }
    
    out = buf;
    
    free(buf);
}

WSI_END_CXX