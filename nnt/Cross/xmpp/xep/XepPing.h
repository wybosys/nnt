
# ifndef __NNT_XMPP_XEP_PING_C4265FBBD42D4CEAA7FC0E4A6FA872BF_H_INCLUDED
# define __NNT_XMPP_XEP_PING_C4265FBBD42D4CEAA7FC0E4A6FA872BF_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

NNTCLASS(Ping);

class Ping
: public ObjectImpl<Ping>
{

    typedef ObjectImpl<Ping> super;
    
public:
    
    Ping();
    
    static bool couldload(xmlnode_t const*);    
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual void update(Client const&);
    virtual bool save(core::data&) const;   
    
};

XMPPXEP_HEADER_END

# endif