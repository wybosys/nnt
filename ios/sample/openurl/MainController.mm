
# import "Foundation+NNT.h"
# import "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    add_sub(inpUrl);
    add_sub(btnGo);
    
    inpUrl.set_placeholder(@"please input open url");
    btnGo.set_text(@"GO");
}

void MainView::layout_subviews()
{
    layout::vbox box(bounds());
    layout::linear lnr(box);
    lnr << (flex)1 << (pixel)30 << (pixel)30 << (flex)1;
    inpUrl.set_frame(box << lnr);
    btnGo.set_frame(box << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btnGo.connect(kSignalButtonClicked, _action(_class::act_go), this);
}

void MainController::act_go()
{
    BOOL suc = [[UIApplication sharedApplication] canOpenURL:ns::URL(view().inpUrl.text())];
    if (suc == NO) {
        core::Confirm::info(@"can not open the input url");
        return;
    }
    
    [[UIApplication sharedApplication] openURL:ns::URL(view().inpUrl.text())];
}

NNTAPP_END
