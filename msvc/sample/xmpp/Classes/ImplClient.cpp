
# include <nnt/Foundation+NNT.h>
# include "ImplClient.h"
# include <nnt/store/Sqlite+NNT.h>
# include <nnt/Core/Directory+NNT.h>
# include <nnt/Cross/xmpp/im/XimMessage.h>
# include <nnt/Cross/xmpp/im/XimXPhoto.h>
# include <nnt/Cross/xmpp/xep/XepVCard.h>

NNTAPP_BEGIN

void Client::set(xmpp::IMClient& cli)
{
    super::set(cli);
    
    cli.connect(xmpp::kSignalNewMessage, _cxxaction(_class::mdl_message), this);
    cli.connect(xmpp::kSignalXPhoto, _cxxaction(_class::mdl_xphoto), this);
}

xmpp::im::Group* Client::mkgrp(xmpp::im::User const* usr, xmpp::im::Group* root, xmpp::im::User::group const&) const
{
    if (usr->groups.size() == 0)
        return NULL;
    
    xmpp::im::Group* grp = root;
    
    // split.
    core::string const& group = usr->groups.front()->name;
    core::deque<core::string> groups;
    core::split(group, "/", groups);
    
    // find & insert.
    while (groups.size())
    {
        core::string const& cur_grp = groups.front();
        xmpp::im::Group* found = grp->find_group(cur_grp);
        if (found == NULL)
        {
            found = new xmpp::im::Group(cur_grp);
            grp->add(found);
            safe_drop(found);
        }
        grp = found;
        
        groups.pop_front();
    }

    safe_grab(grp);
    return grp;
}

static ulong __gs_iduser = 0;
static ulong __gs_idgroup = 0;

void save_contact(store::Sqlite& db, xmpp::im::Contact* user)
{
    if (user->idr != 0)
        return;
    
    core::string sql = "INSERT INTO CONTACTS ('id', 'gid', 'name', 'jid') VALUES (";
    user->idr = ++__gs_iduser;
    sql += core::tostr(user->idr) + ", ";
    sql += core::tostr(user->parent().front()->idr) + ", ";
    sql += "'" + user->name + "'" + ", ",
    sql += "'" + user->jid.to_string() + "'";
    sql += ")";
    db.exec(sql);
}

void save_group(store::Sqlite& db, xmpp::im::Group* grp)
{
    if (grp->idr != 0)
        return;
    grp->idr = ++__gs_idgroup;
    
    core::string sql = "INSERT INTO GROUPS ('id', 'pid', 'name') VALUES (";
    sql += core::tostr(grp->idr) + ", ";
    sql += core::tostr(TRIEXP(grp->parent(), grp->parent()->idr, -1)) + ", ";
    sql += "'" + grp->name + "'";
    sql += ")";
    db.exec(sql);

    for (xmpp::im::Group::children_type::const_iterator each = grp->children().begin();
         each != grp->children().end();
         ++each)
    {
        xmpp::im::Contact* user = core::down_const(*each);
        xmpp::im::Group* chgrp = dynamic_cast<xmpp::im::Group*>(user);
        if (!chgrp ||
            chgrp->idr != 0)
        {
            // save contact.
            save_contact(db, user);
            continue;
        }
 
        // save child.
        save_group(db, chgrp);
    }
}

bool Client::save(xmpp::im::Group* root)
{
    return true;
}

void Client::mdl_message(cxx::eventobj_t &evt)
{

}

void Client::mdl_xphoto(cxx::eventobj_t &evt)
{
    xmpp::im::XPhoto* photo = evt;
    xmpp::xep::VCard obj;
    obj.to = photo->from.to_address();
    client().execute(obj);
}

NNTAPP_END
