
# ifndef MAIN_APP
# define MAIN_APP

# include "MainController.h"

NNTAPP_BEGIN

class App
: public Application
{
public:
    
    void load();
    MainController ctlr;

};

NNTAPP_END

# endif
