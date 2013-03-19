
# include "WSIFoundation.h"
# include "AppDelegate.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Red());
}

void MainView::layout_subviews()
{
    
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    
}

void act_openurl(WSIEventObj* evt)
{
    ns::Dictionary da(evt.result);
    core::Msgbox::info(ns::String::Format(@"OPEN A WITH URL: %@.", da[@"url"]));
}

void App::load()
{
    connect(kSignalAppOpenUrl, act_openurl);
    
    set_root(ctlr);
}

WSIAPP_END
