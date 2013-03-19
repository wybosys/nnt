
# include "Foundation+NNT.h"
# include "AppDelegate.h"
# include "MainController.h"

NNTAPP_BEGIN

void App::load()
{
    ui::Instance<ui::Navigatilize<MainController> > ctlr;
    set_root(ctlr);
}

NNTAPP_END
