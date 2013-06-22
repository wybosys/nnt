
# ifndef __XMPP_CHALLENGEFACTORY_5E843FAE8F9D4B69AC9C7485EF5EFE3E_H_INCLUDED
# define __XMPP_CHALLENGEFACTORY_5E843FAE8F9D4B69AC9C7485EF5EFE3E_H_INCLUDED

# include "XmppResponseFactory.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(xmpp)

class ChallengeFactory
: public AbstractResponseFactory
{
    typedef AbstractResponseFactory super;
    
public:
    
    ChallengeFactory();
    ~ChallengeFactory();
    
    virtual bool process(xmlnode_t const*);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif