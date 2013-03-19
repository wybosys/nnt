
# include "Foundation+NNT.h"
# include "MainController.h"
# include "SecController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_sec.set_text(@"SEC");
    btn_sec.set_text(ui::Color::Black());
    
    add_sub(btn_sec);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    lyt << lnr;
    btn_sec.set_frame(lyt << lnr);
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    set_title(@"MAIN");
    view().btn_sec.connect(kSignalButtonClicked, _action(MainController::act_sec), this);
    navigation();
}

void MainController::act_sec(EventObj&)
{    
    SecController* ctlr = SecController::New();
    navigation().push(ctlr);                    
    ctlr->Release();
}

NNTAPP_END
