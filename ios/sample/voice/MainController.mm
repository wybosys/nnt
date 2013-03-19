
# include "Foundation+NNT.h"
# include "MainController.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_recg.set_text(@"START VOICE RECOGNIZE");
    btn_speak.set_text(@"SPEAK SENTENCE");
    
    add_sub(btn_recg);
    add_sub(btn_speak);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    btn_recg.set_frame(lyt << lnr);
    btn_speak.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn_recg.connect(kSignalButtonClicked, _action(_class::act_recg), this);
    view().btn_speak.connect(kSignalButtonClicked, _action(_class::act_speak), this);
}

void MainController::act_recg()
{
    iflytek::VoiceRecognizer regr;
    regr.connect(kSignalVoiceRecognizeSuccess, _action(_class::act_recg_result), this);
    regr.execute();
}

void MainController::act_recg_result(EventObj& evt)
{
    core::Msgbox::info(evt.result());
}

void MainController::act_speak()
{
    _sph.set_text(@"一二三");
    _sph.connect(kSignalSpeechCompletion, _action(_class::act_speak_next), this).oneshot();
    _sph.speak();
}

void MainController::act_speak_next()
{
    _sph.set_text(@"四五六");
    _sph.speak();
}

NNTAPP_END
