
# include "Foundation+NNT.h"
# include "AppDelegate.h"
# include "WSIClipboard.h"

NNTAPP_BEGIN

void App::load()
{
    set_root(ctlr);
}

void App::background()
{
    while(!is_activity())
    {
        sys::Clipboard cp;
        if (cp.is_string())
        {
            ns::LocalNotification noti;
            noti.set_body(cp);
            noti.execute();
            
            cp.clear();
        }
        sleep_second(1);
    }
}

NNTAPP_END
