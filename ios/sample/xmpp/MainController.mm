
# include "WSIFoundation.h"
# include "MainController.h"
# include "ContactsCenter.h"
# include "ImplClient.h"

# include "XmppFailure.h"
# include "XmppClose.h"
# include "XimPresence.h"
# include "XimMessage.h"
# include "XimRoster.h"
# include "XimShow.h"
# include "XepVCard.h"
# include "XepAvatar.h"

WSIAPP_BEGIN

xmpp::im::User const* __gs_user = NULL;
xmpp::IMClient* __gs_client = NULL;

ContactCell::ContactCell()
: super(UITableViewCellStyleValue1)
{

}

void ContactCell::layout_subviews()
{
    
}

void ContactCell::update()
{
    xmpp::im::User const* data = (xmpp::im::User const*)object();
    text().set_text(data->name);
}

void ContactCell::selected()
{
    // select.
    __gs_user = (xmpp::im::User const*)object();
    
    // get vcard.
    {
        xmpp::xep::VCard obj;
        obj.to = __gs_user->jid.to_address();
        __gs_client->execute(obj);
    }
}

ContactGroup::ContactGroup()
{
    set_accessory(UITableViewCellAccessoryDisclosureIndicator);
}

void ContactGroup::layout_subviews()
{
    super::layout_subviews();
}

void ContactGroup::update()
{
    super::update();
    
    core::string str = object();
    text().set_text(str);
}

::wsi::Object* ContactsTree::makecell(IndexPath const& ip) const
{
    return new ContactCell;
}

::wsi::Object* ContactsTree::makegroupcell(IndexPath const& ip) const
{
    return new ContactGroup;
}

MainView::MainView()
{
    set_background(ui::Color::White());      
    
    send.set_text(@"SEND");
    logout.set_text(@"LOGOUT");
    
    add_sub(input);
    add_sub(send);
    add_sub(tree);
    add_sub(logout);
}

void MainView::layout_subviews()
{
    CGRectLayoutVBox lyt(bounds());
    CGRectLayoutLinear lnr(lyt);
    lnr << (pixel)30 << (flex)1 << (pixel)30;
    
    {
        CGRectLayoutHBox lytinput(lyt << lnr);
        CGRectLayoutLinear lnrinput(lytinput);
        lnrinput << (flex)1 << (pixel)100;
        input.set_frame(lytinput << lnrinput);
        send.set_frame(lytinput << lnrinput);
    }
    
    tree.view().set_frame(lyt << lnr);
    
    {
        CGRectLayoutHBox lytbtm(lyt << lnr);
        CGRectLayoutLinear lnrbtm(lytbtm);
        lnrbtm << (flex)1;
        logout.set_frame(lytbtm << lnrbtm);
    }
}

WSIDECL_PRIVATE_BEGIN_CXX(MainController)

void init()
{
    clientor.set(d_owner->_client);
    __gs_client = &d_owner->_client;
}

void dealloc()
{
    PASS;
}

ContactsCenter contacts;
Client clientor;

WSIDECL_PRIVATE_END_CXX

MainController::MainController()
{
    WSIDECL_PRIVATE_CONSTRUCT(MainController);
}

MainController::~MainController()
{
    WSIDECL_PRIVATE_DESTROY();
}

void MainController::view_loaded()
{
    _client.setting.user = "fcy";
    _client.setting.passwd = "5811627";

    _client.setting.address = cross::NetAddress("192.168.176.192:5222");
    _client.setting.mechanism = xmpp::cor::MECHANISM_PLAIN;
    _client.start();
    
    _client.connect(xmpp::kSignalConnected, _cxxaction(_class::act_connected), this);
    _client.connect(xmpp::kSignalDisconnected, _cxxaction(_class::act_disconnected), this);
    _client.connect(xmpp::kSignalFailure, _cxxaction(_class::act_failure), this);
    _client.connect(xmpp::kSignalRosterComplete, _cxxaction(_class::mdl_roaster_loaded), this);
    _client.connect(xmpp::kSignalNewMessage, _cxxaction(_class::mdl_message_new), this);
    _client.connect(xmpp::kSignalShowChanged, _cxxaction(_class::mdl_show_changed), this);
    _client.connect(xmpp::kSignalGotVCard, _cxxaction(_class::mdl_got_vcard), this);
    
    view().send.connect(kSignalButtonClicked, _action(_class::act_send), this);
    view().logout.connect(kSignalButtonClicked, _action(_class::act_logout), this);
}

void MainController::act_connected()
{
    // online.
    {
        xmpp::im::Presence obj;
        _client.execute(obj);
    }
    
    // show tree.
    {
        xmpp::im::RosterQuery obj;
        _client.execute(obj);
    }
}

void MainController::act_disconnected()
{
    core::Msgbox::info(@"LOST CONNECTED.");
}

void MainController::act_send()
{
    autocollect;
    
    if (__gs_user == NULL)
    {
        core::Msgbox::info(@"please select a contact.");
        return;
    }

    if (!view().input.text().not_empty())
    {
        core::Msgbox::info(@"please input some text.");
        return;
    }
    
    xmpp::im::Message obj;
    obj.content = core::type_cast<core::string>(view().input.text());
    obj.to = __gs_user->jid;
    _client.execute(obj);
}

void MainController::act_failure(cxx::eventobj_t &evt)
{
    autocollect;
    
    xmpp::cor::Failure const* obj = (xmpp::cor::Failure const*)evt.data;
    switch (obj->err)
    {
        case xmpp::cor::ERR_UNKNOWN | xmpp::cor::ERR_NOT_AUTHORIZED:
        {
            core::Msgbox::info("failed to authorize.");
        } break;
    }
}

void make_section(ui::TableTreeSection* sec, Group const* grp)
{
    sec->header = grp->name;
    
    for (Group::contacts_type::const_iterator each = grp->contacts.begin();
         each != grp->contacts.end();
         ++each)
    {
        sec->add((*each)->data);
    }
    
    for (Group::groups_type::const_iterator each = grp->groups.begin();
         each != grp->groups.end();
         ++each)
    {
        sec->add(each->first);
        
        ui::TableTreeSection& subitem = sec->item_at(sec->count() - 1);
        make_section(&subitem, each->second);
    }
}

void MainController::mdl_roaster_loaded(cxx::eventobj_t &evt)
{
    autocollect;
    
    ContactsTree& tree = view().tree;
    d_ptr->contacts.load(*(xmpp::im::RosterQuery::contacts_type const*)evt.data);
    
    // clear.
    tree.clear();
    
    // make section.
    for (Group::groups_type::const_iterator each_grp = d_ptr->contacts.tree.groups.begin();
         each_grp != d_ptr->contacts.tree.groups.end();
         ++each_grp)
    {
        ui::TableTreeSection* sec = new ui::TableTreeSection;
        make_section(sec, each_grp->second);
        tree.add(sec);
        sec->drop();
    }

    // reload.
    tree.reload();
}

void MainController::mdl_message_new(cxx::eventobj_t &evt)
{
    autocollect;
    
    xmpp::im::Message const* msg = evt;
    core::Msgbox::info(msg->from.username + ": " + msg->content);
}

void MainController::mdl_show_changed(cxx::eventobj_t &evt)
{
    autocollect;
    
    //xmpp::im::Show* obj = evt;
}

void MainController::mdl_got_vcard(cxx::eventobj_t &evt)
{
    autocollect;
    
    xmpp::xep::VCard* obj = evt;
    core::string str = obj->vcard->name.name + "\n" + obj->vcard->name.title + "\n" + obj->vcard->orangizations.front().unit + "\n" + obj->vcard->mobiles.front().number;
    core::Msgbox::info(str);
}

void MainController::act_logout()
{
    xmpp::cor::Close obj;
    _client.execute(obj);
}

WSIAPP_END