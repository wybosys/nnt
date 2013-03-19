
# include "WSIFoundation.h"
# include "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    clip.set_readonly();
        
    add_sub(input);
    add_sub(clip);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    input.set_frame(lyt << lnr);
    clip.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    clip.connect(kSignalContentChanged, _action(_class::act_clip_changed), this);
}

void MainController::act_clip_changed()
{
    if (clip.is_string())
    {
        view().clip.set_text(clip);
    }
}

WSIAPP_END
