
# import "Foundation+NNT.h"
# import "CController.h"

NNTAPP_BEGIN

CView::CView()
{
    set_background(wsi::ui::Color::Blue());
}

void CView::layout_subviews()
{
    
}

CController::CController()
{
    set_title(@"C");
    set_title(wsi::ui::Image(@"c.png"));
}

void CController::view_loaded()
{
    
}

NNTAPP_END