
# include "Core.h"
# include "XmppBind.h"
# include "../core/XmppIQ.h"
# include "../XmppClient.h"

XMPPCORE_BEGIN

Bind::Bind()
: idr(0)
{
    
}

bool Bind::couldload(xmlnode_t const* node)
{
    if (node->name == "bind" &&
        node->ns == "urn:ietf:params:xml:ns:xmpp-bind")
    {
        return true;
    }
    return false;
}

bool Bind::load(xmlnode_t const* node)
{
    if (xmlnode_t const* find = node->node("jid"))
    {
        jid.set(find->value);
    }
    
    return true;
}

void Bind::process(Client& cli)
{
    if (cli.jid.empty())
    {
        cli.jid = jid;
        if (cli.idr != cli.jid.resource)
            cli.jid.resource = cli.idr;
    }
    
    cli.emit(kSignalBind);
}

void Bind::update(Client const& cli)
{
    if (cli.idr.empty() == false)
        jid.resource = cli.idr;
}

bool Bind::save(core::data &da) const
{
    cor::IQ iq;
    iq.idr = "bind_" + core::tostr(idr);
    iq.type = cor::IQ_SET;
    
    xmlnode_t* node = NULL;
    xmlnode_t* tmp = NULL;
    
    node = iq.root.add_node("bind");
    node->ns = "urn:ietf:params:xml:ns:xmpp-bind";
    
    if (jid.resource.empty() == false)
    {
        tmp = node->add_node("resource");
        tmp->value = jid.resource;
    }
    
    return iq.save(da);
}

XMPPCORE_END