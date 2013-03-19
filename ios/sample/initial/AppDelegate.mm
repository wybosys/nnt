
# include "Foundation+NNT.h"
# include "AppDelegate.h"
# include "UIInitialView.h"
# include "UIActivityIndicatorBar.h"
# include "UIActivityIndicatorWave.h"

NNTAPP_BEGIN

class Initial
: public ui::InitialView
{
public:
    
    Initial()
    {
        add_sub(lbl);
        add_sub(bar);
        add_sub(wave);
        
        lbl.set_fontcolor(ui::Color::White());
        lbl.set_background(ui::Color::Black());
        lbl.set_alignment(UITextAlignmentCenter);
        lbl.set_text(@"PLEASE WAIT FOR 10 SECOND.");
    }
    
    ~Initial()
    {
        trace_msg(@"initial destroy.");
    }
    
    void layout_subviews()
    {
        CGRectLayoutVBox vlyt(bounds(), 5);
        CGRectLayoutLinear vlnr(vlyt);
        vlnr << (flex)2 << (pixel)30 << (pixel)20 << (pixel)20 << (flex)1;
        vlyt << vlnr;
        
        lbl.set_frame(vlyt << vlnr);
        bar.set_frame(vlyt << vlnr);
        wave.set_frame(vlyt << vlnr);
    }
    
    void work()
    {
        bar.start();
        wave.start();
        perform(_perform_action(Initial::time), 2);
    }
    
    void time()
    {
        hide();
    }
    
    ui::Label lbl;
    ui::activity::Bar bar;
    ui::activity::Wave wave;
    
};

void App::load()
{
    set_initial(ui::Instance<Initial>::instance()());
    set_root(ctlr);
}

NNTAPP_END
