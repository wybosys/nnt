
# include "Core.h"
# include "XmppChallenge.h"
# include "../XmppClient.h"
# include "../../../Security/WsiSecurity.h"
# include "XmppResponse.h"
# include "../../../Parser/XmlParserUtil.h"

XMPPCORE_BEGIN

Challenge::Challenge()
{
    
}

bool Challenge::couldload(xmlnode_t const* node)
{
    return node->name == "challenge" &&
    node->ns == "urn:ietf:params:xml:ns:xmpp-sasl";
}

bool Challenge::load(xmlnode_t const* node)
{
    core::string str = node->value;
    str = core::type_cast<core::string>(
                                        base64::decode(
                                                       core::type_cast<core::data>(str)
                                                       )
                                        );
    realm = parser::XmlAttributeUtil::AttributeFind("realm", str);
    nonce = parser::XmlAttributeUtil::AttributeFind("nonce", str);
    qop = parser::XmlAttributeUtil::AttributeFind("qop", str);
    return true;
}

void Challenge::process(Client& client)
{
    core::string str_respn;
    core::string str_cnonce = nonce::simple();
    core::string str_nc = core::tostr(client.counter_challenge());
    core::string str_user = client.setting.user;
    core::string str_passwd = client.setting.passwd;
    core::string str_addr = client.setting.address.address;
    core::string str_uri = "xmpp/" + str_addr;
        
    // calc ha1.
    core::string ha1 = str_user + ":" + realm + ":" + str_passwd;
    ha1 = md5::digest(core::type_cast<core::data>(ha1));
    ha1 = ha1 + ":" + nonce + ":" + str_cnonce;
    ha1 = md5::digest(core::type_cast<core::data>(ha1));
    
    // calc ha2.
    core::string ha2 = "AUTHENTICATE:" + str_uri;
    ha2 = md5::digest(core::type_cast<core::data>(ha2));
    
    // calc response value.
    core::string val_respn = ha1 + ":" + nonce + ":" + str_nc + ":" + str_cnonce + ":" + qop + ":" + ha2;
    val_respn = md5::digest(core::type_cast<core::data>(val_respn));
    
    str_respn += parser::XmlAttributeUtil::AttributeMake("username", str_user, true) + ",";
    str_respn += parser::XmlAttributeUtil::AttributeMake("realm", realm, true) + ",";
    str_respn += parser::XmlAttributeUtil::AttributeMake("nonce", nonce, true) + ",";
    str_respn += parser::XmlAttributeUtil::AttributeMake("cnonce", str_cnonce, true) + ",";
    str_respn += parser::XmlAttributeUtil::AttributeMake("nc", str_nc) + ",";
    str_respn += parser::XmlAttributeUtil::AttributeMake("qop", qop) + ",";
    str_respn += parser::XmlAttributeUtil::AttributeMake("response", val_respn) + ",";
    str_respn += parser::XmlAttributeUtil::AttributeMake("charset", "utf-8");
    
    str_respn = core::type_cast<core::string>(base64::encode(core::type_cast<core::data>(str_respn)));
    
    str_respn = "<response xmlns='urn:ietf:params:xml:ns:xmpp-sasl'>" + str_respn + "</response>";
    //Response respn;
    //respn.str = str_respn;
    //client.execute(respn);
    
    StringObject obj;
    obj.str = str_respn;
    client.execute(obj);
}

XMPPCORE_END
