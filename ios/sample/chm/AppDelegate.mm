
# include "Foundation+NNT.h"
# include "AppDelegate.h"

NNTAPP_BEGIN

void App::load()
{
    ui::Instance<ui::Navigatilize<ui::CHMController> > ctlr;
    ctlr->root().read_named(@"help.chm");
    ctlr->view().set_background(ui::Color::White());
    set_root(ctlr);
}

NNTAPP_END
