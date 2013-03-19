
# include "WSIFoundation.h"
# include "MainController.h"
# include "AbstractCache.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Orange());
    
    add_sub(btn_save);
    add_sub(btn_load);
    
    btn_save.set_text(@"SAVE");
    btn_load.set_text(@"LOAD");
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    
    layout::hbox lyth(lyt << lnr);
    layout::linear lnrh(lyth);
    lnrh << (flex)1 << (flex)1 << (flex)1 << (flex)1;
    
    lyth << lnrh;
    btn_save.set_frame(lyth << lnrh);
    btn_load.set_frame(lyth << lnrh);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn_save.connect(kSignalButtonClicked, _action(_class::act_save), this);
    view().btn_load.connect(kSignalButtonClicked, _action(_class::act_load), this);
}

void MainController::act_save()
{
    core::Cache::Default().set(@"TEST", @"TEST").set_overdate(DT_1MIN);
}

void MainController::act_load()
{
    core::Confirm::info(core::Cache::Default().find(@"TEST"));
}

WSIAPP_END
