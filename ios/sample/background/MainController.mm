
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_aud.set_text(@"PLAY AUDIO");
    
    add_sub(btn_aud);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1;
    btn_aud.set_frame(lyt << lnr);
}

MainController::MainController()
{
    aud.connect(kSignalPlayCompleted, _action(_class::act_audio_end), this);
}

void MainController::view_loaded()
{
    view().btn_aud.connect(kSignalButtonClicked, _action(_class::act_audio), this);
}

void MainController::act_audio()
{
    ns::URL file = ns::URL::Bundle(@"music.mp3");
    aud.set_target(file);
    aud.set_loop(5);
    aud.set_background();
    aud.play();
}

void MainController::act_audio_end()
{
    trace_msg(@"Completed play audio.");
}

NNTAPP_END
