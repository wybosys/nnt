
# ifndef __WSI_XMPP_BLACKHOLEFACTORY_80B9B2DFB5114D08AF63602370E7E0E3_H_INCLUDED
# define __WSI_XMPP_BLACKHOLEFACTORY_80B9B2DFB5114D08AF63602370E7E0E3_H_INCLUDED

# include "XmppResponseFactory.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(xmpp)

class BlackholeFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    BlackholeFactory();
    ~BlackholeFactory();
    
    virtual bool process(xmlnode_t const*);
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif