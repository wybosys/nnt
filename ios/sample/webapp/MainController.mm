
# include "Foundation+NNT.h"
# include "MainController.h"
# include "HttpServer.h"
# include "HttpParser.h"

NNTAPP_BEGIN

MainView::MainView()
{
    add_sub(url);
    add_sub(progress);
    add_sub(web);
    
    progress.set_progress(ui::Color::Red());
    
    web.view().connect(kSignalProgressAdded, _action(_class::act_web_begin), this);
    web.view().connect(kSignalProgressStep, _action(_class::act_web_step), this);
    
    url.set_background(ui::Color::White());
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (pixel)30 << (pixel)10 << (flex)1;
    
    url.set_frame(lyt << lnr);
    progress.set_frame(lyt << lnr);
    web.view().set_frame(lyt << lnr);
}

void MainView::act_web_begin()
{
    progress.set_max(web.view().resource_count());
}

void MainView::act_web_step()
{
    progress.set_value(web.view().resource_completed());
}

NNTDECL_PRIVATE_BEGIN_CXX(MainController)

void init()
{
    web.config.addr = "localhost:18888";
    web.connect(cross::kSignalNewConnection, _cxxaction(_class::act_web), this);
    web.start();
}

void dealloc()
{
    
}

void act_web(cxx::eventobj_t& evt)
{
    parser::Http11Response resp;
    resp.data.append("In-App Web Server");
    cross::HttpConnection& cnt = evt;
    cnt.write(resp.full());
}

cross::HttpServer web;

NNTDECL_PRIVATE_END_CXX

MainController::MainController()
{
    NNTDECL_PRIVATE_CONSTRUCT(MainController);
    
    url = @"http://localhost:18888";
    //url = @"http://www.163.com";
}

MainController::~MainController()
{
    NNTDECL_PRIVATE_DESTROY();
}

void MainController::view_loaded()
{
    view().url.set_text(url);
    view().url.connect(kSignalValueChanged, _action(_class::act_goto), this);
    view().web.view().load(ns::URLRequest(url));
}

void MainController::act_goto(EventObj& evt)
{
    ns::String str = evt.result();
    view().web.view().load(ns::URLRequest(ns::HttpUrlReform(str)));
}

NNTAPP_END
