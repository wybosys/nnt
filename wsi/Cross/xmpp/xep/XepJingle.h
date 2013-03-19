
# ifndef __WSI_XMPP_XEP_JINGLE_DD40925938454A559AD9734127FE5A1F_H_INCLUDED
# define __WSI_XMPP_XEP_JINGLE_DD40925938454A559AD9734127FE5A1F_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class Jingle
: public ObjectImpl<Jingle>
{
    typedef ObjectImpl<Jingle> super;
    
public:
    
    typedef enum
    {
        UNKNOWN,
        CONTENT_ACCEPT,
        CONTENT_ADD,
        CONTENT_MODIFY,
        CONTENT_REJECT,
        CONTENT_REMOVE,
        DESCRIPTION_INFO,
        SECURITY_INFO,
        SESSION_ACCEPT,
        SESSION_INFO,
        SESSION_INITIATE,
        SESSION_TERMINATE,
        TRANSPORT_ACCEPT,
        TRANSPORT_INFO,
        TRANSPORT_REJECT,
        TRANSPORT_REPLACE
    } ActionType;
    
    static core::string ActionTypeToString(ActionType);
    static ActionType ActionTypeFromString(core::string const&);
    
public:
    
    Jingle();
    ~Jingle();
    
    static bool couldload(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
public:
    
    ActionType action;
    cor::Jid initiator, responder;
    core::string sid;
    
};

XMPPXEP_HEADER_END

# endif
