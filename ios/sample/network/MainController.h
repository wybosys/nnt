
# ifndef __MAIN_CTLR_1BB75DFA9E5549C4A28B181C689CAB3B_H_INCLUDED
# define __MAIN_CTLR_1BB75DFA9E5549C4A28B181C689CAB3B_H_INCLUDED

# include "SocketClient.h"

NNTAPP_BEGIN

using namespace ::wsi;

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
    ui::TextField txt_addr;
    ui::TextView txt_input;
    ui::TextView txt_output;
    ui::BevelButton btn_sync, btn_async, btn_connect;
};

class MainController
: public ui::Controller<MainController, MainView>
{
public:
    
    MainController();
    ~MainController();
    
    void view_loaded();
    
protected:
    
    void act_connect();
    void act_sync();
    void act_async();
    void act_bytes(cxx::eventobj_t&);
    
    cross::SocketClient _sync;
    cross::SocketClientAsync _async;
    
};

NNTAPP_END

# endif