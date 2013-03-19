
# include "Foundation+NNT.h"
# include "AppDelegate.h"
# include "MainController.h"

NNTAPP_BEGIN

void App::load()
{
    MainController* ctlr = nntapp::MainController::New();
    set_root(ctlr);
    ctlr->Release();
}

NNTAPP_END
