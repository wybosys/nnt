
# ifndef __WSI_XMPP_IM_SHOW_9E7DAFAB7A9046CAB8748F0CF0838BDB_H_INCLUDED
# define __WSI_XMPP_IM_SHOW_9E7DAFAB7A9046CAB8748F0CF0838BDB_H_INCLUDED

# include "XimIM.h"
# include "../core/XmppJID.h"

XMPPIM_HEADER_BEGIN

class Show
: public ObjectImpl<Show>
{
    typedef ObjectImpl<Show> super;
    
public:
    
    Show();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    virtual void process(Client&);
    
    //! type.
    PresenceType type;
    core::string str_type;
    
};

XMPPIM_HEADER_END

# endif
