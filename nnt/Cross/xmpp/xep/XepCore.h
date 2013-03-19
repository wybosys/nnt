
# ifndef __WSI_XMPP_XEP_CORE_A65A5FE6ACAE4003AED7BDD3A67353B6_H_INCLUDED
# define __WSI_XMPP_XEP_CORE_A65A5FE6ACAE4003AED7BDD3A67353B6_H_INCLUDED

# include "../core/XmppCore.h"
# include "../core/XmppJID.h"
# include "../XmppClient.h"
# include "../core/XmppIQ.h"

# define XMPPXEP_HEADER_BEGIN \
WSI_BEGIN_HEADER_CXX \
WSI_BEGIN_NS(xmpp) \
WSI_BEGIN_NS(xep)

# define XMPPXEP_HEADER_END \
WSI_END_NS \
WSI_END_NS \
WSI_END_HEADER_CXX

# define XMPPXEP_BEGIN \
WSI_BEGIN_CXX \
WSI_BEGIN_NS(xmpp) \
WSI_BEGIN_NS(xep)

# define XMPPXEP_END \
WSI_END_NS \
WSI_END_NS \
WSI_END_CXX

XMPPXEP_HEADER_BEGIN

using cor::IqType;

template <typename objT>
class ObjectImpl
: public cor::ObjectImpl<objT>
{
    typedef cor::ObjectImpl<objT> super;
    
public:
    
    ObjectImpl()
    : type(cor::IQ_UNKNOWN)
    {
        PASS;
    }
    
    virtual bool load(xmlnode_t const* node)
    {
        xmlnode_t const* pnode = node->parent;
        xmlattr_t const* attr = NULL;
        
        from.clear();
        to.clear();
        type = cor::IQ_UNKNOWN;
        
        if ((attr = pnode->attribute("from")))
        {
            from = attr->value;
        }
        
        if ((attr = pnode->attribute("to")))
        {
            to = attr->value;
        }
        
        if ((attr = pnode->attribute("type")))
        {
            str_type = attr->value;
            type = cor::IqTypeFromString(str_type);
        }
        
        if ((attr = pnode->attribute("id")))
        {
            idr = attr->value;
        }
        
        return true;
    }
    
    virtual void update(Client const& cli)
    {
        if (idr.empty())
        {
            idr = "any_" + core::tostr(cli.counter_any());
        }
        
        if (from.empty())
        {
            from = cli.jid.full();
        }
    }
    
    void to_iq(cor::IQ& iq) const
    {
        iq.type = type;
        iq.from = from;
        iq.to = to;
        iq.idr = idr;
    }
    
    cor::IQ to_iq() const
    {
        cor::IQ iq;
        to_iq(iq);
        return iq;
    }
    
    void set_type(core::string const& str)
    {
        type = cor::IQ_UNKNOWN;
        str_type = str;
    }
    
    core::string type_string() const
    {
        if (type != cor::IQ_UNKNOWN)
            return cor::IqTypeToString(type);
        return str_type;
    }
    
    //! type.
    IqType type;
    core::string str_type;
    
    //! user.
    cor::Jid from, to;
    
    //! id.
    core::string idr;
    
};

XMPPXEP_HEADER_END

# endif