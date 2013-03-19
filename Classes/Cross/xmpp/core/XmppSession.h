
# ifndef __WSI_XMPP_CORE_SESSION_25D498B05B754E39AB847288498B9D1D_H_INCLUDED
# define __WSI_XMPP_CORE_SESSION_25D498B05B754E39AB847288498B9D1D_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Session
: public ObjectImpl<Session>
{
public:
    
    Session();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;    
    virtual void process(Client&);
  
    ulong idr;
};

XMPPCORE_HEADER_END

# endif