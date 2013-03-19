
# include "Core.h"
# include "XimComposing.h"

XMPPIM_BEGIN

Composing::Composing()
{
    
}

bool Composing::couldload(xmlnode_t const* node)
{
    return 
    node->name == "composing" &&
    node->ns == "http://jabber.org/protocol/chatstates";
}

bool Composing::load(xmlnode_t const* node)
{
    return super::load(node);
}

void Composing::process(Client&)
{
    
}

bool Composing::save(core::data &) const
{
    return false;
}

XMPPIM_END