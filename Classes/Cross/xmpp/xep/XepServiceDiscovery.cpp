
# include "Core.h"
# include "XepServiceDiscovery.h"

XMPPXEP_BEGIN

DiscoInfo::DiscoInfo()
{
    type = cor::IQ_GET;
}

bool DiscoInfo::couldload(xmlnode_t const* node)
{
    return
    node->name == "query" &&
    node->ns == "http://jabber.org/protocol/disco#info";
}

bool DiscoInfo::load(xmlnode_t const* node)
{
    identities.clear();
    features.clear();
    
    xmlattr_t const* attr;
    xmlnode_t const* each = node->first;
    while (each)
    {
        if (each->name == "identity")
        {
            ServiceIdentity obj;
            if ((attr = each->attribute("category")))
                obj.category = attr->value;
            if ((attr = each->attribute("name")))
                obj.name = attr->value;
            if ((attr = each->attribute("type")))
                obj.type = attr->value;
            
            identities << obj;
        }
        else if (each->name == "feature")
        {
            ServiceFeature obj;
            if ((attr = each->attribute("var")))
                obj.var = attr->value;
            
            features << obj;
        }
        
        each = each->next;
    }
    
    return super::load(node);
}

void DiscoInfo::process(Client& cli)
{
    cli.emit(kSignalDiscoInfo, eventobj_t::Data(this));
}

void DiscoInfo::update(Client const& cli)
{
    if (idr.empty())
        idr = "discoinfo_" + core::tostr(cli.counter_any());
    
    if (from.empty())
        from = cli.jid;
    
    if (to.empty())
        to = cli.server;
}

bool DiscoInfo::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);

    iq.root.add_node("query")->ns = "http://jabber.org/protocol/disco#info";
    
    return iq.save(da);
}

// item

DiscoItem::DiscoItem()
{
    type = cor::IQ_GET;
}

bool DiscoItem::couldload(xmlnode_t const* node)
{
    return
    node->name == "query" &&
    node->ns == "http://jabber.org/protocol/disco#items";
}

bool DiscoItem::load(xmlnode_t const* node)
{
    items.clear();
    
    xmlnode_t const* each = node->first;
    xmlattr_t const* attr;
    
    while (each)
    {
        if (each->name == "item")
        {
            ServiceItem obj;
            if ((attr = each->attribute("jid")))
                obj.jid = attr->value;
            if ((attr = each->attribute("name")))
                obj.name = attr->value;
        
            items << obj;
        }
        
        each = each->next;
    }
    
    return super::load(node);
}

void DiscoItem::process(Client& cli)
{
    cli.emit(kSignalDiscoItems, eventobj_t::Data(this));
}

void DiscoItem::update(Client const& cli)
{
    if (idr.empty())
        idr = "discoitem_" + core::tostr(cli.counter_any());
    
    if (from.empty())
        from = cli.jid;
    
    if (to.empty())
        to = cli.server;
}

bool DiscoItem::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);
    
    iq.root.add_node("query")->ns = "http://jabber.org/protocol/disco#items";
    
    return iq.save(da);
}

XMPPXEP_END
