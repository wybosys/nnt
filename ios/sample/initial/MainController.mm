
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

void MainView::layout_subviews()
{
    set_background(ui::Color::Orange());
}

MainController::MainController()
{
    connect(kSignalViewAppear, _action(_class::act_appear));
    connect(kSignalViewDisappear, _action(_class::act_disappear));
}

void MainController::view_loaded()
{
    trace_msg(@"view loaded.");
}

void MainController::act_appear()
{
    trace_msg(@"view appear.");
}

void MainController::act_disappear()
{
    trace_msg(@"view disappear.");
}

WSIAPP_END
