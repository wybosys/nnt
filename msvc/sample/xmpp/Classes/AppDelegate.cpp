
# include <wsi/WSIFoundation.h>
# include "AppDelegate.h"
# include "MainController.h"

WSIAPP_BEGIN

void App::load()
{
	window()->resize(ui::uc::Size(800, 600));

    set_root(ctlr);

	ctlr.view();
}

WSIAPP_END
