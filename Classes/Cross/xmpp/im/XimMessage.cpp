
# include "Core.h"
# include "XimMessage.h"
# include "../XmppIMClient.h"

XMPPIM_BEGIN

Message::Message()
{
    type = MT_CHAT;
}

bool Message::couldload(xmlnode_t const* node)
{
    return 
    node->name == "body";
}

bool Message::load(xmlnode_t const* node)
{
    content = node->value;
    return super::load(node);
}

void Message::process(Client& cli)
{
    eventobj_t evt;
    evt.data = this;
    cli.emit(kSignalNewMessage, evt);
}

void Message::update(Client const& cli)
{
    if (from.empty())
        from = cli.jid;
    
    if (to.address.empty())
        to.address = from.address;    
}

bool Message::save(core::data & da) const
{
    xmlnode_t node("message");
    
    xmlattr_t* attr = node.add_attr("from");
    attr->value = from.full();
    
    attr = node.add_attr("to");
    attr->value = to.bare();
    
    attr = node.add_attr("type");
    attr->value = MessageTypeToString(type);
    
    attr = node.add_attr("xml:lang");
    attr->value = "utf-8";
    
    xmlnode_t* child = node.add_node("body");
    child->value = content;
    
    return node.save(da);
}

XMPPIM_END