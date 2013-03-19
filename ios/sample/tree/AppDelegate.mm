
# include "WSIFoundation.h"
# include "AppDelegate.h"

WSIAPP_BEGIN

void App::load()
{
    ctlr.set_orientation(UIOrientationEnableAll);
    set_root(ctlr);
}

WSIAPP_END
