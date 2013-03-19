
# include "Core.h"
# include "XmppSuccess.h"
# include "../XmppClient.h"

XMPPCORE_BEGIN

Success::Success()
{
    
}

Success::~Success()
{
    
}

bool Success::couldload(const xmlnode_t * node)
{
    return node->name == "success";
}

bool Success::load(const xmlnode_t * node)
{
    return true;
}

bool Success::save(core::data & da) const
{
    return true;
}

NNT_EXTERN wf::State kStateAuth;

void Success::process(Client & cli)
{
    if (cli.statemachine().exist(kStateAuth))
    {
        cli.statemachine().process(kStateAuth);
    }
}

XMPPCORE_END