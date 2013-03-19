
# include "Core.h"
# include "XmppSasl.h"
# include "../XmppClient.h"

XMPPCORE_BEGIN

Sasl::Sasl()
: _mechanism(MECHANISM_UNKNOWN)
{
    
}

bool Sasl::couldload(const xmlnode_t * node)
{
    if (node->name == "mechanisms" &&
        node->ns == "urn:ietf:params:xml:ns:xmpp-sasl")
    {
        return true;        
    }
    return false;
}

bool Sasl::load(const xmlnode_t * node)
{
    for (xmlnode_t const* each = node->first;
         each;
         each = each->next)
    {
        if (each->value == "PLAIN")
            MASK_SET(MECHANISM_PLAIN, _mechanism)
        else if (each->value == "DIGEST-MD5")
            MASK_SET(MECHANISM_MD5DIGEST, _mechanism)
        else if (each->value == "CRAM-MD5")
            MASK_SET(MECHANISM_MD5CRAM, _mechanism)
        else if (each->value == "ANONYMOUS")
            MASK_SET(MECHANISM_ANONYMOUS, _mechanism);
    }
    return true;
}

void Sasl::process(Client& cli)
{
    if (cli.setting.mechanism == MECHANISM_UNKNOWN)
    {
        if (MASK_CHECK(MECHANISM_MD5DIGEST, _mechanism))
            cli.setting.mechanism = MECHANISM_MD5DIGEST;
        else if (MASK_CHECK(MECHANISM_PLAIN, _mechanism))
            cli.setting.mechanism = MECHANISM_PLAIN;
    }
}

XMPPCORE_END
