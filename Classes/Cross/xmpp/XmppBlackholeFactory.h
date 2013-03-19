
# ifndef __NNT_XMPP_BLACKHOLEFACTORY_80B9B2DFB5114D08AF63602370E7E0E3_H_INCLUDED
# define __NNT_XMPP_BLACKHOLEFACTORY_80B9B2DFB5114D08AF63602370E7E0E3_H_INCLUDED

# include "XmppResponseFactory.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(xmpp)

class BlackholeFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    BlackholeFactory();
    ~BlackholeFactory();
    
    virtual bool process(xmlnode_t const*);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif