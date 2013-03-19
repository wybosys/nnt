
# include "Core.h"
# include "XmppIMClientor.h"
# include "im/XimRoster.h"
# include "im/XimUser.h"
# include "../../Core/Directory+NNT.h"

XMPP_BEGIN

NNTDECL_PRIVATE_BEGIN_CXX(IMClientor)

void init()
{
    
}

void dealloc()
{
    
}

void mdl_roster(eventobj_t& evt)
{
    ulong grpid = 0, usrid = 0;
    
    // convert from roster.
    im::Group* root = new im::Group("root");
    root->idr = ++grpid;
    
    im::RosterQuery::contacts_type const* data = (im::RosterQuery::contacts_type const*)evt.data;
    for (im::RosterQuery::contacts_type::const_iterator each = data->begin();
         each != data->end();
         ++each)
    {
        im::User const* cuser = *each;
        im::Contact* user = new im::Contact(cuser);
        // set user id.
        user->idr = ++usrid;
        
        for (im::User::groups_type::const_iterator each_group = cuser->groups.begin();
             each_group != cuser->groups.end();
             ++each_group)
        {
            im::Group* grp = d_owner->mkgrp(cuser, root, **each_group);
            
            // set group id.
            if (grp->idr == 0)
                grp->idr = ++grpid;
            
            im::Contact* ct = grp->find_contact(cuser->jid);
            if (ct == NULL)
            {
                grp->add(user);
            }
            safe_drop(grp);
        }
        safe_drop(user);
    }
    
    // save.
    if (d_owner->save(root) == false)
    {
        dthrow("failed to save group data.");
    }
    
    safe_drop(root);
}

NNTDECL_PRIVATE_END_CXX

IMClientor::IMClientor()
{
    NNTDECL_PRIVATE_CONSTRUCT(IMClientor);
}

IMClientor::IMClientor(IMClient& cli)
{
    NNTDECL_PRIVATE_CONSTRUCT(IMClientor);
    
    set(cli);
}

IMClientor::~IMClientor()
{
    NNTDECL_PRIVATE_DESTROY();
}

void IMClientor::set(IMClient& cli)
{
    // break.
    if (_client)
    {
        _client->disconnect(d_ptr);
    }
    
    // set
    Clientor::set(cli);
    
    // connect.
    _client->connect(kSignalRosterComplete, _action(private_type::mdl_roster), d_ptr);
}

IMClient const* IMClientor::operator -> () const
{
    return (IMClient const*)_client;
}

IMClient* IMClientor::operator -> ()
{
    return (IMClient *)_client;
}

IMClientor::operator IMClient& ()
{
    return *(IMClient *)_client;
}

IMClientor::operator IMClient const& () const
{
    return *(IMClient const*)_client;
}

IMClient const& IMClientor::client() const
{
    return *(IMClient const*)_client;
}

IMClient& IMClientor::client()
{
    return *(IMClient *)_client;
}

XMPP_END
