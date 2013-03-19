
# include "Core.h"
# include "XimXPhoto.h"
# include "../XmppIMClient.h"
# include "../../../Security/BaseN+NNT.h"

XMPPIM_BEGIN

XPhoto::XPhoto()
{
    
}

bool XPhoto::couldload(xmlnode_t const* node)
{
    return
    node->name == "x" &&
    node->ns == "vcard-temp:x:update" &&
    node->node("photo");
}

bool XPhoto::load(xmlnode_t const* node)
{
    xmlnode_t const* found = node->node("photo");
    value = found->value;    
    return super::load(node);
}

void XPhoto::process(Client& cli)
{
    eventobj_t evt;
    evt.data = this;
    cli.emit(kSignalXPhoto, evt);
}

XMPPIM_END
