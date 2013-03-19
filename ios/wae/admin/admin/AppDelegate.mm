
# include "wae.h"
# include "AppDelegate.h"

WAE_BEGIN

void App::load()
{
    enable_filecache();
    set_root(ctlr);
}

WAE_END
