
# include <nnt/Foundation+NNT.h>
# include "MainController.h"

# include "ContactsCenter.h"
# include "ImplClient.h"

# include <nnt/Cross/xmpp/core/XmppFailure.h>
# include <nnt/Cross/xmpp/core/XmppClose.h>
# include <nnt/Cross/xmpp/im/XimPresence.h>
# include <nnt/Cross/xmpp/im/XimMessage.h>
# include <nnt/Cross/xmpp/im/XimRoster.h>
# include <nnt/Cross/xmpp/im/XimShow.h>
# include <nnt/Cross/xmpp/xep/XepVCard.h>
# include <nnt/Cross/xmpp/xep/XepAvatar.h>

NNTAPP_BEGIN

xmpp::im::User const* __gs_user = NULL;
xmpp::IMClient* __gs_client = NULL;

MainView::MainView()
{

}

void MainView::layout_subviews()
{

}

NNTDECL_PRIVATE_BEGIN_CXX(MainController)

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
    _client.setting.user = "fcy";
    _client.setting.passwd = "5811627";
    
    _client.setting.address = core::NetAddress("192.168.176.192:5222");
    _client.setting.mechanism = xmpp::cor::MECHANISM_PLAIN;
    _client.start();
    
    _client.connect(xmpp::kSignalConnected, _cxxaction(_class::act_connected), this);
    _client.connect(xmpp::kSignalDisconnected, _cxxaction(_class::act_disconnected), this);
    _client.connect(xmpp::kSignalFailure, _cxxaction(_class::act_failure), this);
    _client.connect(xmpp::kSignalRosterComplete, _cxxaction(_class::mdl_roaster_loaded), this);
    _client.connect(xmpp::kSignalNewMessage, _cxxaction(_class::mdl_message_new), this);
    _client.connect(xmpp::kSignalShowChanged, _cxxaction(_class::mdl_show_changed), this);
    _client.connect(xmpp::kSignalGotVCard, _cxxaction(_class::mdl_got_vcard), this);

}

void MainController::act_connected(eventobj_t&)
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

void MainController::act_disconnected(eventobj_t&)
{
    trace_msg("LOST CONNECTED.");
}

void MainController::act_failure(cxx::eventobj_t &evt)
{
    xmpp::cor::Failure const* obj = (xmpp::cor::Failure const*)evt.data;
    switch (obj->err)
    {
        case xmpp::cor::ERR_UNKNOWN | xmpp::cor::ERR_NOT_AUTHORIZED:
        {
            trace_msg("failed to authorize.");
        } break;
    }
}

void MainController::mdl_roaster_loaded(cxx::eventobj_t &evt)
{

}

void MainController::mdl_message_new(cxx::eventobj_t &evt)
{    
    xmpp::im::Message const* msg = evt;
    trace_msg(msg->from.username + ": " + msg->content);
}

void MainController::mdl_show_changed(cxx::eventobj_t &evt)
{

}

void MainController::mdl_got_vcard(cxx::eventobj_t &evt)
{    
    xmpp::xep::VCard* obj = evt;
    core::string str = obj->vcard->name.name + "\n" + obj->vcard->name.title + "\n" + obj->vcard->orangizations.front().unit + "\n" + obj->vcard->mobiles.front().number;
    trace_msg(str);
}

NNTAPP_END
