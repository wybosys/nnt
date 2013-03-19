
# include "WSIFoundation.h"
# include "AppDelegate.h"
# include "MainController.h"

WSIAPP_BEGIN

void App::load()
{
    enable_filecache();
    
    /*
    ::MainController* ctlr = [[::MainController alloc] init];
    ctlr.orientationEnable = UIOrientationEnableAll;
    nsobject().rootViewController = ctlr;
    [ctlr release];
     */
    
    set_root(ctlr);
    
}

WSIAPP_END
