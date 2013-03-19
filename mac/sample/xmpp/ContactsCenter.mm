
# include <wsi/WSIFoundation.h>
# include "ContactsCenter.h"

# include <wsi/Cross/xmpp/im/XimRoster.h>

WSIAPP_BEGIN

Contact::Contact()
: data(NULL)
{
    
}

Contact::~Contact()
{
    safe_drop(data);
}

Group::Group()
{
    
}

Group::~Group()
{
    clear();
}

void Group::clear()
{
    core::clear_destroy(contacts);
    core::clear_destroy(groups);
}

ContactsCenter::ContactsCenter()
{
    
}

void ContactsCenter::clear()
{
    tree.clear();
}

void ContactsCenter::load(contacts_type const& contacts)
{
    clear();
    
    for (contacts_type::const_iterator each = contacts.begin();
         each != contacts.end();
         ++each)
    {
        xmpp::im::User const* data = *each;
        
        for (xmpp::im::User::groups_type::const_iterator each = data->groups.begin();
             each != data->groups.end();
             ++each)
        {
            core::string const& group = (*each)->name;
            core::deque<core::string> groups;
            core::split(group, "/", groups);
            
            // insert.
            Group* groupobj = &tree;
            while (groups.size())
            {
                core::string const& cur_grp = groups.front();
                Group::groups_type::iterator found = groupobj->groups.find(cur_grp);
                if (found == groupobj->groups.end())
                {
                    // insert group.
                    groupobj = groupobj->groups.insert(core::make_pair(cur_grp, new Group())).first->second;
                    groupobj->name = cur_grp;
                }
                else
                {
                    groupobj = found->second;
                }
                
                groups.pop_front();
            }
            
            // insert contact.
            Contact* obj = new Contact;
            obj->data = data;
            data->grab();
            groupobj->contacts.push_back(obj);
            
        }
    }
}

WSIAPP_END