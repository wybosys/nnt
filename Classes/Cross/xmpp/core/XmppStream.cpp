
# include "Core.h"
# include "XmppStream.h"
# include "../XmppClient.h"

XMPPCORE_BEGIN

Stream::Stream()
{
    
}

Stream::~Stream()
{
    
}

bool Stream::couldload(xmlnode_t const* node)
{
    return
    node->name == "stream" &&
    node->ns == "http://etherx.jabber.org/streams";
}

bool Stream::load(xmlnode_t const* node)
{
    xmlattr_t const* attr = NULL;
    
    if ((attr = node->attribute("id")))
    {
        idr = attr->value;
    }
    
    if ((attr = node->attribute("from")))
    {
        from = attr->value;
    }
    
    return true;
}

void Stream::process(Client& cli)
{
    if (cli.idr.empty())
        cli.idr = idr;

    if (cli.server.empty())
        cli.server = from;
}

bool Stream::save(core::data & da) const
{
    parser::XmlDocument doc;
    parser::XmlNode* node = doc.root();
    
    node->name = "stream";
    node->ns = "http://etherx.jabber.org/streams";
    node->prefix = "stream";
    
    if (from.empty() == false)
        node->add_attr("from", from);
    
    if (idr.empty() == false)
        node->add_attr("id", idr);
    
    if (to.empty() == false)
        node->add_attr("to", to);
    
    node->add_attr("xml:lang", "utf-8");
    node->add_attr("xmlns", "jabber:client");
    node->add_attr("version", "1.0");    
    if (false == doc.save(da))
        return false;
        
    da.set_length(da.length() - 16);
    return true;
}

XMPPCORE_END