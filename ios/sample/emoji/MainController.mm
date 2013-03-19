
# include "WSIFoundation.h"
# include "MainController.h"
# include "EmojiConverter.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    emoji.set_emojis(EmojiConverter::getInstance().emojis());
    add_sub(emoji);
}

void MainView::layout_subviews()
{
    wsi::CGRectLayoutVBox lyt_main(bounds());
    wsi::CGRectLayoutLinear lnr_main(lyt_main);
    
    lnr_main << (wsi::flex)1 << (wsi::pixel)100 << (wsi::flex)1;
    
    lyt_main << lnr_main;
    emoji.view().set_frame(CGRectDeflateCenter(lyt_main << lnr_main, 10, 0));
    lyt_main << lnr_main;
}

MainController::MainController()
{
}

void MainController::view_loaded()
{
    view().emoji.connect(kSignalEmojiSelected, _action(_class::act_click), this);
}

void MainController::act_click(EventObj& evt)
{
    WSIUILabel* lbl = (WSIUILabel*)evt.result();
    trace_obj(lbl.text);
}

WSIAPP_END