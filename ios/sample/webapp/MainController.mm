
# include "Foundation+NNT.h"
# include "MainController.h"
# include "HttpServer.h"
# include "HttpParser.h"

NNTAPP_BEGIN

MainView::MainView()
{
    add_sub(web);
}

void MainView::layout_subviews()
{
    web.view().set_frame(bounds());
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
}

MainController::~MainController()
{
    NNTDECL_PRIVATE_DESTROY();
}

void MainController::view_loaded()
{
    view().web.view().load(ns::URLRequest(@"http://localhost:18888"));
}

NNTAPP_END
