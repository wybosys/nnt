
# include "Core.h"
# include "XmppIQ.h"
# include "../XmppClient.h"

XMPPCORE_BEGIN

IQ::IQ()
{
    type = IQ_UNKNOWN;
}

bool IQ::couldload(xmlnode_t const* node)
{
    return false;
}

bool IQ::load(xmlnode_t const* node)
{
    return false;
}

void IQ::process(Client&)
{
    PASS;
}

void IQ::update(Client const& cli)
{
    if (idr.empty())
    {
        idr = "any_" + core::tostr(cli.counter_any());
    }
    
    if (from.empty())
    {
        from = cli.jid.full();
    }
}

bool IQ::save(core::data & da) const
{
    xmlnode_t& rnode = core::down_const<xmlnode_t>(root);    
    rnode.name = "iq";
    
    if (type != cor::IQ_UNKNOWN)
        rnode.ava_attribute("type")->value = cor::IqTypeToString(type);
    else if (!str_type.empty())
        rnode.ava_attribute("type")->value = str_type;
    
    if (!idr.empty())
    {
        rnode.ava_attribute("id")->value = idr;
    }
    
    if (from.empty())
    {
        if (rnode.attribute("from"))
            rnode.remove_attribute("from");
    }
    else
    {
        rnode.ava_attribute("from")->value = from.full();
    }
    
    if (to.empty())
    {
        if (rnode.attribute("to"))
            rnode.remove_attribute("to");
    }
    else
    {
        rnode.ava_attribute("to")->value = to.full();
    }
    
    return rnode.save(da);
}

XMPPCORE_END
