
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

BackView::BackView()
{
    set_background(ui::Color::Gray());
}

MainView::MainView()
{
    set_background(ui::Color::Orange());
    
    add_sub(page_back);
    add_sub(page);
    
    page.set_count(10);
    page.set_current(0);
    page.set_diameter(10);
    
    page.set_selected(ui::Color::Black());
    page.set_normal(ui::Color::LightGray());
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    
    lnr << (flex)1;
    lnr << (pixel)50;
    lnr << (flex)1;
    
    lyt << lnr;
    
    page.set_frame(lyt << lnr);
    
    cg::Rect rc_back = CGRectInset(page.frame().location(page.stage_region()), -5, -5);
    page_back.set_frame(rc_back);
    page_back.layer().set_clip(true);
    page_back.layer().set_corner(rc_back.height() / 2);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

WSIAPP_END
