
# include "Core.h"
# include "XmppClientor.h"
# include "xep/XepServiceDiscovery.h"

XMPP_BEGIN

class StateDiscoItem
: public wf::Operation
{
public:
    
    virtual int run(void* param)
    {
        xep::DiscoItem const* obj = (xep::DiscoItem const*)param;
        
        for (xep::DiscoItem::items_type::const_iterator each = obj->items.begin();
             each != obj->items.end();
             ++each)
        {
            xep::DiscoInfo obj;
            obj.to = each->jid.bare();
            client->execute(obj);
        }
        return RESULT_SUC | RESULT_COMPLETE;
    }
    
    Client* client;
};

class StateDiscoInfo
: public wf::Operation
{
public:
        
    virtual int run(void* param)
    {
        xep::DiscoInfo const* obj = (xep::DiscoInfo const*)param;

        static xep::ServiceFeature items("http://jabber.org/protocol/disco#items");
        xep::DiscoInfo::features_type::const_iterator found = ::std::find(obj->features.begin(), obj->features.end(), items);
        if (found != obj->features.end())
        {
            xep::DiscoItem obj;
            client->execute(obj);
            
            // state.
            client->statemachine().look<StateDiscoItem>(obj.idr)->client = client;
        }
        
        return RESULT_SUC | RESULT_COMPLETE;
    }
    
    Client* client;
};

NNTDECL_PRIVATE_BEGIN_CXX(Clientor)

void init()
{
    PASS;
}

void dealloc()
{
    PASS;
}

void act_connected(eventobj_t&)
{
    xep::DiscoInfo obj;
    d_owner->client().execute(obj);
    
    d_owner->client().statemachine().look<StateDiscoInfo>(obj.idr)->client = &d_owner->client();
}

void act_discoinfo(eventobj_t& evt)
{    
    xep::DiscoInfo const* obj = evt;
    d_owner->client().statemachine().process(wf::State(obj->idr), (void*)obj);
}

void act_discoitems(eventobj_t& evt)
{
    xep::DiscoItem const* obj = evt;
    d_owner->client().statemachine().process(wf::State(obj->idr), (void*)obj);
}

NNTDECL_PRIVATE_END_CXX

Clientor::Clientor()
: _client(NULL)
{
    NNTDECL_PRIVATE_CONSTRUCT(Clientor);
}

Clientor::Clientor(Client& cli)
{
    NNTDECL_PRIVATE_DESTROY();
    
    set(cli);
}

Clientor::~Clientor()
{
    
}

void Clientor::set(Client& cli)
{
    if (_client)
    {
        _client->disconnect(this);
        _client->disconnect(d_ptr);
    }
    
    // set.
    _client = &cli;
    
    // connect.
    _client->connect(kSignalConnected, _action(private_type::act_connected), d_ptr);
    _client->connect(kSignalDiscoInfo, _action(private_type::act_discoinfo), d_ptr);
    _client->connect(kSignalDiscoItems, _action(private_type::act_discoitems), d_ptr);
}

Client const* Clientor::operator -> () const
{
    return _client;
}

Client* Clientor::operator -> ()
{
    return _client;
}

Clientor::operator Client  const& () const
{
    return *_client;
}

Clientor::operator Client& ()
{
    return *_client;
}

Client const& Clientor::client() const
{
    return *_client;
}

Client& Clientor::client()
{
    return *_client;
}

XMPP_END
