
# import "WSIFoundation.h"
# import "MainController.h"
# import "WSIConfiguration.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_config.set_text(@"CONFIG");
    
    add_sub(txt_config);
    add_sub(btn_config);
    
    btn_config.connect(kSignalButtonClicked, _action(MainView::act_config), this);
    
    store::Configuration& config = store::Configuration::shared();
    ns::String str_config = config.get(@"str_config", @"");
    txt_config.set_text(str_config);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);    
    lnr << (pixel)30 << (flex)1;
    
    {
        CGRectLayoutHBox slyt(lyt << lnr);
        CGRectLayoutLinear slnr(slyt);
        slnr << (flex)1 << (pixel)100;
        
        txt_config.set_frame(slyt << slnr);
        btn_config.set_frame(slyt << slnr);
    }
}

void MainView::act_config()
{
    store::Configuration& config = store::Configuration::shared();
    config.set(@"str_config", txt_config.text());
}

void MainController::view_loaded()
{
    
}

WSIAPP_END