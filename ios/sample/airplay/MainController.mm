
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Black());
    
    add_sub(airplay);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    airplay.set_frame(lyt << lnr);
}

MainController::MainController()
{
    connect(kSignalRemoteControlEvent, _action(_class::act_remotecontrol));
}

void MainController::view_loaded()
{
    
}

void MainController::act_remotecontrol(EventObj& evt)
{
    
}

WSIAPP_END
