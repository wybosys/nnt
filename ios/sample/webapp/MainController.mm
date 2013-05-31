
# include "Foundation+NNT.h"
# include "MainController.h"
# include "HttpServer.h"
# include "HttpParser.h"

NNTAPP_BEGIN

MainView::MainView()
{
    add_sub(url);
    add_sub(web);
    
    url.set_background(ui::Color::White());
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds());
    layout::linear lnr(lyt);
    lnr << (pixel)30 << (flex)1;
    
    url.set_frame(lyt << lnr);
    web.view().set_frame(lyt << lnr);
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
