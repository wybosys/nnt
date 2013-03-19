
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

LogoHeaderView::LogoHeaderView()
{
    add_sub(logo);
    logo.send_toback();
    
    logo.set_image(ui::Image(@"logobg.png"));
}

void LogoHeaderView::layout_subviews()
{
    layout::hbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << whar(1, 1) << (flex)1;
    lyt << lnr;
    logo.set_frame(lyt << lnr);
}

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_center.set_background(ui::Color::Black());
    add_sub(btn_center);
    
    top.set_background(ui::Color::Red());
    bottom.set_background(ui::Color::Blue());
    
    top.normal_text().set_text(@"TOP HEADER");
    top.action_text().set_text(@"TOP ACTION HEADER");
    bottom.normal_text().set_text(@"BOTTOM HEADER");
    bottom.action_text().set_text(@"BOTTOM ACTION HEADER");
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    CGRectLayoutHBox lyth(lyt << lnr);
    CGRectLayoutLinear lnrh(lyth);
    lnrh << (flex)1 << (flex)1 << (flex)1;
    lyth << lnrh;
    btn_center.set_frame(lyth << lnrh);
}

MainController::MainController()
{
    PASS;
}

void MainController::view_loaded()
{
    //view().set_deceleration_rate(0);
    view().set_content_size(cg::Size(320, 900));
    //set_content_size(CGSizeMake(320, 320));
    
    view().set_topheader(view()->top);
    view().set_bottomheader(view()->bottom);
    
    view()->top.connect(kSignalAction, _action(MainController::act_top), this);
    view()->bottom.connect(kSignalAction, _action(MainController::act_bottom), this);
}

void MainController::act_top(EventObj &)
{
    trace_msg(@"TOP REFRESH");
}

void MainController::act_bottom(EventObj &)
{
    trace_msg(@"BOTTOM REFRESH");
}

WSIAPP_END