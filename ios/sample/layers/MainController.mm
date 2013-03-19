
# include "WSIFoundation.h"
# include "MainController.h"
# include "WCALayerFliters.h"
# include "WCALayerShapes.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    view.set_frame(cg::Rect(100, 100, 100, 100));
    view.set_background(ui::Color::Black());
    
    add_sub(view);
    
    // set mask.
    /*
    ca::shape::Shape sp;
    sp.path.add_ellipse(view.bounds());
    view.layer().use_mask(sp);
     */
    
    // set filter.
    ca::filter::Shadow filter;
    filter.opacity = 1.f;
    filter.radius = 10;
    view.layer().use_filter(filter);
}

void MainView::layout_subviews()
{
    /*
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1;
    lyt << lnr;
    layout::hbox hyt(lyt << lnr);
    layout::linear hnr(hyt);
    hnr << (flex)1 << (flex)1 << (flex)1;
    hyt << hnr;
    view.set_frame(hyt << hnr);
     */
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

WSIAPP_END
