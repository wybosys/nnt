
# include "Core.h"
# include "XimPriority.h"
# include "../XmppIMClient.h"

XMPPIM_BEGIN

Priority::Priority()
: priority(0)
{
    
}

bool Priority::couldload(xmlnode_t const* node)
{
    return node->name == "priority";
}

bool Priority::load(xmlnode_t const* node)
{
    priority = core::toint(node->value);
    return super::load(node);
}

void Priority::process(Client& cli)
{
    PASS;
}

bool Priority::save(core::data &da) const
{
    return false;
}

XMPPIM_END
