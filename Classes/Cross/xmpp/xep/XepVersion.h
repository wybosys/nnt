
# ifndef __WSI_XMPP_XEP_VERSION_764DA1AE4DC2469BA8D2DEE63105E838_H_INCLUDED
# define __WSI_XMPP_XEP_VERSION_764DA1AE4DC2469BA8D2DEE63105E838_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

WSICLASS(Version);

class Version
: public ObjectImpl<Version>
{
    
    typedef ObjectImpl<Version> super;
    
public:
    
    Version();
    
    static bool couldload(xmlnode_t const*);    
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const; 
    
    core::string name, version;
    
};

XMPPXEP_HEADER_END

# endif