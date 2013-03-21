
# include <nnt/Foundation+NNT.h>
# include "AppDelegate.h"
# include "MainController.h"

NNTAPP_BEGIN

void App::load()
{
	window()->resize(ui::uc::Size(800, 600));

    set_root(ctlr);

	ctlr.view();
}

NNTAPP_END
