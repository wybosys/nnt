
# include "Foundation+NNT.h"
# include "AppDelegate.h"

NNTAPP_BEGIN

void App::load()
{
    enable_filecache();
    set_root(ctlr);
}

NNTAPP_END
