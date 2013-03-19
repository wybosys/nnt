
# import "WSIFoundation.h"
# import "MainController.h"

using namespace wsi;

WSIAPP_BEGIN

MainView::MainView()
{    
    set_background(ui::Color::White());
    
    btn.set_text(@"BUTTON");
    
    add_sub(btn);
    
    btn.set_background(cg::Fill(cg::Color::Red()));
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    btn.set_frame(lyt << lnr);
    lyt << lnr;
}

void MainController::view_loaded()
{
    
}

WSIAPP_END