
# ifndef _APPDELEGATE
# define _APPDELEGATE

# include "MainController.h"
# include <CCApplication.h>

NNTAPP_BEGIN

class App
: public Application
{
public:
    
    void load();
    
    MainController ctlr;
    
};

class ccApp
: public cocos2d::CCApplication
{
public:
    
    ccApp();
    ~ccApp();
    
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
    
};

NNTAPP_END

# endif
