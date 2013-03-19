
# ifndef __XMPP_CLIENT_9EFA6AD889BF472092FCB3E0F7A63F4B_H_INCLUDED
# define __XMPP_CLIENT_9EFA6AD889BF472092FCB3E0F7A63F4B_H_INCLUDED

# include "../NetAddress.h"
# include "XmppObject.h"

# include "./core/XmppCore.h"
# include "./core/XmppJID.h"

# include "../../Workflow/StateMachine.h"

XMPP_HEADER_BEGIN

NNTCLASS(Client);

NNTDECL_PRIVATE_HEAD_CXX(Client);

class ClientSetting
{
public:
    
    ClientSetting();
    
    //! address of server.
    cross::NetAddress address;
    
    //! user for login.
    core::string user;
    
    //! passwd for login.
    core::string passwd;
    
    //! frame length.
    uint framelen;
    
    //! timeout.
    uint timeout;
    
    //! client app version.
    core::string version;
    
    //! client app name.
    core::string name;
    
    //! mechanism.
    cor::MechanismType mechanism;
    
};

class ResponseFactory;

class Client
: public cxx::Object<>
{
    NNTDECL_PRIVATE_CXX(Client);
    typedef cxx::Object<> super;
    
public:
    
    Client();
    ~Client();
    
    //! start xmpp client.
    void start();
    
    //! execute a object.
    bool execute(xmpp::Object const& obj) const;
    
    //! execute a object complete.
    template <typename objT>
    bool execute(objT& obj, typename objT::response_object_empty_type* = NULL) const;
    
    NNTDECL_SIGNALS_SLOTS;
    
    //! read counter.
    ulong counter_challenge() const;
    ulong counter_session() const;
    ulong counter_bind() const;
    ulong counter_any() const;
    
    //! state machine.
    wf::Machine& statemachine();
    
protected:
    
    //! get response.
    ResponseFactory* _response_factory();
    
public:
    
    //! setting for client.
    ClientSetting setting;
    
    //! clientid.
    core::string idr;
    
    //! server.
    core::string server;
    
    //! jid.
    cor::Jid jid;
        
};

NNT_STATIC_CONST cxx::signal_t kSignalConnected = "::wsi::xmpp::connected";
NNT_STATIC_CONST cxx::signal_t kSignalDisconnected = "::wsi::xmpp::disconnected";
NNT_STATIC_CONST cxx::signal_t kSignalFailure = "::wsi::xmpp::failure";
NNT_STATIC_CONST cxx::signal_t kSignalBind = "::wsi::xmpp::bind";
NNT_STATIC_CONST cxx::signal_t kSignalSession = "::wsi::xmpp::session";
NNT_STATIC_CONST cxx::signal_t kSignalDiscoInfo = "::wsi::xmpp::disco::info";
NNT_STATIC_CONST cxx::signal_t kSignalDiscoItems = "::wsi::xmpp::disco::items";

template <typename objT>
inline_impl bool Client::execute(objT& obj, typename objT::response_object_empty_type*) const
{
    obj.update(*this);
    bool suc = execute((xmpp::Object const&)obj);
    if (suc)
        obj.complete(*this);
    return suc;
}

XMPP_HEADER_END

# endif