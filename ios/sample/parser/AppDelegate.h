
# include "HtmlController.h"
# include "XmlController.h"

NNTAPP_BEGIN

class App
: public Application
{
public:
    void load();
    
    XmlController ctlr;
    //HtmlController ctlr;
    
};

NNTAPP_END
