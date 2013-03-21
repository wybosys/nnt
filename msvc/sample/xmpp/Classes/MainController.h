
# ifndef __MAIN_CTLR_1B2928C6300A4AE6915A4E3E46FCAC7E_H_INCLUDED
# define __MAIN_CTLR_1B2928C6300A4AE6915A4E3E46FCAC7E_H_INCLUDED

# include <nnt/Cross/xmpp/XmppIMClient.h>

NNTAPP_BEGIN

class MainView
	: public ui::uc::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
};

NNTDECL_PRIVATE_HEAD_CXX(MainController);

class MainController
	: public ui::uc::Controller<MainController, MainView>
{
    NNTDECL_PRIVATE_CXX(MainController);
    
public:
    
    MainController();
    ~MainController();
    
    void view_loaded();
    
protected:
    
    void act_connected(eventobj_t&);
    void act_disconnected(eventobj_t&);
    void act_failure(eventobj_t&);
    
protected:
    
    void mdl_roaster_loaded(cxx::eventobj_t&);
    void mdl_message_new(cxx::eventobj_t&);
    void mdl_show_changed(cxx::eventobj_t&);
    void mdl_got_vcard(cxx::eventobj_t&);
    
protected:
    
    xmpp::IMClient _client;
    
};

NNTAPP_END

# endif