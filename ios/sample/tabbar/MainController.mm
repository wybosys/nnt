
# import "Foundation+NNT.h"
# import "MainController.h"

NNTAPP_BEGIN

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

NNTAPP_END