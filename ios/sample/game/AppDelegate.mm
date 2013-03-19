
# include "Foundation+NNT.h"
# include "AppDelegate.h"

NNTAPP_BEGIN

void App::load()
{
    enable_icloud();    
    set_appstore(@"https://itunes.apple.com/us/app/game-wsi/id606130983?ls=1&mt=8");
    
    set_root(ctlr);
}

NNTAPP_END
