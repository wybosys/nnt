
# include "Core.h"
# include "XimActive.h"

XMPPIM_BEGIN

Active::Active()
{
    
}

bool Active::couldload(xmlnode_t const* node)
{
    return
    node->name == "active";
}

bool Active::load(xmlnode_t const* node)
{
    return super::load(node);
}

void Active::process(Client&)
{
    
}

bool Active::save(core::data &) const
{
    return false;
}

XMPPIM_END
