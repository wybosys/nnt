
# include "MainController.h"

NNTAPP_BEGIN

class App
: public cross::Application
{
public:
    void load();
    MainController ctlr;
};

NNTAPP_END
