
# ifndef __NNT_XMPP_IM_PRESENCE_44C6AB34CB2E4590869A43104E914888_H_INCLUDED
# define __NNT_XMPP_IM_PRESENCE_44C6AB34CB2E4590869A43104E914888_H_INCLUDED

# include "XimIM.h"

XMPPIM_HEADER_BEGIN

NNTCLASS(Presence);

class Presence
: public cor::ObjectImpl<Presence>
{
public:
    
    Presence();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;    
    virtual void process(Client&);
    
    void load_node(xmlnode_t const*);
    
    //! show type.
    PresenceType show;
    core::string str_show;
    
    //! text for status.
    core::string status;
    
    //! ids.
    cor::Jid from, to;
    
};

XMPPIM_HEADER_END

# endif