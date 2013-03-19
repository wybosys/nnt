
# ifndef __NNT_XMPP_CORE_BIND_F5FAA7626C8B456994459C831F0E5F79_H_INCLUDED
# define __NNT_XMPP_CORE_BIND_F5FAA7626C8B456994459C831F0E5F79_H_INCLUDED

# include "XmppCore.h"
# include "XmppJID.h"

XMPPCORE_HEADER_BEGIN

class Bind
: public ObjectImpl<Bind>
{
public:
    
    Bind();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    virtual void update(Client const&);
    virtual void process(Client&);
  
    ulong idr;
    Jid jid;
    
};

XMPPCORE_HEADER_END

# endif