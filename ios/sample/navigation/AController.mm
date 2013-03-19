
# import "Foundation+NNT.h"
# import "AController.h"
# import "BController.h"

NNTAPP_BEGIN

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
    view().connect(kSignalViewClicked, _action(AController::act_clicked), this);
    connect(kSignalViewAppear, _action(AController::act_appear), this);
    connect(kSignalViewDisappear, _action(AController::act_disappear), this);
}

void AController::act_appear()
{
    trace_msg(@"A appear");
        
    // set top.
    ui::BevelButton btn;
    btn.set_size(cg::Size(150, navigation().topbar().height()));
    btn.set_removable(false);
    btn.set_text(@"A TOP BUTTON");
    navigation().topbar().top_item().set_title(btn);
    btn.connect(kSignalButtonClicked, _action(_class::act_top), this);
}

void AController::act_disappear()
{
    trace_msg(@"A disappear");
}

void AController::act_clicked()
{
    navigation().push(ui::auto_release<ui::WrapController<ui::Navigatilize<BController> > >::instance());
}

void AController::act_top()
{
    trace_msg(@"click top item.");
}

NNTAPP_END