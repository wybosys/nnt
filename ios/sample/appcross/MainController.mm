
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_a.set_text(@"A");
    btn_b.set_text(@"B");
    
    add_sub(btn_a);
    add_sub(btn_b);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    btn_a.set_frame(lyt << lnr);
    btn_b.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn_a.connect(kSignalButtonClicked, _action(_class::act_a));
    view().btn_b.connect(kSignalButtonClicked, _action(_class::act_b));
}

void MainController::act_a()
{
    Application::getInstance().open(ns::URL(@"wsi-sample-a://com.wsi.sample.a"));
}

void MainController::act_b()
{
    Application::getInstance().open(ns::URL(@"wsi-sample-b://com.wsi.dev"));
}

NNTAPP_END
