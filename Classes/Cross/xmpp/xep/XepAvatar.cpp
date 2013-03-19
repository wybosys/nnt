
# include "Core.h"
# include "XepAvatar.h"
# include "../core/XmppPubsub.h"

XMPPXEP_BEGIN

UserAvatar::UserAvatar()
{
    type = cor::IQ_GET;
}

bool UserAvatar::couldload(xmlnode_t const*)
{
    return false;
}

bool UserAvatar::load(xmlnode_t const*)
{
    return false;
}

void UserAvatar::process(Client&)
{
    
}

bool UserAvatar::save(core::data &da) const
{
    cor::Pubsub iq;
    to_iq(iq);
    
    xmlnode_t* items = iq.root->add_node("items");
    items->add_attr("node", "urn:xmpp:avatar:data");
    items->add_node("item")->add_attr("id", idr);
    
    return iq.save(da);
}

// -------------------------- IQ-Base Avatar

IQAvatar::IQAvatar()
{
    type = cor::IQ_GET;
}

bool IQAvatar::couldload(xmlnode_t const*)
{
    return false;
}

bool IQAvatar::load(xmlnode_t const*)
{
    return false;
}

void IQAvatar::process(Client&)
{
    
}

bool IQAvatar::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);
    iq.from.clear();
    
    iq.root.add_node("query")->ns = "jabber:iq:avatar";
    
    return iq.save(da);
}

XMPPXEP_END
