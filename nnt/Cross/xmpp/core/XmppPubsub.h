
# ifndef __WSI_XMPP_CORE_PUBSUB_D276FAAAEA5045F188FADF321E097A42_H_INCLUDED
# define __WSI_XMPP_CORE_PUBSUB_D276FAAAEA5045F188FADF321E097A42_H_INCLUDED

# include "XmppIQ.h"

XMPPCORE_HEADER_BEGIN

class Pubsub
: public IQ
{
    typedef IQ super;
    
public:
    
    Pubsub();
    
    xmlnode_t *root;
    
};

XMPPCORE_HEADER_END

# endif
