
# include "Core.h"
# include "XmppSuccessFactory.h"

# include "./core/XmppSuccess.h"
# include "./core/XmppFailure.h"

XMPP_BEGIN

SuccessFactory::SuccessFactory()
{
    register_object(cor::Success::FacObj);
    register_object(cor::Failure::FacObj);
}

SuccessFactory::~SuccessFactory()
{
    PASS;
}

bool SuccessFactory::process(xmlnode_t const* node)
{
    if (node->name == "success")
    {
        return super::process_object(cor::Success::FacObj, node);
    }
    else if (node->name == "failure")
    {
        return super::process_object(cor::Failure::FacObj, node);
    }
    
    return false;    
}

XMPP_END
