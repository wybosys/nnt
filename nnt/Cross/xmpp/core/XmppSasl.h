
# ifndef __XMPP_SASL_16F46320B26D45D3BB73A6AB45B02B91_H_INCLUDED
# define __XMPP_SASL_16F46320B26D45D3BB73A6AB45B02B91_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Sasl
: public ObjectImpl<Sasl>
{
public:
    
    Sasl();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual void process(Client&);
    
protected:

    enum_t _mechanism;
    
};

XMPPCORE_HEADER_END

# endif