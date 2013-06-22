
# ifndef __NNT_XMPP_IM_CONTACT_4EA24CD5BB9444E39B12A8E3597D140F_H_INCLUDED
# define __NNT_XMPP_IM_CONTACT_4EA24CD5BB9444E39B12A8E3597D140F_H_INCLUDED

# include "XimIM.h"
# include "XimUser.h"
# include "../core/XmppJID.h"

XMPPIM_HEADER_BEGIN

NNTCLASS(Contact);
NNTCLASS(Group);

enum
{
    CT_UNKNOWN,
    CT_CONTACT = CT_UNKNOWN,
    CT_GROUP,
};
typedef uint ContactType;

class Contact
: public RefObject
{
    friend class Group;
    
public:
        
    Contact(im::User const* = NULL);
    virtual ~Contact();
    
    typedef core::list<Group*> groups_type;
    
public:
    
    void clear();
    void set(im::User const*);
    
    //! idr for store. default 0.
    ulong idr;
        
    //! name.
    core::string name;
    
    //! jid.
    cor::Jid jid;
    
    //! type.
    ContactType type;
    
    //! parent.
    groups_type const& parent() const;
    
protected:
    
    //! parent groups.
    groups_type _parent;

};

class Group
: public Contact
{
    typedef Contact super;
    
public:
    
    Group();
    Group(core::string const&);
    virtual ~Group();
    
    typedef core::refpointer_vector<Contact> children_type;
    
public:
    
    //! add contact.
    Contact* add(Contact*);
    
    //! add group.
    Group* add(Group*);
    
    //! exist contact.
    bool exist(Contact const*) const;
    
    //! find contact by jid.
    Contact* find_contact(cor::Jid const&);
    
    //! find group by name.
    Group* find_group(core::string const&);
    
    //! get.
    children_type const& children() const;
    
    //! get parent.
    Group const* parent() const;
        
protected:
    
    children_type _children;
    
};

XMPPIM_HEADER_END

# endif
