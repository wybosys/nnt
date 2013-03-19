
# import "WSIFoundation.h"
# import "AController.h"

WSIAPP_BEGIN

AView::AView()
{
    set_background(wsi::ui::Color::Red());
    add_sub(ctlr);
}

void AView::layout_subviews()
{
    wsi::CGRectLayoutVBox lyt(bounds());
    wsi::CGRectLayoutLinear lnr(lyt);
    lnr << (wsi::flex)1 << (wsi::flex)1;
    ctlr.view().set_frame(lyt << lnr);
}

AController::AController()
{
    set_title(@"A");
    set_title(wsi::ui::Image(@"a.png"));
}

void AController::view_loaded()
{
    connect(kSignalViewAppear, _action(AController::act_appear), this);
    connect(kSignalViewDisappear, _action(AController::act_disappear), this);
}

void AController::act_appear()
{
    trace_msg(@"A appear");
}

void AController::act_disappear()
{
    trace_msg(@"A disappear");
}

WSIAPP_END