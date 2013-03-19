
# import "Foundation+NNT.h"
# import "DController.h"

NNTAPP_BEGIN

DView::DView()
{
    set_background(wsi::ui::Color::Gray());
}

void DView::layout_subviews()
{
    
}

DController::DController()
{
    set_title(@"D");
    set_title(wsi::ui::Image(@"d.png"));
}

void DController::view_loaded()
{
    
}

NNTAPP_END