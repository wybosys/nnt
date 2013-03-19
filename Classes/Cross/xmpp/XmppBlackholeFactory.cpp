
# include "Core.h"
# include "XmppBlackholeFactory.h"

XMPP_BEGIN

BlackholeFactory::BlackholeFactory()
{
    PASS;
}

BlackholeFactory::~BlackholeFactory()
{
    PASS;
}

bool BlackholeFactory::process(xmlnode_t const* node)
{
    trace_msg("unhandled message [" + node->name + "] from server.");
    return true;
}

XMPP_END
