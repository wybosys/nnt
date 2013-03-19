
# include "Core.h"
# include "XmppAuth.h"
# include "../../../Security/WsiSecurity.h"

XMPPCORE_BEGIN

Auth::Auth()
: mechanism(MECHANISM_UNKNOWN)
{
    
}

bool Auth::couldload(const xmlnode_t * node)
{
    if (node->name == "auth" &&
        node->ns == "http://jabber.org/features/iq-auth")
    {
        return true;
    }
    return false;
}

bool Auth::load(const xmlnode_t * node)
{
    return true;
}

void Auth::process(Client&)
{
    PASS;
}

bool Auth::save(core::data &da) const
{
    xmlnode_t node("auth");
    node.ns = "urn:ietf:params:xml:ns:xmpp-sasl";
        
    switch (mechanism)
    {
        case MECHANISM_MD5DIGEST:
        {
            node.add_attr("mechanism", "DIGEST-MD5"); 
        } break;
        default:
        case MECHANISM_PLAIN:
        {
            node.add_attr("mechanism", "PLAIN");
            
            core::data stm;
            stm.append(core::type_cast<core::data>(user + "@" + address));
            stm.append('\0');
            stm.append(core::type_cast<core::data>(user));
            stm.append('\0');
            stm.append(core::type_cast<core::data>(passwd));
            
            core::string val = core::type_cast<core::string>(base64::encode(stm));
            node.value = val;
        } break;
    }
    
    return node.save(da);
}

XMPPCORE_END