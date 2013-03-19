
# ifndef __XMPP_MESSAGE_FACTORY_669EE54A731549F9996805C28666747B_H_INCLUDED
# define __XMPP_MESSAGE_FACTORY_669EE54A731549F9996805C28666747B_H_INCLUDED

# include "XmppResponseFactory.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(xmpp)

class MessageFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    MessageFactory();
    ~MessageFactory();
    
    virtual bool process(xmlnode_t const*);

};

WSI_END_NS
WSI_END_HEADER_CXX

# endif