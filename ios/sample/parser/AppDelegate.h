
# include "HtmlController.h"
# include "XmlController.h"

WSIAPP_BEGIN

class App
: public Application
{
public:
    void load();
    
    XmlController ctlr;
    //HtmlController ctlr;
    
};

WSIAPP_END
