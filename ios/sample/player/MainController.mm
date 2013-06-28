
# include "Foundation+NNT.h"
# include "MainController.h"
# include "JuiceCocoa++.hpp"

NNTAPP_BEGIN

WaveView::WaveView()
{

}

void WaveView::layout_subviews()
{
    
}

void WaveView::draw(CGContextRef, CGRect const& rc)
{
    juice::cocoa::Graphics gra = juice::cocoa::Graphics::Current(rc);
    
    core::vector<real> tmps = vals;
    vals.clear();
    
    // draw.
    
}

void WaveView::add(real v)
{
    vals.push_back(v);
    if (vals.size() > 60)
        redraw();
}

MainView::MainView()
{
    set_background(cg::Gradient(cg::Color::Black(), cg::Color::White(), 0, 1, M_PI_4));
                   
    add_sub(wave);
    add_sub(ctl_progress);
    add_sub(btn_play);
    add_sub(btn_stop);
    
    btn_play.set_text(@"PLAY");
    btn_stop.set_text(@"STOP");
    
    _tmr_bkg.set(ns::TimeInterval::Second(1));
    _tmr_bkg.connect(::kSignalTimerFired, _action(_class::cb_bkg), this);
}

void MainView::layout_subviews()
{
    layout::vbox lyt_main(bounds(), 5);
    layout::linear lnr_main(lyt_main);
    lnr_main << (flex)1 << (pixel)10 << (pixel)100;
    wave.set_frame(lyt_main << lnr_main);
    ctl_progress.set_frame(lyt_main << lnr_main);
    layout::hbox lyt_ctl(lyt_main << lnr_main);
    layout::linear lnr_ctl(lyt_ctl);
    lnr_ctl << (flex)1 << (flex)1;
    btn_play.set_frame(lyt_ctl << lnr_ctl);
    btn_stop.set_frame(lyt_ctl << lnr_ctl);
}

void MainView::cb_bkg()
{
    static real r = M_PI_4;
    r += M_PI_360;
    set_background(cg::Gradient(cg::Color::Black(), cg::Color::White(), 0, 1, r));
}

MainController::MainController()
{
    _fd.open(core::type_cast<core::string>(ns::URL::Bundle(@"nessun dorma.mp3").std()), mask_t().on<Io::read>());
}

MainController::~MainController()
{
    _fd.close();
}

void MainController::view_loaded()
{
    view().btn_play.connect(kSignalButtonClicked, _action(_class::act_play), this).oneshot();
    view().btn_stop.connect(kSignalButtonClicked, _action(_class::act_stop), this);
    
    _tmr_play.set(ns::TimeInterval::Second(1 / 60), true, false);
    _tmr_play.connect(::kSignalTimerFired, _action(_class::cb_progress), this);
}

void MainController::cb_progress()
{
    view().ctl_progress.set_max(_player.length());
    view().ctl_progress.set_value(_player.position());
    //view().wave.add(_player.gain());
}

void MainController::act_play()
{
    view().btn_play.connect(kSignalButtonClicked, _action(_class::act_pause), this).oneshot();
    view().btn_play.set_text(@"PAUSE");
    
    _tmr_play.start();
    _player.play(_fd, AUDIO_FORMAT_MP3);
}

void MainController::act_pause()
{
    view().btn_play.connect(kSignalButtonClicked, _action(_class::act_resume), this).oneshot();
    view().btn_play.set_text(@"RESUME");
    
    _tmr_play.stop();
    _player.pause();
}

void MainController::act_stop()
{
    view().btn_play.disconnect_signal(kSignalButtonClicked);
    view().btn_play.set_text(@"PLAY");
    view().btn_play.connect(kSignalButtonClicked, _action(_class::act_play), this).oneshot();
    
    _player.stop();
}

void MainController::act_resume()
{
    view().btn_play.connect(kSignalButtonClicked, _action(_class::act_pause), this).oneshot();
    view().btn_play.set_text(@"PAUSE");
    
    _tmr_play.start();
    _player.resume();
}

NNTAPP_END
