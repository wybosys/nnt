
# include "MainController.h"

WSIAPP_BEGIN

class App
: public Application
{
public:
    void load();
    void act_memory();
    MainController ctlr;
};

WSIAPP_END
