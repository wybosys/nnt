
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    add_sub(lbl);
    add_sub(lbl2);
    
    lbl.set_font(ui::Font(@"NASAL", 40));
    lbl.set_text(@"HELLO, LABEL!");
    //lbl.set_alignment(UITextAlignmentCenter);
    
    lbl2.set_font(ui::Font(@"NASAL", 40));
    lbl2.set_text(@"HELLO, LABEL TWO!");
    
    add_sub(txt);
    
    txt.set_font(ui::Font(@"NASAL", 30));
    txt.set_text(@"INPUT");
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex).5f << (flex).5f << (flex)1 << (flex)1;
    lyt << lnr;
    
    lbl.set_frame(lyt << lnr);
    lbl2.set_frame(lyt << lnr);
    txt.set_frame(lyt << lnr);
}

MainController::MainController()
{
    set_orientation(UIOrientationEnableAll);
}

void MainController::view_loaded()
{
    view().lbl.start();
    view().lbl2.start();
    
    view().lbl.connect(kSignalMarqueeNext, _action(_class::act_next), this);
}

void MainController::act_next()
{
    view().lbl.set_text(view().lbl.text() + @" NEXT");
}

WSIAPP_END
