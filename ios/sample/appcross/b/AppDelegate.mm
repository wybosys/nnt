
# include "WSIFoundation.h"
# include "AppDelegate.h"

WSIAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::Blue());
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

void act_openurl(WSIEventObj*)
{
    core::Msgbox::info(@"OPEN B WITH URL");
}

void App::load()
{
    connect(kSignalAppOpenUrl, act_openurl);

    set_root(ctlr);
}

WSIAPP_END
