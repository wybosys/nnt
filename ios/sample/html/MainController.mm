
# import "WSIFoundation.h"
# import "MainController.h"

WSIAPP_BEGIN

MainView::MainView()
{
    add_sub(web);
}

void MainView::layout_subviews()
{
    web.view().set_frame(bounds());
}

MainController::MainController()
{

}

void MainController::view_loaded()
{
    view().web.web().view().connect(kSignalWebAction, _action(_class::act_webaction), this);
    view().web.web().view().enable_callback();
    view().web.web().view().load(ns::URL::Bundle(@"index.html"), ns::URL::Bundle(@""));
}

void MainController::act_webaction(EventObj& evt)
{
    ns::String act = evt.result();
    if (act == @"BAIDU")
        view().web.web().view().load(ns::URLRequest(@"http://www.baidu.com"));
    else if (act == @"MSG")
        core::Msgbox::info(@"INFO");
}

WSIAPP_END