
# ifndef __NNT_XMPP_XEP_MUC_1AB661FB22BC44AA99410D2F67D2BB7C_H_INCLUDED
# define __NNT_XMPP_XEP_MUC_1AB661FB22BC44AA99410D2F67D2BB7C_H_INCLUDED

# include "XepCore.h"
# include "../im/XimPresence.h"

XMPPXEP_HEADER_BEGIN
NNT_BEGIN_NS(muc)

typedef enum
{
    UR_NONE,
    UR_MODERATOR,
    UR_PARTICIPANT,
    UR_VISITOR,
} UserRole;

typedef enum
{
    UA_NONE,
    UA_OWNER,
    UA_ADMIN,
    UA_MEMBER,
    UA_OUTCAST,
} UserAffiliation;

UserRole UserRoleFromString(core::string const&);
core::string UserRoleToString(UserRole);

UserAffiliation UserAffiliationFromString(core::string const&);
core::string UserAffiliationToString(UserAffiliation);

class Enter
: public ExtendObject<Enter, im::Presence>
{
    typedef ExtendObject<Enter, im::Presence> super;
    
public:
    
    virtual void update(Client const&);
    virtual bool save(core::data&) const;
    
    core::string idr;
    
};

class Presence
: public ExtendObject<Presence, im::Presence>
{
    typedef ExtendObject<Presence, im::Presence> super;
    
public:
        
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual void process(Client&);
    virtual void update(Client const&);
    virtual bool save(core::data&) const;
    
    core::string idr;
    
    UserRole role;
    UserAffiliation affiliation;
    cor::Jid user;
    
};

NNT_END_NS
XMPPXEP_HEADER_END

# endif
