
# ifndef __NNT_XMPP_XEP_SERVICEDISCOVERY_C880F88D80874D359E7DC4E51C4B579D_H_INCLUDED
# define __NNT_XMPP_XEP_SERVICEDISCOVERY_C880F88D80874D359E7DC4E51C4B579D_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class ServiceIdentity
{
public:
    core::string category, name, type;
};

class ServiceFeature
{
public:
    
    ServiceFeature()
    {
        PASS;
    }
    
    ServiceFeature(core::string const& v)
    : var(v)
    {
        PASS;
    }
    
    bool operator == (ServiceFeature const& r) const;
    
    core::string var;
};

inline_impl bool ServiceFeature::operator == (ServiceFeature const& r) const
{
    return var == r.var;
}

class DiscoInfo
: public ObjectImpl<DiscoInfo>
{
    typedef ObjectImpl<DiscoInfo> super;
    
public:
    
    DiscoInfo();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    virtual void update(Client const&);
    
    typedef core::list<ServiceIdentity> identities_type;
    typedef core::list<ServiceFeature> features_type;
    identities_type identities;
    features_type features;
};

class ServiceItem
{
public:
    
    cor::Jid jid;
    core::string name;
};

class DiscoItem
: public ObjectImpl<DiscoItem>
{
    typedef ObjectImpl<DiscoItem> super;
    
public:
    
    DiscoItem();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    virtual void update(Client const&);
    
    typedef core::list<ServiceItem> items_type;
    items_type items;
    
};

XMPPXEP_HEADER_END

# endif
