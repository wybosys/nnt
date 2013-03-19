
# include "Core.h"
# include "XepMUC.h"
# include "../XmppIMClient.h"

XMPPXEP_BEGIN
WSI_BEGIN_NS(muc)

UserRole UserRoleFromString(core::string const& str)
{
    UserRole ret = UR_NONE;
    
    if (str == "moderator")
        ret = UR_MODERATOR;
    else if (str == "participant")
        ret = UR_PARTICIPANT;
    else if (str == "visitor")
        ret = UR_VISITOR;
    
    return ret;
}

core::string UserRoleToString(UserRole ur)
{
    core::string ret = "none";
    
    switch (ur)
    {
        default: break;
        case UR_MODERATOR: ret = "moderator"; break;
        case UR_PARTICIPANT: ret = "participant"; break;
        case UR_VISITOR: ret = "visitor"; break;
    }
    
    return ret;
}

UserAffiliation UserAffiliationFromString(core::string const& str)
{
    UserAffiliation ret = UA_NONE;
    
    if (str == "owner")
        ret = UA_OWNER;
    else if (str == "admin")
        ret = UA_ADMIN;
    else if (str == "member")
        ret = UA_MEMBER;
    else if (str == "outcast")
        ret = UA_OUTCAST;
    
    return ret;
}

core::string UserAffiliationToString(UserAffiliation ua)
{
    core::string ret = "none";
    
    switch (ua)
    {
        default: break;
        case UA_OWNER: ret = "owner"; break;
        case UA_ADMIN: ret = "admin"; break;
        case UA_MEMBER: ret = "member"; break;
        case UA_OUTCAST: ret = "outcast"; break;
    }
    
    return ret;
}

void Enter::update(Client const& cli)
{
    if (idr.empty())
        idr = "muc_" + core::tostr(cli.counter_any());
    
    if (from.empty())
        from = cli.jid;
}

bool Enter::save(core::data &da) const
{
    xmlnode_t node("presence");
    
    node.add_attr("from", from.full());
    node.add_attr("to", to.full());
    node.add_attr("id", idr);
    
    return node.save(da);
}

bool Presence::couldload(xmlnode_t const* node)
{
    return
    node->name == "x" &&
    node->ns == "http://jabber.org/protocol/muc#user";
}

bool Presence::load(xmlnode_t const* node)
{
    xmlnode_t const* item = node->node("item");
    if (item == NULL)
        return false;
    
    xmlattr_t const* attr_jid = item->attribute("jid");
    xmlattr_t const* attr_affi = item->attribute("affiliation");
    xmlattr_t const* attr_role = item->attribute("role");
    
    if (!(attr_jid && attr_affi && attr_role))
        return false;
    
    user = attr_jid->value;
    affiliation = UserAffiliationFromString(attr_affi->value);
    role = UserRoleFromString(attr_role->value);
    
    return super::load(node);
}

void Presence::process(Client& cli)
{
    super::process(cli);
    
    cli.emit(kSignalMUCPresence, cxx::eventobj_t::Data(this));
}

void Presence::update(Client const& cli)
{
    if (idr.empty())
        idr = "muc_" + core::tostr(cli.counter_any());
    
    if (from.empty())
        from = cli.jid;
}

bool Presence::save(core::data &da) const
{
    xmlnode_t node("presence");
    
    node.add_attr("from", from.full());
    node.add_attr("to", to.full());
    node.add_attr("id", idr);
    node.add_node("x")->ns = "http://jabber.org/protocol/muc";
    
    return node.save(da);
}

WSI_END_NS
XMPPXEP_END
