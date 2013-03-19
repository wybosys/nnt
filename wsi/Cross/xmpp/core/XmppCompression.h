
# ifndef __XMPP_COMPRESSION_132EDF84341849C8B4571E248713C7BA_H_INCLUDED
# define __XMPP_COMPRESSION_132EDF84341849C8B4571E248713C7BA_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Compression
: public ObjectImpl<Compression>
{
public:
    
    Compression();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual void process(Client&);
    
protected:
    
    uenum _compression;
    
};

XMPPCORE_HEADER_END

# endif