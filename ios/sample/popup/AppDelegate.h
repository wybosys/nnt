
# include "MainController.h"

WSIAPP_BEGIN

class App
: public ::wsi::Application
{
public:
    void load();
    ::wsiapp::MainController ctlr;
};

WSIAPP_END
