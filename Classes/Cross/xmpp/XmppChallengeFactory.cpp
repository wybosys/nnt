
# include "Core.h"
# include "XmppChallengeFactory.h"
# include "core/XmppChallenge.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(xmpp)

ChallengeFactory::ChallengeFactory()
{
    register_object(cor::Challenge::FacObj);
}

ChallengeFactory::~ChallengeFactory()
{
    PASS;
}

bool ChallengeFactory::process(const xmlnode_t * node)
{
    if (node->name != "challenge")
        return false;
        
    return super::process(node);
}

WSI_END_NS
WSI_END_CXX