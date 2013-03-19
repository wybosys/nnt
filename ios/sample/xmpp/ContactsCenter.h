
# ifndef __CONTACTS_CENTER_1DB98D731F3D40B9ACB7A169162C5F44_H_INCLUDED
# define __CONTACTS_CENTER_1DB98D731F3D40B9ACB7A169162C5F44_H_INCLUDED

# include "XimUser.h"

WSIAPP_BEGIN

using namespace ::wsi;

class Contact
{
public:
    
    Contact();
    ~Contact();
    
    xmpp::im::User const* data;
    
};

class Group
: public Contact
{
public:
    
    typedef core::list<Contact*> contacts_type;
    typedef core::map<core::string, Group*> groups_type;
    
    Group();
    ~Group();
    
    void clear();
    
    contacts_type contacts;
    groups_type groups;
    
    core::string name;
    
};

class ContactsCenter
{
public:
    
    typedef core::vector<xmpp::im::User*> contacts_type;
    
    ContactsCenter();
    
    void clear();
    void load(contacts_type const&);
    
    Group tree;
    
};

WSIAPP_END

# endif