
# include "Core.h"
# include "XimPresence.h"
# include "../XmppIMClient.h"

XMPPIM_BEGIN

Presence::Presence()
: show(PT_NULL)
{
    
}

bool Presence::couldload(xmlnode_t const* node)
{
    return 
    node->parent && 
    node->parent->name == "presence";
}

bool Presence::load(xmlnode_t const* _node)
{
    xmlnode_t const* node = _node->parent;
    xmlattr_t const* attr = NULL;
    
    from.clear();
    to.clear();
    
    if ((attr = node->attribute("from")))
    {
        from.set(attr->value);
    }
    
    if ((attr = node->attribute("to")))
    {
        to.set(attr->value);
    }
    
    return true;
}

void Presence::load_node(xmlnode_t const* node)
{
    xmlattr_t const* attr = NULL;
    
    from.clear();
    to.clear();
    show = PT_ONLINE;
    
    if ((attr = node->attribute("from")))
    {
        from.set(attr->value);
    }
    
    if ((attr = node->attribute("to")))
    {
        to.set(attr->value);
    }
    
    if ((attr = node->attribute("type")))
    {
        show = PresenceTypeFromString(attr->value);
    }
}

void Presence::process(Client& cli)
{
    if (from == cli.jid)
        return;
}

bool Presence::save(core::data &da) const
{
    xmlnode_t node("presence");
    
    if (show != PT_NULL)
        node.add_node("show")->value = PresenceTypeToString(show);
    else if (!str_show.empty())
        node.add_node("show")->value = str_show;
    else
        node.add_node("show");
    
    if (!status.empty())
        node.add_node("status")->value = status;
    
    return node.save(da);
}

XMPPIM_END