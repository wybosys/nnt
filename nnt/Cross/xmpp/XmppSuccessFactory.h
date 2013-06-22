
# ifndef __NNT_XMPP_SUCCESSFACTORY_CF34834D30FB4A39BFF5EF6DE1312775_H_INCLUDED
# define __NNT_XMPP_SUCCESSFACTORY_CF34834D30FB4A39BFF5EF6DE1312775_H_INCLUDED

# include "XmppResponseFactory.h"

XMPP_HEADER_BEGIN

class SuccessFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    SuccessFactory();
    ~SuccessFactory();
    
    virtual bool process(xmlnode_t const*);
    
};

XMPP_HEADER_END

# endif