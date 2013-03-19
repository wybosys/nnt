
# ifndef __MAIN_CTLR_1400F91542FC4B439E99C83ADB62FEA9_H_INCLUDED
# define __MAIN_CTLR_1400F91542FC4B439E99C83ADB62FEA9_H_INCLUDED

# include "XmppIMClient.h"

WSIAPP_BEGIN

using namespace ::wsi;

class ContactsTree
: public ui::TableTreeController
{
public:
    
    ::wsi::Object* makecell(IndexPath const&) const;
    ::wsi::Object* makegroupcell(IndexPath const&) const;
    
};

class ContactCell
: public ui::TableCell<ContactCell>
{
    typedef ui::TableCell<ContactCell> super;
    
public:
    
    ContactCell();
    
    void layout_subviews();
    void update();
    void selected();
    
};

class ContactGroup
: public ui::TableGroupCell<ContactCell, ContactsTree>
{
    typedef ui::TableGroupCell<ContactCell, ContactsTree> super;
    
public:
    
    ContactGroup();
    
    void layout_subviews();
    void update();
    
};

class MainView
: public ui::View<MainView>
{
public:
    
    MainView();
    
    void layout_subviews();
    
    ui::TextField input;
    ui::BevelButton send;
    ContactsTree tree;
    ui::BevelButton logout;
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
    void act_send();
    void act_logout();
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