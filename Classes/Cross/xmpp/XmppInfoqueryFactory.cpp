
# include "Core.h"
# include "XmppInfoqueryFactory.h"

# include "core/XmppBind.h"
# include "core/XmppSession.h"

# include "im/XimRoster.h"

# include "xep/XepPing.h"
# include "xep/XepVCard.h"
# include "xep/XepServiceDiscovery.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(xmpp)

InfoqueryFactory::InfoqueryFactory()
{
    //! register core.
    register_object(cor::Bind::FacObj);
    register_object(cor::Session::FacObj);
    
    //! register im.
    register_object(im::RosterQuery::FacObj);
    
    //! register xep.
    register_object(xep::Ping::FacObj);
    register_object(xep::VCard::FacObj);
    register_object(xep::VCardV4::FacObj);
    register_object(xep::DiscoInfo::FacObj);
    register_object(xep::DiscoItem::FacObj);
}

InfoqueryFactory::~InfoqueryFactory()
{
    
}

bool InfoqueryFactory::process(xmlnode_t const* node)
{
    if (node->name != "iq")
        return false;
    
    xmlattr_t const* attr_idr = node->attribute("id");
    xmlattr_t const* attr_type = node->attribute("type");
    
    if (!(attr_idr &&
          attr_type))
    {
        trace_msg("lost id parameter of IQ.");
        return false;
    }
    
    xmlattr_t const* attr_from = node->attribute("from");
    xmlattr_t const* attr_to = node->attribute("to");
    
    from = attr_from ? attr_from->value : "";
    to = attr_to ? attr_to->value : "";
    idr = attr_idr->value;
    
    if (attr_type->value == "get")
    {
        type = cor::IQ_GET;
    }
    else if (attr_type->value == "set")
    {
        type = cor::IQ_SET;
    }
    else if (attr_type->value == "result")
    {
        type = cor::IQ_RESULT;
    }
    else if (attr_type->value == "error")
    {
        type = cor::IQ_ERROR;
    }
    else
    {
        type = cor::IQ_UNKNOWN;
    }
    
    return super::process(node);
}

WSI_END_NS
WSI_END_CXX