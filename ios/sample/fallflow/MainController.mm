
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    add_sub(fall);
}

void MainView::layout_subviews()
{
    fall.view().set_frame(bounds());
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    
}

WSIAPP_END
