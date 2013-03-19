
# ifndef __XMPP_RESPONSE_1D034B9E5FA945E7A3CA76EDC5531032_H_INCLUDED
# define __XMPP_RESPONSE_1D034B9E5FA945E7A3CA76EDC5531032_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Response
: public ObjectImpl<Response, StringObject>
{
    
public:
    
    Response();
    
    static bool couldload(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
};

XMPPCORE_HEADER_END

# endif