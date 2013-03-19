
# include "Core.h"
# include "XmppResponse.h"

XMPPCORE_BEGIN

Response::Response()
{
    PASS;
}

bool Response::save(core::data & da) const
{
    xmlnode_t node("response", super::str);
    node.ns = "urn:ietf:params:xml:ns:xmpp-sasl";    
    return node.save(da);
}

bool Response::couldload(xmlnode_t const*)
{
    return false;
}

XMPPCORE_END