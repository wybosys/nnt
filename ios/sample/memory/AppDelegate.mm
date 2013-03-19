
# include "Foundation+NNT.h"
# include "AppDelegate.h"

NNTAPP_BEGIN

void App::load()
{
    set_root(ctlr);
    
    connect(kSignalMemoryWarning, _action(App::act_memory), this);
}

void App::act_memory()
{
    
}

NNTAPP_END
