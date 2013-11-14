
# ifndef APPDELEGATE
# define APPDELEGATE

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
