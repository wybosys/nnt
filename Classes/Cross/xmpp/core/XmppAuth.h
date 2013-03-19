
# ifndef __XMPP_AUTH_C2B59A24E19F4277ACDF340D0DF2CCCB_H_INCLUDED
# define __XMPP_AUTH_C2B59A24E19F4277ACDF340D0DF2CCCB_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Auth
: public ObjectImpl<Auth>
{
public:
    
    Auth();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(::wsi::core::data&) const;    
    virtual void process(Client&);
    
    core::string user;
    core::string passwd;
    core::string address;
    MechanismType mechanism;
};

XMPPCORE_HEADER_END

# endif