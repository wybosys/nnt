
# include "Core.h"
# include "XepXHtmlIm.h"
# include "../XmppIMClient.h"
# include "XepField.h"

XMPPXEP_BEGIN

HtmlMessage::HtmlMessage()
{
    
}

bool HtmlMessage::couldload(xmlnode_t const* node)
{
    return
    node->name == "html";
}

bool HtmlMessage::load(xmlnode_t const* node)
{
    body.clear();
    data.clear();
        
    // load.
    xmlnode_t const* bodynode = node->prev;
    if (bodynode && bodynode->name == "body")
    {
        body = bodynode->value;
    }
    
    bool suc = super::load(node);
    if (suc == false)
        return false;
    
    // process content.
    suc = data.load(core::type_cast<core::data>(node->value));
    if (suc == false)
        return false;
        
    return suc;
}

void HtmlMessage::process_filter(xmlnode_t *node, Client& cli)
{
    if (node->name == "img")
    {
        Field fld = node->value;
        cli.emit(kSignalGotField, eventobj_t::Data(this, &fld));
    }
    
    // each child.
    for (xmlnode_t::children_type::iterator iter = node->children.begin();
         iter != node->children.end();
         ++iter)
    {
        process_filter(iter->second, cli);
    }
}

void HtmlMessage::process(Client& cli)
{
    // process sub.
    process_filter(&data, cli);
    
    // emit message.
    cli.emit(kSignalHtmlMessage, eventobj_t::Data(this));
}

bool HtmlMessage::save(core::data &da) const
{
    xmlnode_t node("message");
    node.add_attr("from", from.full());
    node.add_attr("to", to.bare());
    node.add_node("body", body);
    node.add_node("html", getdata())->ns = "http://jabber.org/protocol/xhtml-im";
    
    return node.save(da);
}

bool HtmlMessage::getdata(core::data &da, xmlnode_t const& node) const
{
    return node.save(da);
}

core::string HtmlMessage::getdata() const
{
    core::data da;
    bool suc = getdata(da, data);
    if (suc == false)
        return core::null_string;
    return core::type_cast<core::string>(da);
}

XMPPXEP_END
