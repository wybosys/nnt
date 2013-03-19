
# include "Core.h"
# include "XmppClient.h"
# include "../SocketClient.h"
# include "XmppResponseFactory.h"
# include "core/XmppStream.h"

XMPP_BEGIN

NNTDECL_PRIVATE_BEGIN_CXX(Client)

void init()
{
    responsor.set_client(*d_owner);

    cnt_challenge = cnt_session = cnt_bind = cnt_any = 0;
    binded = sessioned = false;

    // socket.
    connector.connect(kSignalSuccess, _cxxaction(_class::act_connected), this);
    connector.connect(kSignalFailed, _cxxaction(_class::act_failed), this);
}

void dealloc()
{
    PASS;
}

void reset()
{
    binded = sessioned = false;
    machine.clear();
    d_owner->jid.clear();
    d_owner->server.clear();
    d_owner->idr.clear();
    
    // break old signals.
    d_owner->disconnect(kSignalBind, this);
    d_owner->disconnect(kSignalSession, this);
}

void act_connected(eventobj_t&)
{
    trace_msg("xmpp connected.");
    
    // bind client.
    d_owner->connect(kSignalBind, _cxxaction(_class::act_binded), this);
    d_owner->connect(kSignalSession, _cxxaction(_class::act_sessioned), this);
    
    // bind signal.
    connector.stream().connect(kSignalBytesAvailable, _cxxaction(private_type::act_bytes), this)->in_background();
    connector.stream().connect(kSignalClosed, _cxxaction(private_type::act_close), this);
    
    // set initial stream entry.
    cor::Stream stream;
    stream.from = d_owner->setting.user + "@" + d_owner->setting.address.address;
    stream.to = d_owner->setting.address.address;
    d_owner->execute(stream);
}

void act_failed(eventobj_t&)
{
    trace_msg("failed to connect to xmpp server.");
	d_owner->emit(kSignalFailure);
}

void act_bytes(cxx::eventobj_t& evt)
{
    // read data.
    cross::SocketStream* stm = (cross::SocketStream*)evt.data;
    ::nnt::core::data da(d_owner->setting.framelen);
    ::nnt::core::Timeout tm = ::nnt::core::Timeout::Milliseconds(d_owner->setting.timeout);
    
    // parse data.
    if (stm->read_all(da, tm))
    {
# ifdef NNT_DEBUG
        trace_msg("XMPP will process: " + core::type_cast<core::string>(da));
# endif

        // from factory.
        responsor.process(da);
    }
    else
    {
        stm->close();
    }
}

void act_close(cxx::eventobj_t&)
{
    reset();
    
    d_owner->emit(kSignalDisconnected);
}

void act_binded(eventobj_t&)
{
    binded = true;
    if (sessioned)
        d_owner->emit(kSignalConnected);
}

void act_sessioned(eventobj_t&)
{
    sessioned = true;
    if (binded)
        d_owner->emit(kSignalConnected);
}

cross::SocketClientAsync connector;
ResponseFactory responsor;

// counter.
ulong cnt_challenge;
ulong cnt_session;
ulong cnt_bind;
ulong cnt_any;

// tag.
bool binded, sessioned;

//! state machine.
wf::Machine machine;

NNTDECL_PRIVATE_END_CXX

ClientSetting::ClientSetting()
: 
framelen(1024),
timeout(100),
mechanism(cor::MECHANISM_UNKNOWN)
{
    version = "1.0.0.0";
    name = "::nnt::cross::xmpp";
}

Client::Client()
{
    NNTDECL_PRIVATE_CONSTRUCT(Client);
}

Client::~Client()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNTDECL_SIGNALS_BEGIN(Client, super)
NNT_SIGNAL(kSignalConnected)
NNT_SIGNAL(kSignalDisconnected)
NNT_SIGNAL(kSignalFailure)
NNT_SIGNAL(kSignalBind)
NNT_SIGNAL(kSignalSession)
NNT_SIGNAL(kSignalDiscoInfo)
NNT_SIGNAL(kSignalDiscoItems)
NNTDECL_SIGNALS_END

void Client::start()
{
    d_ptr->connector.close();
    d_ptr->connector.connect_to(setting.address);
}

bool Client::execute(xmpp::Object const& obj) const
{
    ::nnt::core::data da;
    
    // save to data.
    if (false == obj.save(da))
        return false;
    
    // send to server.
    if (false == d_ptr->connector.stream().write(da))
        return false;
        
    return true;
}

ulong Client::counter_challenge() const
{
    return ++d_ptr->cnt_challenge;
}

ulong Client::counter_session() const
{
    return ++d_ptr->cnt_session;
}

ulong Client::counter_bind() const
{
    return ++d_ptr->cnt_bind;
}

ulong Client::counter_any() const
{
    return ++d_ptr->cnt_any;
}

ResponseFactory* Client::_response_factory()
{
    return &d_ptr->responsor;
}

wf::Machine& Client::statemachine()
{
    return d_ptr->machine;
}

XMPP_END
