
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{

}

void MainView::layout_subviews()
{
    
}

MainController::MainController()
{
    set_fullscreen(true);
}

void MainController::view_loaded()
{
    CCApplication::sharedApplication()->run();
}

NNTAPP_END
