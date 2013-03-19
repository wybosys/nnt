
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

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

NNTAPP_END
