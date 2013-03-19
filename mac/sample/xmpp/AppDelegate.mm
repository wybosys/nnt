
# include "wsi/WSIFoundation.h"
# include "AppDelegate.h"
# include "MainController.h"

WSIAPP_BEGIN

void App::load()
{
    MainController* ctlr = ::wsiapp::MainController::New();
    set_root(ctlr);
    ctlr->Release();
}

WSIAPP_END
