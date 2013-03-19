
# import "WSIFoundation.h"
# import "MainController.h"

WSIAPP_BEGIN

using namespace ::wsi;

MainController::MainController()
{
    tabbar().set_preferred_count(5);
    tabbar().set_height(100);
    tabbar().set_background(wsi::ui::Color::Orange());
    
    // add.
    add(ctlr_a);
    add(ctlr_b);
    add(ctlr_c);
    add(ctlr_d);
    
    update();    
}

WSIAPP_END