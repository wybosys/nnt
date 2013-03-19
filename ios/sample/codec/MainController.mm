
# include "WSIFoundation.h"
# include "MainController.h"
# include "SystemAudio.h"

WSIAPP_BEGIN

MainView::MainView()
{
    btn_blow.set_text(@"BLOW");
    btn_bottle.set_text(@"BOTTLE");
    btn_glass.set_text(@"GLASS");
    
    add_sub(btn_blow);
    add_sub(btn_bottle);
    add_sub(btn_glass);
    
    btn_blow.connect(kSignalButtonClicked, _action(_class::act_blow), this);
    btn_bottle.connect(kSignalButtonClicked, _action(_class::act_bottle), this);
    btn_glass.connect(kSignalButtonClicked, _action(_class::act_glass), this);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)30 << (flex)1;
    
    {
        CGRectLayoutHBox ilyt(lyt << lnr);
        CGRectLayoutLinear ilnr(ilyt);
        ilnr << (flex)1 << (flex)1 << (flex)1;
        
        btn_blow.set_frame(ilyt << ilnr);
        btn_bottle.set_frame(ilyt << ilnr);
        btn_glass.set_frame(ilyt << ilnr);
    }
}

void MainView::act_blow()
{
    ns::SystemAudio::Play(@"BLOW");
}

void MainView::act_bottle()
{
    ns::SystemAudio::Play(@"BOTTLE");
}

void MainView::act_glass()
{
    ns::SystemAudio::Play(@"GLASS");
}

MainController::MainController()
{
    ns::SystemAudio::Register(@"BLOW", ns::URL::Bundle(@"aif.bundle/Blow.aiff"));
    ns::SystemAudio::Register(@"BOTTLE", ns::URL::Bundle(@"aif.bundle/Bottle.aiff"));
    ns::SystemAudio::Register(@"GLASS", ns::URL::Bundle(@"aif.bundle/Glass.aiff"));
}

void MainController::view_loaded()
{
    
}

WSIAPP_END
