
# ifndef __MAIN_CTLR_1B2928C6300A4AE6915A4E3E46FCAC7E_H_INCLUDED
# define __MAIN_CTLR_1B2928C6300A4AE6915A4E3E46FCAC7E_H_INCLUDED

# include <wsi/Cross/xmpp/XmppIMClient.h>

WSIAPP_BEGIN

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
};

WSIDECL_PRIVATE_HEADER_CXX(MainController);

class MainController
: public ui::Controller<MainController, MainView>
{
    WSIDECL_PRIVATE_CXX(MainController);
    
public:
    
    MainController();
    ~MainController();
    
    void view_loaded();
    
protected:
    
    void act_connected();
    void act_disconnected();
    void act_failure(cxx::eventobj_t&);
    
protected:
    
    void mdl_roaster_loaded(cxx::eventobj_t&);
    void mdl_message_new(cxx::eventobj_t&);
    void mdl_show_changed(cxx::eventobj_t&);
    void mdl_got_vcard(cxx::eventobj_t&);
    
protected:
    
    xmpp::IMClient _client;
    
};

WSIAPP_END

# endif