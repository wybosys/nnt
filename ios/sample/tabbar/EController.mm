
# import "Foundation+NNT.h"
# import "EController.h"

NNTAPP_BEGIN

EView::EView()
{
    set_background(wsi::ui::Color::Gray());
}

void EView::layout_subviews()
{
    
}

void EController::view_loaded()
{
    connect(kSignalViewAppear, _action(EController::act_appear), this);
    connect(kSignalViewDisappear, _action(EController::act_disappear), this);
}

void EController::act_appear()
{
    trace_msg(@"E appear");
}

void EController::act_disappear()
{
    trace_msg(@"E disappear");
}

NNTAPP_END