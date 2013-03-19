
# include "Core.h"
# include "XmppSession.h"
# include "../core/XmppIQ.h"
# include "../XmppClient.h"

XMPPCORE_BEGIN

Session::Session()
: idr(0)
{
    
}

bool Session::couldload(xmlnode_t const* node)
{
    if (node->name == "session" &&
        node->ns == "urn:ietf:params:xml:ns:xmpp-session")
    {
        return true;
    }
    return false;
}

bool Session::load(xmlnode_t const* node)
{
    return true;
}

void Session::process(Client& cli)
{
    cli.emit(kSignalSession);
}

bool Session::save(core::data &da) const
{
    cor::IQ iq;
    iq.idr = "sess_" + core::tostr(idr);
    iq.type = cor::IQ_SET;
    
    xmlnode_t* node = new xmlnode_t("session");
    node->ns = "urn:ietf:params:xml:ns:xmpp-session";
    iq.root.add(node);
    node->drop();
    
    return iq.save(da);
}

XMPPCORE_END