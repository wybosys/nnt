
# include "Core.h"
# include "XimShow.h"
# include "../XmppIMClient.h"

XMPPIM_BEGIN

Show::Show()
: type(PT_NULL)
{
    
}

bool Show::couldload(xmlnode_t const* node)
{
    return node->name == "show";
}

bool Show::load(xmlnode_t const* node)
{
    type = PresenceTypeFromString(node->value);
    str_type = node->value;
    return super::load(node);
}

void Show::process(Client& cli)
{
    eventobj_t evt;
    evt.data = this;
    cli.emit(kSignalShowChanged, evt);
}

bool Show::save(core::data &da) const
{
    return false;
}

XMPPIM_END
