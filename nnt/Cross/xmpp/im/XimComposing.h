
# ifndef __WSI_XMPP_IM_COMPOSING_9C1F3BC454734B3E82CF768C86B84018_H_INCLUDED
# define __WSI_XMPP_IM_COMPOSING_9C1F3BC454734B3E82CF768C86B84018_H_INCLUDED

# include "XimIM.h"
# include "../core/XmppJID.h"

XMPPIM_HEADER_BEGIN

class Composing
: public ObjectImpl<Composing>
{
    typedef ObjectImpl<Composing> super;
    
public:
    
    Composing();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;    
    virtual void process(Client&);
    
};

XMPPIM_HEADER_END

# endif