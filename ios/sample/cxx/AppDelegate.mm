
# include "WSIFoundation.h"
# include "AppDelegate.h"
# include "MainController.h"

WSIAPP_BEGIN

void App::load()
{
    ui::Instance<ui::Navigatilize<MainController> > ctlr;
    ctlr->set_orientation(UIOrientationEnableAll);
    set_root(ctlr);
}

WSIAPP_END
