
# ifndef APP_DELEGATE
# define APP_DELEGATE

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
