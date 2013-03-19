
# include <wsi/WSIFoundation.h>
# include "AppDelegate.h"
# include <wsi/Cross/SocketServer.h>

WSIAPP_BEGIN

void App::load()
{
    
    cross::SocketServer serv;
    bool suc = false;
    
    if (0)
    {
        suc = serv.listen("127.0.0.1:7777");
        if (suc)
            trace_msg(@"success create 7777 on localhost.");
        serv.stop();
    }
    
    if (0)
    {
        suc = serv.listen("*:7778");
        if (suc)
            trace_msg(@"success create 7778 on any address.");
    }

}

WSIAPP_END
