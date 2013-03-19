
# include "MainController.h"

NNTAPP_BEGIN

class App
: public Application
{
public:
    App();
    ~App();
    void load();
    MainController ctlr;
};

NNTAPP_END
