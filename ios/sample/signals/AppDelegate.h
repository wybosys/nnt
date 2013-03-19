
# include "MainController.h"

WSIAPP_BEGIN

class App
: public Application
{
public:
    App();
    ~App();
    void load();
    MainController ctlr;
};

WSIAPP_END
