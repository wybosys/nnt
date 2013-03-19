
# include "Core.h"
# include "XepBitsOfBinary.h"

XMPPXEP_BEGIN

BitsOfBinary::BitsOfBinary()
{
    type = cor::IQ_GET;
}

BitsOfBinary::~BitsOfBinary()
{
    
}

bool BitsOfBinary::couldload(xmlnode_t const* node)
{
    return false;
}

bool BitsOfBinary::load(xmlnode_t const* node)
{
    super::load(node);
    return false;
}

void BitsOfBinary::process(Client& cli)
{
    if (idr.empty())
        idr = "bob_" + core::tostr(cli.counter_any());
    
    super::process(cli);
}

bool BitsOfBinary::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);
    
    xmlnode_t* node = iq.root.add_node("data");
    node->ns = "urn:xmpp:bob";
    node->add_attr(field.protocol(), field.data());
    
    return iq.save(da);
}

XMPPXEP_END
