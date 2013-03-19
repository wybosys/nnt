
# include "WSIFoundation.h"
# include "AppDelegate.h"

WSIAPP_BEGIN

void App::load()
{
    set_root(ctlr);
    
    connect(kSignalMemoryWarning, _action(App::act_memory), this);
}

void App::act_memory()
{
    
}

WSIAPP_END
