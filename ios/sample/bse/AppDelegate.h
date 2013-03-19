
# ifndef MAIN_APP
# define MAIN_APP

# include "MainController.h"

WSIAPP_BEGIN

class App
: public Application
{
public:
    
    void load();
    MainController ctlr;

};

WSIAPP_END

# endif
