
# ifndef __NNT_XMPP_XEP_SIPUB_4847C56727F14E8E840AEB8345BE8D63_H_INCLUDED
# define __NNT_XMPP_XEP_SIPUB_4847C56727F14E8E840AEB8345BE8D63_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class SiPub
: public ObjectImpl<SiPub>
{
    typedef ObjectImpl<SiPub> super;
    
public:
    
    class File
    {
    public:
        
        core::string name;
        uint size;
        
    };
    
public:
    
    SiPub();
    ~SiPub();
    
    virtual bool append(xmlnode_t*) const;
    
    core::string mimetype;
    core::string profile;
    core::used<File> file;
    
};

XMPPXEP_HEADER_END

# endif
