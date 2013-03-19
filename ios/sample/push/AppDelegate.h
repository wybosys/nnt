
# include "MainController.h"

WSIAPP_BEGIN

class App
: public Application
{
    typedef App _class;
    
public:
    
    void load();
    MainController ctlr;
    
protected:
    
    void act_devicetoken(EventObj&);
    void act_remotenoti(EventObj&);
    
};

WSIAPP_END
