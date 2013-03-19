
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    
}

void MainView::layout_subviews()
{
    
}

MainController::MainController()
{
    connect(kSignalDeviceShaked, _action(_class::act_shaked));
}

void MainController::view_loaded()
{

}

void MainController::act_shaked()
{
    //ui::Device::Shake();
    core::Msgbox::info(@"SHAKED");
}

WSIAPP_END
