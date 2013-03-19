
# include "MainController.h"

NNTAPP_BEGIN

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

NNTAPP_END
