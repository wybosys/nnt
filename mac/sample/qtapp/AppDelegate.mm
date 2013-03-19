
# include <wsi/WSIFoundation.h>
# include "AppDelegate.h"

WSIAPP_BEGIN

void App::load()
{
    window()->resize(ui::uc::Size(800, 600));
    
    set_root(ctlr);
}

WSIAPP_END
