
# include "Core.h"
# include "XmppFailure.h"
# include "../XmppClient.h"

XMPPCORE_BEGIN

Failure::Failure()
{
    
}

Failure::~Failure()
{
    
}

bool Failure::couldload(const xmlnode_t * node)
{
    return
    node->name == "failure" &&
    node->ns == "urn:ietf:params:xml:ns:xmpp-sasl";
}

bool Failure::load(xmlnode_t const* node)
{
    err = ERR_UNKNOWN;
    
    for (xmlnode_t::nodes_type::const_iterator each = node->children.begin();
         each != node->children.end();
         ++each)
    {
        err |= ErrorCodeFromString(each->second->name);
    }
    
    return true;
}

bool Failure::save(core::data & da) const
{
    return true;
}

void Failure::process(Client & cli)
{
    eventobj_t evt;
    evt.data = this;
    cli.emit(kSignalFailure, evt);

# ifdef WSI_DEBUG
	trace_msg("failed at user: " + cli.setting.user + " . ");
# endif
}

XMPPCORE_END