
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    img.set_image(ui::Image::Retina(@"logo.png"));
    view.set_background(ui::Color::White());
    
    add_sub(img);
    add_sub(view);
    
    view.set_frame(cg::Rect(10, 10, 10, 10));
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    CGRectLayoutHBox lyta(lyt << lnr);
    CGRectLayoutLinear lnra(lyta);
    lnra << (flex)1 << (flex)1 << (flex)1;
    lyta << lnra;
    img.set_frame(lyta << lnra);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().view.connect(kSignalViewClicked, _action(_class::act_view), this);
}

void MainController::act_view()
{
    core::Confirm::info(tostr(view().scale_factor()));
}

NNTAPP_END