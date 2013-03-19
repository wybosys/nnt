
# import "Foundation+NNT.h"
# import "MainController.h"
# import "SocketClient.h"

NNTAPP_BEGIN

MainView::MainView()
{
    set_background(ui::Color::White());
    
    btn_sync.set_text(@"SYNC");
    btn_async.set_text(@"ASYNC");
    btn_connect.set_text(@"CONNECT");
    
    txt_addr.set_text(@"192.168.170.58:5222");
    txt_input.set_background(ui::Color::Gray());
    txt_output.set_background(ui::Color::Orange());
    
    txt_input.set_text(@"<?xml version='1.0'?><stream:stream to='baison.com' xmlns='jabber:client' xmlns:stream='http://etherx.jabber.org/streams' version='1.0'>");
    
    add_sub(txt_addr);
    add_sub(txt_input);
    add_sub(txt_output);
    add_sub(btn_sync);
    add_sub(btn_async);
    add_sub(btn_connect);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt_main(bounds());
    CGRectLayoutLinear lnr_main(lyt_main);
    lnr_main << (pixel)30 << (pixel)30 << (flex)1 << (flex)1;
    
    {
        CGRectLayoutHBox lyt(lyt_main << lnr_main);
        CGRectLayoutLinear lnr(lyt);
        lnr << (flex)1 << (pixel)100;
        
        txt_addr.set_frame(lyt << lnr);
        btn_connect.set_frame(lyt << lnr);
    }
    
    {
        CGRectLayoutHBox lyt(lyt_main << lnr_main);
        CGRectLayoutLinear lnr(lyt);
        lnr << (flex)1 << (flex)1;
        
        btn_sync.set_frame(lyt << lnr);
        btn_async.set_frame(lyt << lnr);
    }
    
    txt_input.set_frame(lyt_main << lnr_main);
    txt_output.set_frame(lyt_main << lnr_main);
}

MainController::MainController()
{
    
}

MainController::~MainController()
{
    
}

void MainController::view_loaded()
{
    view().btn_connect.connect(kSignalButtonClicked, _action(MainController::act_connect), this);
    view().btn_sync.connect(kSignalButtonClicked, _action(MainController::act_sync), this);
    view().btn_async.connect(kSignalButtonClicked, _action(MainController::act_async), this);    
}

void MainController::act_connect()
{
    _sync.close();
    _async.close();
        
    _sync.connect_to(cross::NetAddress(core::type_cast<core::string>(view().txt_addr.text())));
    _async.connect_to(cross::NetAddress(core::type_cast<core::string>(view().txt_addr.text())));
    
    _async.stream().connect(::wsi::kSignalBytesAvailable, _cxxaction(MainController::act_bytes), this);
}

void MainController::act_sync()
{
    core::data da = core::type_cast<core::data>(view().txt_input.text());
    _sync.stream().write(da);
}

void MainController::act_async()
{
    core::data da = core::type_cast<core::data>(view().txt_input.text());
    _async.stream().write(da);
}

void MainController::act_bytes(cxx::eventobj_t& evt)
{
    cross::SocketStream* stm = (cross::SocketStream*)evt.data;
    core::data da(1024);
    stm->read(da, core::Timeout::Default());
    
    WSI_MAINTHREAD_BEGIN
    view().txt_output.set_text(core::type_cast<ns::String>(da));
    WSI_MAINTHREAD_END
}

NNTAPP_END