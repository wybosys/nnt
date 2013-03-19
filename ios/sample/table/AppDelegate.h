
# include "MainController.h"

NNTAPP_BEGIN

class App
: public ::wsi::Application
{
public:
    void load();
    ::nntapp::MainController ctlr;
};

NNTAPP_END
