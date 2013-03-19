
# ifndef APP_DELEGATE
# define APP_DELEGATE

# include "MainController.h"

WSIAPP_BEGIN

class App
: public Application
{
public:
    
    void load();
    MainController ctlr;
    
    virtual void background();
    
};

WSIAPP_END

# endif
