
# include "Core.h"
# include "XepSubject.h"
# include "../XmppIMClient.h"

XMPPXEP_BEGIN

bool Subject::couldload(xmlnode_t const* node)
{
    return
    node->name == "subject";
}

bool Subject::load(xmlnode_t const* node)
{
    value = node->value;
    return super::load(node);
}

void Subject::process(Client& cli)
{
    cli.emit(kSignalMUCSubject, cxx::eventobj_t::Data(this));
}

bool Subject::save(core::data &da) const
{
    return false;
}

XMPPXEP_END
