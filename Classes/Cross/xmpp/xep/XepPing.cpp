
# include "Core.h"
# include "XepPing.h"

XMPPXEP_BEGIN

Ping::Ping()
{
    type = cor::IQ_GET;
}

bool Ping::couldload(const xmlnode_t * node)
{
    return 
    node->name == "ping" &&
    node->ns == "urn:xmpp:ping";
}

bool Ping::load(const xmlnode_t * node)
{
    return true;
}

void Ping::process(Client &)
{
    PASS;
}

void Ping::update(Client const& cli)
{
    if (to.empty())
        to = cli.server;
    
    super::update(cli);
}

bool Ping::save(core::data & da) const
{
    cor::IQ iq;
    to_iq(iq);
    
    iq.root.add_node("ping")->ns = "urn:xmpp:ping";
    
    return iq.save(da);
}

XMPPXEP_END