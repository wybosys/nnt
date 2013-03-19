
# include "Core.h"
# include "XmppClose.h"

XMPPCORE_BEGIN

Close::Close()
{
    
}

void Close::process(Client&)
{
    PASS;
}

bool Close::save(core::data &da) const
{
    da = core::type_cast<core::data>("</stream:stream>");
    return true;
}

XMPPCORE_END
