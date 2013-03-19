
# include "Foundation+NNT.h"
# include "MainController.h"
# include "UIHudView.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Orange());
    
    simple.set_text(@"simple");
    lines.set_text(@"lines");
    progress.set_text(@"progress");
    
    add_sub(simple);
    add_sub(lines);
    add_sub(progress);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    
    lnr << (pixel)30 << (pixel)30 << (pixel)30;
    lnr << (flex)1;
    
    simple.set_frame(lyt << lnr);
    lines.set_frame(lyt << lnr);
    progress.set_frame(lyt << lnr);
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    view().simple.connect(kSignalButtonClicked, _action(_class::act_simple), this);
    view().lines.connect(kSignalButtonClicked, _action(_class::act_lines), this);
    view().progress.connect(kSignalButtonClicked, _action(_class::act_progress), this);
}

void MainController::act_simple()
{
    ui::Hud::show(@"SIMPLE TEXT");
}

void MainController::act_lines()
{
    ui::Hud::show(@"LINE 0\r\nLINE 1\r\nLINE 2\r\n");
}

ui::HudProgress* hudpro = NULL;

void MainController::act_progress()
{
    hudpro = new ui::HudProgress;
    hudpro->open();
    
    perform(_perform_action(_class::act_progress_end), 5);
}

void MainController::act_progress_end()
{
    hudpro->close();
    delete hudpro;
}

NNTAPP_END