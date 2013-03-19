
# include "Core.h"
# include "XmppMessageFactory.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(xmpp)

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

WSI_END_NS
WSI_END_CXX