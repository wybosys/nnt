
# include <wsi/WSIFoundation.h>
# include <wsi/Security/WsiSecurity.h>

using namespace wsi;

extern core::string str_long;
extern core::string str_short;

int main(int argc, const char * argv[])
{   
    if (1)
    {
        core::vector<byte> data, data1;
        base64::encode((void*)"ABC", 3, data);
        base64::decode(core::pointer(data), data.size(), data1);
        core::data da = core::type_cast<core::data>("root");
        core::data dad = base64::decode(base64::encode(da));
    }
    
    if (1)
    {
        core::string dig = core::present_cast(md5::digest(core::type_cast<core::data>(str_long)));
        trace_msg(dig);
    }
    
    if (1)
    {
        core::string uid = core::type_cast<core::string>(uuid());
        trace_msg(uid);
    }
    
    if (1)
    {
        char const* key = "TEST";
        core::vector<byte> data;
        des::encrypt(key, str_short, data);
        core::string result;
        des::decrypt(key, data, result);
        if (str_short == result)
        {
            trace_msg("des short: pass");
        }
        else
        {
            trace_msg("des short: failed");
        }
        des::encrypt(key, str_long, data);
        des::decrypt(key, data, result);
        if (str_long == result)
        {
            trace_msg("des long: pass");        
        }
        else
        {
            trace_msg("des long: failed");
        }
    }
    
    if (1)
    {
        core::data key = core::type_cast<core::data>("TEST");
        core::vector<byte> res_de, res_en;
        aes::encrypt(key, core::type_cast<core::data>(str_short), res_en);
        aes::decrypt(key, core::type_cast<core::data>(res_en), res_de);
        if (core::type_cast<core::data>(str_short) == core::type_cast<core::data>(res_de))
            trace_msg("aes short encrypt: pass.");
        else
            trace_msg("aes short encrypt: failed.");
        aes::encrypt(key, core::type_cast<core::data>(str_long), res_en);
        aes::decrypt(key, core::type_cast<core::data>(res_en), res_de);
        if (core::type_cast<core::data>(str_long) == core::type_cast<core::data>(res_de))
            trace_msg("aes long encrypt: pass.");
        else
            trace_msg("aes long encrypt: failed.");
    }
    
    if (1)
    {
        rsa key;
        if (key.generate())
        {
            core::vector<byte> sec_text;
            core::vector<byte> plain_text;
            
            key.encrypt(core::type_cast<core::data>(str_short), sec_text);
            key.decrypt(core::type_cast<core::data>(sec_text), plain_text);                    
            if (core::type_cast<core::data>(str_short) == core::type_cast<core::data>(plain_text))
                trace_msg("rsa short encrypt: pass.");
            else
                trace_msg("rsa short encrypt: failed.");
            
            key.encrypt(core::type_cast<core::data>(str_long), sec_text);
            key.decrypt(core::type_cast<core::data>(sec_text), plain_text);                    
            if (core::type_cast<core::data>(str_long) == core::type_cast<core::data>(plain_text))
                trace_msg("rsa long encrypt: pass.");
            else
                trace_msg("rsa long encrypt: failed.");
        }
        else
        {
            trace_msg("failed to generate rsa key");
        }
    }
        
    return 0;
}

core::string str_short = "1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxc";

core::string str_long = "1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./";