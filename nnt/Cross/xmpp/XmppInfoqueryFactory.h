
# ifndef __XMPP_IQ_FACTORY_CF2D1785584A4EA7A66E093FA9E42E99_H_INCLUDED
# define __XMPP_IQ_FACTORY_CF2D1785584A4EA7A66E093FA9E42E99_H_INCLUDED

# include "XmppResponseFactory.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(xmpp)

class InfoqueryFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    InfoqueryFactory();
    ~InfoqueryFactory();
    
    virtual bool process(xmlnode_t const*);
    
public:
    
    core::string from, to, idr;
    cor::IqType type;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif