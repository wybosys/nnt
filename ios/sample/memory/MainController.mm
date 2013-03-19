
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

SubView::SubView()
{
    set_background(ui::Color::Blue());
}

void SubView::layout_subviews()
{
    
}

SubController::SubController()
{
    
}

void SubController::view_loaded()
{
    
}

void SubController::imitate()
{
    [*this viewDidUnload];
}

MainView::MainView()
{
    set_background(ui::Color::Orange());
    
    btn_imitate.set_text(@"IMITATE");
    btn_view.set_text(@"USE VIEW");
    
    add_sub(ctlr);
    add_sub(btn_imitate);
    add_sub(btn_view);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    ctlr.view().set_frame(lyt << lnr);
    
    layout::hbox lyt2(lyt << lnr);
    layout::linear lnr2(lyt2);
    lnr2 << (flex)1 << (flex)1;
    btn_imitate.set_frame(lyt2 << lnr2);
    btn_view.set_frame(lyt2 << lnr2);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn_imitate.connect(kSignalButtonClicked, _action(_class::act_imitate), this);
    view().btn_view.connect(kSignalButtonClicked, _action(_class::act_view), this);
}

void MainController::act_imitate()
{
    view().ctlr.imitate();
}

void MainController::act_view()
{
    view().relayout();
}

WSIAPP_END
