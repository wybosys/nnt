
# ifndef __WSI_XMPP_IM_ACTIVE_763A343BB1714FA1AE678C1AB2C4A637_H_INCLUDED
# define __WSI_XMPP_IM_ACTIVE_763A343BB1714FA1AE678C1AB2C4A637_H_INCLUDED

# include "XimIM.h"
# include "../core/XmppJID.h"

XMPPIM_HEADER_BEGIN

class Active
: public ObjectImpl<Active>
{
    typedef ObjectImpl<Active> super;
    
public:
    
    Active();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;    
    virtual void process(Client&);
    
};

XMPPIM_HEADER_END

# endif