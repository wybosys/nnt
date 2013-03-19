
# ifndef __MAIN_CTLR_4771A78F1A254188BFD0F478FD3539D8_H_INCLUDED
# define __MAIN_CTLR_4771A78F1A254188BFD0F478FD3539D8_H_INCLUDED

# import "AController.h"
# import "BController.h"
# import "CController.h"
# import "DController.h"

WSIAPP_BEGIN

class MainController
: public wsi::ui::TabBarController
{
public:
    
    MainController();

protected:
    
    wsiapp::AController ctlr_a;
    wsiapp::BController ctlr_b;
    wsiapp::CController ctlr_c;
    wsiapp::DController ctlr_d;
};

WSIAPP_END

# endif