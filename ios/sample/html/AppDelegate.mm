
# include "WSIFoundation.h"
# include "AppDelegate.h"
# include "MainController.h"

WSIAPP_BEGIN

void App::load()
{
    ctlr.set_orientation(UIOrientationEnableAll);
    set_root(ctlr);
}

WSIAPP_END
