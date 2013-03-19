
# include "Foundation+NNT.h"
# include "MainController.h"
# include "AController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    btn_present.set_text(@"PRESENT");
    btn_form.set_text(@"FORM");
    btn_desktop.set_text(@"DESKTOP");
    
    add_sub(btn_present);
    add_sub(btn_form);
    add_sub(btn_desktop);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds(), 10);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)30 << (pixel)30 << (pixel)30 << (flex)1;
    
    lyt << lnr;
    btn_present.set_frame(lyt << lnr);
    btn_form.set_frame(lyt << lnr);
    btn_desktop.set_frame(lyt << lnr);
}

MainController::MainController()
{
    set_title(@"MAIN");
}

void MainController::view_loaded()
{
    view().btn_present.connect(kSignalButtonClicked, _action(_class::act_present), this);
    view().btn_form.connect(kSignalButtonClicked, _action(_class::act_form), this);
    view().btn_desktop.connect(kSignalButtonClicked, _action(_class::act_desktop), this);
}

void MainController::act_present()
{
    ui::Navigatilize<AController>* ctlr = ui::Navigatilize<AController>::New();
    present(ctlr);
    ctlr->Release();
}

void MainController::act_form()
{
    ui::Navigatilize<AController>* ctlr = ui::Navigatilize<AController>::New();
    ctlr->set_presentation(UIModalPresentationFormSheet);
    present(ctlr);
    ctlr->Release();
}

void MainController::act_desktop()
{
    ui::Desktop* desk = ui::Desktop::New();
    
    ui::Label lbl;
    lbl.set_text(@"LABEL ON DESK");
    lbl.set_removable(false);
    lbl.set_frame(100, 100, 200, 100);
    lbl.set_background(ui::Color::Orange());
    desk->add_sub(lbl);
    
    desk->set_autoclose(true);
    desk->show();
    desk->Release();
}

NNTAPP_END