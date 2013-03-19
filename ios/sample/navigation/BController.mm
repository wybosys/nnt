
# import "Foundation+NNT.h"
# import "BController.h"

NNTAPP_BEGIN

BView::BView()
{
    set_background(wsi::ui::Color::Green());
}

void BView::layout_subviews()
{
    
}

BController::BController()
{
    set_title(@"B");
    set_title(wsi::ui::Image(@"b.png"));
}

BController::~BController()
{
    trace_msg(@"B destroy");
}

void BController::view_loaded()
{
    connect(kSignalViewAppear, _action(BController::act_appear), this);
    connect(kSignalViewDisappear, _action(BController::act_disappear), this);
}

void BController::act_appear()
{
    trace_msg(@"B appear");
}

void BController::act_disappear()
{
    trace_msg(@"B disappear");
}

NNTAPP_END