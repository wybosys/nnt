
# include "Core.h"
# include "XmppPresenceFactory.h"
# include "XmppIMClient.h"
# include "im/XimPresence.h"

XMPP_BEGIN

PresenceFactory::PresenceFactory()
{

}

PresenceFactory::~PresenceFactory()
{
    PASS;    
}

bool PresenceFactory::process(xmlnode_t const* node)
{
    if (node->name != "presence")
        return false;
    
    // emit signal.
    im::Presence obj;
    obj.load_node(node);
    this->_client->emit(kSignalGotPresence, eventobj_t::Data(&obj));
    
    // process children.
    super::process(node);
    
    // always true.
    return true;
}

XMPP_END
