
# include "WSIFoundation.h"
# include "MainController.h"
# include "WSIConfiguration.h"
# include "Context.h"
# include "User.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Orange());
    
    si_set.set_text(@"SI SET");
    si_get.set_text(@"SI GET");
    
    add_sub(si_key);
    add_sub(si_value);
    add_sub(si_set);
    add_sub(si_get);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    CGRectLayoutVBox lytsi(lyt << lnr);
    CGRectLayoutLinear lnrsi(lytsi);
    lnrsi << (pixel)30 << (flex)1 << (pixel)30;
    si_key.set_frame(lytsi << lnrsi);
    si_value.set_frame(lytsi << lnrsi);
    CGRectLayoutHBox lytsib(lytsi << lnrsi);
    CGRectLayoutLinear lnrsib(lytsib);
    lnrsib << (flex)1 << (flex)1;
    si_set.set_frame(lytsib << lnrsib);
    si_get.set_frame(lytsib << lnrsib);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().si_set.connect(kSignalButtonClicked, _action(_class::act_siset), this);
    view().si_get.connect(kSignalButtonClicked, _action(_class::act_siget), this);
    
    // login default.
    context::User().login(@"test");
}

void MainController::act_siset()
{
    context::User().configuration().set(view().si_value.text(), view().si_key.text());
}

void MainController::act_siget()
{
    view().si_value.set_text(context::User().configuration().string(view().si_key.text()));
}

WSIAPP_END
