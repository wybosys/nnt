
# include "Core.h"
# include "XmppPubsub.h"

XMPPCORE_BEGIN

Pubsub::Pubsub()
{
    root = super::root.add_node("pubsub");
    root->ns = "http://jabber.org/protocol/pubsub";
}

XMPPCORE_END
