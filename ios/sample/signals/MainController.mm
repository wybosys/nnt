
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    add_sub(block);
    
    block.set_background(ui::Color::Blue());
    block.connect(kSignalViewClicked, _action(_class::act_clicked), this);
}

void MainView::act_clicked()
{
    trace_msg(@"clicked block view");
}

void MainView::layout_subviews()
{
    layout::hbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    block.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().set_background(ui::Color::Orange());
    view().connect(kSignalViewClicked, _action(_class::act_clicked), this);
}

void MainController::act_clicked()
{
    trace_msg(@"clicked");
}

NNTAPP_END
