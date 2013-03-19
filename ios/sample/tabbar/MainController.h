
# ifndef __MAIN_CTLR_4771A78F1A254188BFD0F478FD3539D8_H_INCLUDED
# define __MAIN_CTLR_4771A78F1A254188BFD0F478FD3539D8_H_INCLUDED

# import "AController.h"
# import "BController.h"
# import "CController.h"
# import "DController.h"

NNTAPP_BEGIN

class MainController
: public wsi::ui::TabBarController
{
public:
    
    MainController();

protected:
    
    nntapp::AController ctlr_a;
    nntapp::BController ctlr_b;
    nntapp::CController ctlr_c;
    nntapp::DController ctlr_d;
};

NNTAPP_END

# endif