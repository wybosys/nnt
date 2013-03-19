
# include "Core.h"
# include "XepOfflineMessage.h"

XMPPXEP_BEGIN

OfflineMessage::OfflineMessage()
{
    
}

bool OfflineMessage::couldload(xmlnode_t const* node)
{
    return false;
}

bool OfflineMessage::load(xmlnode_t const* node)
{
    return false;
}

void OfflineMessage::process(Client& cli)
{
    
}

void OfflineMessage::update(Client const& cli)
{
    from = cli.jid;
}

bool OfflineMessage::save(core::data& da) const
{
    xmlnode_t node("presence");
    node.add_attr("from", from.full());
    node.add_node("priority", "1");
    return node.save(da);
}

XMPPXEP_END
