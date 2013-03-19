
# ifndef __XMPP_PRESENCE_FACTORY_AD8AF7AFF3AD4FC690AEC72FDF66B064_H_INCLUDED
# define __XMPP_PRESENCE_FACTORY_AD8AF7AFF3AD4FC690AEC72FDF66B064_H_INCLUDED

# include "XmppResponseFactory.h"

XMPP_HEADER_BEGIN

class PresenceFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    PresenceFactory();
    ~PresenceFactory();
    
    virtual bool process(xmlnode_t const*);
    
};

XMPP_HEADER_END

# endif