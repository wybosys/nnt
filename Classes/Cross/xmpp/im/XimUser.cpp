
# include "Core.h"
# include "XimUser.h"

XMPPIM_BEGIN

User::User()
{
    PASS;
}

User::~User()
{
    core::clear_destroy(groups);
}

XMPPIM_END