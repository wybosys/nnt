
# include "MainController.h"
# include "ImageController.h"

NNTAPP_BEGIN

class App
: public Application
{
public:
    void load();
    
    MainController ctlr;
    //ImageController ctlr;
    
};

NNTAPP_END
