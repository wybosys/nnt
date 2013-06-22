
# ifndef __NNT_XMPP_XEP_VCARD_199C3FA2E19749FF8DD2DCDAF0096F17_H_INCLUDED
# define __NNT_XMPP_XEP_VCARD_199C3FA2E19749FF8DD2DCDAF0096F17_H_INCLUDED

# include "../../VCard+NNT.h"
# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

NNTCLASS(VCard);

class VCard
: public ObjectImpl<VCard>
{
    typedef ObjectImpl<VCard> super;
    
public:
    
    VCard();
    ~VCard();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
    cross::VCard* vcard;
};

NNTCLASS(VCardUpdate);

class VCardUpdate
: public ExtendObject<VCardUpdate, VCard>
{
public:
    
    VCardUpdate();
    
    virtual bool save(core::data&) const;
    void set(cross::VCard*);
    
};

NNTCLASS(VCardV4);

class VCardV4
: public ObjectImpl<VCardV4>
{
    typedef ObjectImpl<VCardV4> super;
    
public:
    
    VCardV4();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
};

XMPPXEP_HEADER_END

# endif