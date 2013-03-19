
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{    
    txt0.set_borderstyle(UITextBorderStyleBezel);
    txt1.set_borderstyle(UITextBorderStyleRoundedRect);
    
    add_sub(txt0);
    add_sub(txt1);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)30 << (flex)1 << (pixel)30;
    
    txt0.set_frame(lyt << lnr);
    lyt << lnr;
    txt1.set_frame(lyt << lnr);
}

MainController::MainController()
{
    set_orientation(UIOrientationEnableAll);
}

void MainController::view_loaded()
{
    
}

WSIAPP_END
