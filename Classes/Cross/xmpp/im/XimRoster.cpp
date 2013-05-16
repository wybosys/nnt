
# include "Core.h"
# include "XimRoster.h"
# include "../XmppIMClient.h"
# include "../core/XmppIQ.h"

XMPPIM_BEGIN

RosterQuery::RosterQuery()
: idr(0)
{
    
}

bool RosterQuery::couldload(xmlnode_t const* node)
{
    return 
    node->name == "query" &&
    node->ns == "jabber:iq:roster";
}

void RosterQuery::loaduser(im::User &each, xmlnode_t const* data) const
{
    xmlattr_t const* attr = NULL;

    if ((attr = data->attribute("name")))
    {
        each.name = attr->value;
    }
    
    if ((attr = data->attribute("jid")))
    {
        each.jid = attr->value;
    }
    
    // find all groups.
    xmlnode_t::const_nodes_result gdata = data->nodes("group");
    each.groups.clear();
    for (xmlnode_t::const_nodes_result::const_iterator iter = gdata.begin();
         iter != gdata.end();
         ++iter)
    {
        xmlnode_t const* node = *iter;
        
        User::group* grp = this->newgroup();
        
        // load.
        this->loadgroup(*grp, node);
        
        // release in groups.
        each.groups.push_back(grp);
    }

}

User::group* RosterQuery::newgroup() const
{
    return new User::group;
}

void RosterQuery::loadgroup(im::User::group &grp, const xmlnode_t *node) const
{
    grp.name = node->value;
}

void RosterQuery::resize_users(uint sz)
{
    contacts.resize(sz);
}

bool RosterQuery::load(xmlnode_t const* node)
{
    // resize.
    this->resize_users((uint)node->children.size());
    
    // load.
    for (core::counter<xmlnode_t::nodes_type::const_iterator> iter = node->children.begin();
         iter != node->children.end();
         ++iter)
    {
        xmlnode_t const* data = iter->second;
        im::User& each = *contacts[iter.count];
        
        // load user.
        this->loaduser(each, data);
    }
    
    return true;
}

void RosterQuery::process(Client& cli)
{
    eventobj_t evt;
    evt.data = &contacts;
    cli.emit(kSignalRosterComplete, evt);
}

void RosterQuery::update(Client const& cli)
{
    IMClient const& imcli = (IMClient const&)cli;
    
    if (idr == 0)
        idr = imcli.roster_counter();
    
    if (from.empty())
        from = imcli.jid;
}

bool RosterQuery::save(core::data &da) const
{
    cor::IQ iq;
    iq.from = from.full();
    iq.type = cor::IQ_GET;
    iq.idr = "roster_" + core::tostr(idr);
    iq.root.add_node("query")->ns = "jabber:iq:roster";
    
    return iq.save(da);
}

XMPPIM_END