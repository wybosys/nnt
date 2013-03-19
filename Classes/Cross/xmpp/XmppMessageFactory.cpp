
# include "Core.h"
# include "XmppMessageFactory.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(xmpp)

MessageFactory::MessageFactory()
{
    
}

MessageFactory::~MessageFactory()
{
    
}

bool MessageFactory::process(xmlnode_t const* node)
{
    if (node->name != "message")
        return false;
    
    return super::process(node);
}

NNT_END_NS
NNT_END_CXX