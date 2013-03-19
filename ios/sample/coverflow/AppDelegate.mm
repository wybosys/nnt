
# include "Foundation+NNT.h"
# include "AppDelegate.h"
# include "MainController.h"

NNTAPP_BEGIN

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

NNTAPP_END
