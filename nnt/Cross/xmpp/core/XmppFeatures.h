
# ifndef __XMPP_CONFIGURATION_E2BC15FEE9FC40EDA2F55841DEAF6032_H_INCLUDED
# define __XMPP_CONFIGURATION_E2BC15FEE9FC40EDA2F55841DEAF6032_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Sasl;
class Compression;
class Auth;
class Bind;
class Session;

class Features
: public ObjectImpl<Features>
{
    
public:
    
    Features();
    ~Features();
       
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual void process(Client&);
    
protected:           
    
    Sasl* _sasl;
    Compression* _compression;
    Bind* _bind;
    Session* _session;
    
};

XMPPCORE_HEADER_END

# endif