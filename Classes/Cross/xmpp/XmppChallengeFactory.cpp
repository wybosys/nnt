
# include "Core.h"
# include "XmppChallengeFactory.h"
# include "core/XmppChallenge.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(xmpp)

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

NNT_END_NS
NNT_END_CXX