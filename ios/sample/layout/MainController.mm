
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Gray());
    
    add_sub(r0);
    add_sub(r1);
    add_sub(r2);
    
    r0.set_background(ui::Color::Red());
    r1.set_background(ui::Color::Green());
    r2.set_background(ui::Color::Blue());
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    
    CGRectLayoutHBox lytr(lyt << lnr);
    CGRectLayoutLinear lnrr(lytr);
    lnrr << (flex)1 << whar(16, 9) << (flex)1;
    r0.set_frame(lytr << lnrr);
    r1.set_frame(lytr << lnrr);
    r2.set_frame(lytr << lnrr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

WSIAPP_END
