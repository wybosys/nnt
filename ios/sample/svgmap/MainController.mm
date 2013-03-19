
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Orange());
    
    add_sub(map);
}

void MainView::layout_subviews()
{
    map.view().set_frame(bounds());
}

MainController::MainController()
{
    set_orientation(UIOrientationEnableAll);
}

void MainController::view_loaded()
{
    
}

WSIAPP_END
