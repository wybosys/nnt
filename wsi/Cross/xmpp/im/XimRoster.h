
# ifndef __WSI_XMPP_IM_ROSTER_553DAB23DC91418F9D354681D8E8DC48_H_INCLUDED
# define __WSI_XMPP_IM_ROSTER_553DAB23DC91418F9D354681D8E8DC48_H_INCLUDED

# include "XimIM.h"
# include "../core/XmppJID.h"
# include "XimUser.h"

XMPPIM_HEADER_BEGIN

WSICLASS(RosterQuery);

class RosterQuery
: public ObjectImpl<RosterQuery>
{
public:
    
    typedef core::refpointer_vector<im::User> contacts_type;
    
    RosterQuery();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;    
    virtual void process(Client&);
    virtual void update(Client const&);
    
    //! from jid.
    cor::Jid from;
    
    //! id of roster.
    ulong idr;
    
    //! result of query.
    contacts_type contacts;
    
public:
    
    virtual im::User::group* newgroup() const;
    virtual void loaduser(im::User&, xmlnode_t const*) const;
    virtual void loadgroup(im::User::group&, xmlnode_t const*) const;
    virtual void resize_users(uint sz);
    
};

XMPPIM_HEADER_END

# endif