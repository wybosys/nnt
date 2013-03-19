
# include "Core.h"
# include "XepJingle.h"

XMPPXEP_BEGIN

Jingle::Jingle()
: action(UNKNOWN)
{
    type = cor::IQ_SET;
}

Jingle::~Jingle()
{

}

# define JINGLETYPEMAP_DECL \
typedef core::initializer::add<core::twmap<int, core::string> > map_type; \
static map_type map( \
core::make_pair(CONTENT_ACCEPT,          "content-accept"), \
core::make_pair(CONTENT_ADD,             "content-add"), \
core::make_pair(CONTENT_MODIFY,          "content-modify"), \
core::make_pair(CONTENT_REJECT,          "content-reject"), \
core::make_pair(CONTENT_REMOVE,          "content-remove"), \
core::make_pair(DESCRIPTION_INFO,        "description-info"), \
core::make_pair(SECURITY_INFO,           "security-info"), \
core::make_pair(SESSION_ACCEPT,          "session-accept"), \
core::make_pair(SESSION_INFO,            "session-info"), \
core::make_pair(SESSION_INITIATE,        "session-initiate"), \
core::make_pair(SESSION_TERMINATE,       "session-terminate"), \
core::make_pair(TRANSPORT_ACCEPT,        "transport-accept"), \
core::make_pair(TRANSPORT_INFO,          "transport-info"), \
core::make_pair(TRANSPORT_REJECT,        "transport-reject"), \
core::make_pair(TRANSPORT_REPLACE,       "transport-replace") \
);

core::string Jingle::ActionTypeToString(ActionType at)
{
    JINGLETYPEMAP_DECL;
    map_type::type::left_map_type::const_iterator found = map->left_map.find(at);
    if (found == map->left_map.end())
        return "";
    return found->second;
}

Jingle::ActionType Jingle::ActionTypeFromString(core::string const& str)
{
    JINGLETYPEMAP_DECL;
    map_type::type::right_map_type::const_iterator found = map->right_map.find(str);
    if (found == map->right_map.end())
        return UNKNOWN;
    return (Jingle::ActionType)found->second;
}

bool Jingle::couldload(xmlnode_t const* node)
{
    return false;
}

bool Jingle::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);
    
    // add jingle xml node.
    xmlnode_t* node = iq.root.add_node("jingle");
    node->ns = "urn:xmpp:jingle:1";
    node->add_attr("action", ActionTypeToString(action));
    node->add_attr("sid", sid);
    
    if (initiator.empty() == false)
        node->add_attr("initiator", initiator.to_string());
    if (responder.empty() == false)
        node->add_attr("responder", responder.to_string());
    
    return iq.save(da);
}

XMPPXEP_END
