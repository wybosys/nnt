
# include "Core.h"
# include "XepVersion.h"
# include "../XmppClient.h"
# include "../core/XmppIQ.h"

XMPPXEP_BEGIN

Version::Version()
{
    
}

bool Version::couldload(xmlnode_t const* node)
{
    return 
    node->name == "query" &&
    node->ns == "jabber:iq:version";
}

bool Version::load(xmlnode_t const* node)
{
    return super::load(node);
}

void Version::process(Client& cli)
{
    Version* obj = (Version*)this->instance();
    obj->type = cor::IQ_RESULT;
    obj->to = from;
    obj->name = cli.setting.name;
    obj->version = cli.setting.version;
    obj->idr = idr;
    
    cli.execute(*obj);
    
    safe_delete(obj);
}

bool Version::save(core::data &da) const
{
    cor::IQ iq;
    iq.type = type;
    iq.to = to;
    iq.idr = idr;
    
    xmlnode_t* node = new xmlnode_t("query");
    node->ns = "jabber:iq:version";
    node->add_node("name")->value = name;
    node->add_node("version")->value = version;
    node->add_node("os")->value = "nnt toolkit";
    
    iq.root.add(node);
    
    bool suc = iq.save(da);
    
    node->drop();
    
    return suc;
}

XMPPXEP_END