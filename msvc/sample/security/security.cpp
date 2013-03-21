// security.cpp : Defines the entry point for the console application.
//

# include <nnt/Foundation+NNT.h>
# include <nnt/Security/Security+NNT.h>

NNTAPP_BEGIN

extern core::string str_long;
extern core::string str_short;

class App
    : public cross::Console
{
public:

    void load()
    {
        if (1)
        {
            core::string dig = md5::digest(core::type_cast<core::data>(str_long));
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
            rsa key;
            if (key.generate())
            {
                core::vector<byte> sec_text;
                core::vector<byte> plain_text;

                key.encrypt(core::type_cast<core::data>(str_short), sec_text);
                key.decrypt(core::type_cast<core::data>(sec_text), plain_text);                    
                if (core::type_cast<core::data>(str_short) == core::type_cast<core::data>(plain_text)) 
                {
                    trace_msg("rsa short encrypt: pass.");
                }
                else
                {
                    trace_msg("rsa short encrypt: failed.");
                }

                key.encrypt(core::type_cast<core::data>(str_long), sec_text);
                key.decrypt(core::type_cast<core::data>(sec_text), plain_text);                    
                if (core::type_cast<core::data>(str_long) == core::type_cast<core::data>(plain_text))
                {
                    trace_msg("rsa long encrypt: pass.");
                }
                else
                {
                    trace_msg("rsa long encrypt: failed.");
                }
            }
            else
            {
                trace_msg("failed to generate rsa key");
            }
        }
    }

};

core::string str_short = "1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxc";

core::string str_long = "1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./1234567890-qwertyuiop[]asdfghjklzxcvbnm,./";

NNTAPP_END



int main(int argc, char* argv[])
{   
    ::nntapp::App app;
    return app.execute(argc, argv);
}
