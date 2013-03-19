
# include "WSIFoundation.h"
# include "MainController.h"
# include "ColorPalette.h"

WSIAPP_BEGIN

MainView::MainView()
{
    add_sub(tag);
    
    set_background(ui::Color::White());
}

void MainView::layout_subviews()
{
    tag.view().set_frame(bounds());
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    core::ColorWheel cw;
    
    // load data.
    for (uint i = 0; i < 100; ++i)
    {
        ui::Label* lbl = ui::Label::New();
        lbl->set_fontcolor(ui::Color::RGB(cw.next()));
        lbl->set_size(cg::Size(100, 50));
        lbl->set_text(@"TAG" + ns::String(i));
        view().tag.add(lbl);
        lbl->Release();
    }
    
    view().tag.reload();
    view().tag.connect(kSignalContentClicked, _action(_class::act_click), this);
    view().tag.view().connect(kSignalTouchesBegin, _action(_class::act_touchin), this);
    view().tag.view().connect(kSignalTouchesEnd, _action(_class::act_touchout), this);
    
    play = true;
    act_play();
}

void MainController::act_click(EventObj &evt)
{
    ui::Label* lbl = (ui::Label*)evt.result();
    core::Confirm::info(lbl->text());
}

void MainController::act_play()
{
    if (play == false)
        return;
    
    view().tag.view().set_offset(view().tag.view().offset_a() + M_2PI_360, view().tag.view().offset_b());
    view().tag.view().relayout();
    
    perform(_perform_action(_class::act_play), .01);
}

void MainController::act_touchin()
{
    play = false;
}

void MainController::act_touchout()
{
    play = true;
    act_play();
}

WSIAPP_END
