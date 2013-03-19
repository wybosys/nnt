
# ifndef __XMPP_CHALLENGEFACTORY_5E843FAE8F9D4B69AC9C7485EF5EFE3E_H_INCLUDED
# define __XMPP_CHALLENGEFACTORY_5E843FAE8F9D4B69AC9C7485EF5EFE3E_H_INCLUDED

# include "XmppResponseFactory.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(xmpp)

class ChallengeFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    ChallengeFactory();
    ~ChallengeFactory();
    
    virtual bool process(xmlnode_t const*);
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif