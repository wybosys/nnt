
# include "WSIFoundation.h"
# include "AppDelegate.h"

WSIAPP_BEGIN

void App::load()
{
    ui::Instance<ui::Navigatilize<ui::CHMController> > ctlr;
    ctlr->root().read_named(@"help.chm");
    ctlr->view().set_background(ui::Color::White());
    set_root(ctlr);
}

WSIAPP_END
