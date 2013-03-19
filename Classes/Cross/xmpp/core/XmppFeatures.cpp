
# include "Core.h"
# include "XmppFeatures.h"
# include "../XmppClient.h"

# include "XmppSasl.h"
# include "XmppCompression.h"
# include "XmppAuth.h"
# include "XmppBind.h"
# include "XmppSession.h"
# include "XmppStream.h"

XMPPCORE_BEGIN

wf::State kStateAuth = wf::State("::wsi::xmpp::auth");

Features::Features()
: _sasl(NULL)
, _compression(NULL)
, _bind(NULL)
, _session(NULL)
{
    PASS;
}

Features::~Features()
{
    zero_drop(_sasl);
    zero_drop(_compression);
    zero_drop(_bind);
    zero_drop(_session);
}

bool Features::couldload(xmlnode_t const* node)
{
	if (node->name == "features")
		return true;        
	return false;
}

bool Features::load(xmlnode_t const* node)
{
    // load mechanisms.
    if (xmlnode_t const* mechs = node->node("mechanisms"))
    {
        if (Sasl::couldload(mechs))
        {
            _sasl = new Sasl;
            if (!_sasl->load(mechs))
                zero_drop(_sasl);
        }
    }        
    
    // load compress.
    if (xmlnode_t const* comp = node->node("compression"))
    {
        if (Compression::couldload(comp))
        {
            _compression = new Compression;
            if (!_compression->load(comp))
                zero_drop(_compression);
        }
    }
    
    // load bind.
    if (xmlnode_t const* bind = node->node("bind"))
    {
        if (Bind::couldload(bind))
        {
            _bind = new Bind;
            if (!_bind->load(bind))
                zero_drop(_bind);
        }
    }
    
    // load session.
    if (xmlnode_t const* sess = node->node("session"))
    {
        if (Session::couldload(sess))
        {
            _session = new Session;
            if (!_session->load(sess))
                zero_drop(_session);
        }
    }
        
    return true;
}

class SaslOperation
: public wf::Operation
{
public:
    
    SaslOperation(Client& _cli)
    : cli(_cli)
    {
        PASS;
    }
    
    virtual int run(void*)
    {
        Stream stm;
        stm.to = cli.setting.address.address;
        cli.execute(stm);
        
        return RESULT_SUC | RESULT_COMPLETE;
    }
    
    Client& cli;
};

void Features::process(Client& cli)
{
    if (_sasl)
        _sasl->process(cli);
    
    if (_compression)
        _compression->process(cli);
    
    if (_sasl)
    {
        // set state.
        SaslOperation* ope = new SaslOperation(cli);
        cli.statemachine().look(kStateAuth, ope);
        safe_drop(ope);
        
        // start select auth mech.
        Auth auth;
        auth.user = cli.setting.user;
        auth.passwd = cli.setting.passwd;
        auth.address = cli.setting.address.address;
        auth.mechanism = cli.setting.mechanism;        
        cli.execute(auth);
    }
    
    if (_bind)
    {
        _bind->idr = cli.counter_bind();
        cli.execute(*_bind);
    }
    
    if (_session)
    {
        _session->idr = cli.counter_session();
        cli.execute(*_session);
    }
}

XMPPCORE_END
