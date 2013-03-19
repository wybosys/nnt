
# include "Core.h"
# include "XimContact.h"

XMPPIM_BEGIN

Contact::Contact(im::User const* usr)
: idr(0)
{
    set(usr);
}

Contact::~Contact()
{

}

void Contact::clear()
{
    type = CT_UNKNOWN;
    name.clear();
    jid.clear();
}

void Contact::set(im::User const* usr)
{
    if (usr == 0)
    {
        clear();
        return;
    }
    
    type = CT_CONTACT;
    name = usr->name;
    jid = usr->jid;
}

Contact::groups_type const& Contact::parent() const
{
    return _parent;
}

Group::Group()
{
    type = CT_GROUP;
}

Group::Group(core::string const& nm)
{
    type = CT_GROUP;
    name = nm;
}

Group::~Group()
{
    
}

Contact* Group::add(Contact* obj)
{
    if (exist(obj))
        return obj;
    
    // as child.
    _children.push_back(obj);
    safe_grab(obj);
    
    // as group.
    if (obj)
    {
        obj->_parent.push_back(this);
    }
    
    return obj;
}

Group* Group::add(Group* obj)
{
    add((Contact*)obj);
    return obj;
}

bool Group::exist(Contact const* obj) const
{
    children_type::const_iterator found = ::std::find(_children.begin(), _children.end(), obj);
    return found != _children.end();
}

Contact* Group::find_contact(cor::Jid const& jid)
{
    for (children_type::iterator each = _children.begin();
         each != _children.end();
         ++each)
    {
        Contact* ct = *each;
        if (ct->type == CT_CONTACT &&
            ct->jid == jid)
            return ct;
    }
    return NULL;
}

Group* Group::find_group(core::string const& name)
{
    for (children_type::iterator each = _children.begin();
         each != _children.end();
         ++each)
    {
        Contact* ct = *each;
        if (ct->type == CT_GROUP &&
            ct->name == name)
            return dynamic_cast<Group*>(ct);
    }
    return NULL;
}

Group::children_type const& Group::children() const
{
    return _children;
}

Group const* Group::parent() const
{
    if (super::parent().size() == 0)
        return NULL;
    return super::parent().front();
}

XMPPIM_END
