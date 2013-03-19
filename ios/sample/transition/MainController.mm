
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    add_sub(btn_a);
    
    btn_a.set_text(@"BUTTON A");
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    btn_a.set_frame(lyt << lnr);
}

void MainController::view_loaded()
{
    view().btn_a.connect(kSignalButtonClicked, _action(_class::act_a), this);
}

void MainController::act_a()
{

}

WSIAPP_END
