
# include "MainController.h"

NNTAPP_BEGIN

class App
: public Application
{
public:
    void load();
    void act_memory();
    MainController ctlr;
};

NNTAPP_END
