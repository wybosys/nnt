
# import "WSIFoundation.h"
# import "CController.h"

WSIAPP_BEGIN

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

WSIAPP_END