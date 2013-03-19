
# include "Foundation+NNT.h"
# include "MainController.h"
# include "ColorPalette.h"

NNTAPP_BEGIN

MainView::MainView()
{
    roller.set_background(ui::Color::White());
    
    core::ColorWheel cw;
    for (uint i = 0; i < 5; ++i)
    {
        ui::SimpleView view;
        view.set_removable(false);
        view.set_background(ui::Color::RGB(cw.next()));
        roller.add(view);
    }
    
    add_sub(roller);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    roller.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

NNTAPP_END
