
# include "Foundation+NNT.h"
# include "MainController.h"
# include "UIPopoverController+NNT.h"

NNTAPP_BEGIN

MainView::MainView()
{
    pop.set_text(@"POP");
    
    add_sub(pop);
    
    set_background(ui::Color::White());
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (pixel)30 << (flex)1;
    lyt << lnr;
    CGRectLayoutHBox lyth(lyt << lnr);
    CGRectLayoutLinear lnrh(lyth);
    lnrh << (flex)1 << (flex)1 << (flex)1;
    lyth << lnrh;
    pop.set_frame(lyth << lnrh);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().pop.connect(kSignalButtonClicked, _action(_class::act_pop), this);
}

void MainController::act_pop()
{
    typedef ui::Popover<ui::Controllerize<ui::SimpleView> > pop_type;
    pop_type* pop = pop_type::New();
    pop->connect(kSignalDismiss, _action(_class::act_dismiss), this);
    pop->set_direction(UIPopoverArrowDirectionAny);
    pop->set_content(cg::Size(0, 400));
    pop->content.view().set_background(ui::Color::Orange());
    pop->present(view().pop.frame(), view());
    pop->Release();
}

void MainController::act_dismiss()
{
    trace_msg(@"DISMISSED.");
}

NNTAPP_END
