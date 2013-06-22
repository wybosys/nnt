
# ifndef __NNT_XMPP_XEP_SIFILE_FC8E664C0FA84C9CAD8A6E9B0E2155AE_H_INCLUDED
# define __NNT_XMPP_XEP_SIFILE_FC8E664C0FA84C9CAD8A6E9B0E2155AE_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class SiFile
: public ObjectImpl<SiFile>
{
    typedef ObjectImpl<SiFile> super;
    
public:
    
    SiFile();
    ~SiFile();
    
    static bool couldload(xmlnode_t const*);
    virtual bool save(core::data&) const;

public:


    
};

XMPPXEP_HEADER_END

# endif
