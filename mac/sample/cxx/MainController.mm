
# include "wsi/WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(cg::Color::Gray());
    
    btn_msg.set_text(@"message");    
    add_sub(btn_msg);
    btn_msg.connect(kSignalAction, _action(MainView::act_msg), this);
}

void MainView::layout_subviews()
{
    lb::CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)30 << (flex)1;
    
    lb::CGRectLayoutHBox lytb(lyt << lnr);
    CGRectLayoutLinear lnrb(lytb);
    lnrb << (flex)1;
    btn_msg.set_frame(lytb << lnrb);
}

void MainView::act_msg()
{
    NSMessageBox* box = [[NSMessageBox alloc] initWithTitle:@"TEST"];
    [box show];
    [box release];
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

WSIAPP_END