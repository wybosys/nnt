
# include "MainController.h"
# include "ImageController.h"

WSIAPP_BEGIN

class App
: public Application
{
public:
    void load();
    
    MainController ctlr;
    //ImageController ctlr;
    
};

WSIAPP_END
