
# include "Foundation+NNT.h"
# include "AController.h"

NNTAPP_BEGIN

AView::AView()
{
    set_background(ui::Color::Orange());
    
    btn_dismiss.set_text(@"DISMISS");
    
    add_sub(btn_dismiss);
}

void AView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)30 << (flex)1;
    
    btn_dismiss.set_frame(lyt << lnr);
}

AController::AController()
{
    set_title(@"A");
    
    connect(kSignalViewAppear, _action(_class::act_appear), this);
}

AController::~AController()
{
    trace_msg(@"AController::destroy.");   
}

void AController::view_loaded()
{
    view().btn_dismiss.connect(kSignalButtonClicked, _action(_class::act_dismiss), this);
}

void AController::act_dismiss()
{
    dismiss();
}

void AController::act_appear()
{
    trace_msg(@"AController::appear.");
    navigation().topbar().set_visible(false);
}

NNTAPP_END