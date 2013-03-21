
# include <nnt/Foundation+NNT.h>
# include "AppDelegate.h"

NNTAPP_BEGIN

void App::load()
{
    window()->resize(ui::uc::Size(800, 600));
    
    set_root(ctlr);
}

NNTAPP_END
