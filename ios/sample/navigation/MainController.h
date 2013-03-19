
# ifndef __MAIN_CTLR_E74BC48BAF9C441CA646A47561C43ECB_H_INCLUDED
# define __MAIN_CTLR_E74BC48BAF9C441CA646A47561C43ECB_H_INCLUDED

# include "AController.h"

NNTAPP_BEGIN

class MainController
: public wsi::ui::NavigationController
{
public:
    
    MainController();
    
    void act_appear();
    void act_click();
    
    AController ctlr;
};

NNTAPP_END

# endif