
# ifndef __NNT_XMPP_IM_E099753114514716A23E6EF2C691696E_H_INCLUDED
# define __NNT_XMPP_IM_E099753114514716A23E6EF2C691696E_H_INCLUDED

# include "../core/XmppCore.h"
# include "../core/XmppJID.h"

# define XMPPIM_HEADER_BEGIN \
NNT_BEGIN_HEADER_CXX \
NNT_BEGIN_NS(xmpp) \
NNT_BEGIN_NS(im)

# define XMPPIM_HEADER_END \
NNT_END_NS \
NNT_END_NS \
NNT_END_HEADER_CXX

# define XMPPIM_BEGIN \
NNT_BEGIN_CXX \
NNT_BEGIN_NS(xmpp) \
NNT_BEGIN_NS(im)

# define XMPPIM_END \
NNT_END_NS \
NNT_END_NS \
NNT_END_CXX

XMPPIM_HEADER_BEGIN

typedef enum
{
    PT_OFFLINE = -1, // offline.
    PT_NULL = 0,
    PT_ONLINE = PT_NULL, // online.
    PT_AWAY,// away.
    PT_CHAT,// chating.
    PT_DND, // Do Not Disturb.
    PT_XA,  // eXtended Away.
} 
PresenceType;

NNTAPI(PresenceType) PresenceTypeFromString(core::string const&);
NNTAPI(core::string) PresenceTypeToString(PresenceType);

typedef enum
{
    MT_NULL,
    MT_CHAT,
    MT_ERROR,
    MT_GROUPCHAT,
    MT_HEADLINE,
    MT_NORMAL,
} 
MessageType;

NNTAPI(MessageType) MessageTypeFromString(core::string const&);
NNTAPI(core::string) MessageTypeToString(MessageType);

template <typename objT>
class ObjectImpl
: public cor::ObjectImpl<objT>
{
    typedef cor::ObjectImpl<objT> super;
    
public:
    
    ObjectImpl()
    : type(MT_NULL)
    {
        PASS;
    }
    
    virtual bool load(xmlnode_t const* node)
    {
        xmlnode_t const* pnode = node->parent;
        xmlattr_t const* attr = NULL;
        
        from.clear();
        to.clear();
        type = MT_NULL;
        
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
            type = MessageTypeFromString(attr->value);
        }
        
        return true;
    }
    
    //! type.
    MessageType type;
    
    //! user.
    cor::Jid from, to;
};

XMPPIM_HEADER_END

# endif