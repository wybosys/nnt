
# ifndef __XMPP_STREAM_79DD1E9A8C044D178138FF9323F2B46A_H_INCLUDED
# define __XMPP_STREAM_79DD1E9A8C044D178138FF9323F2B46A_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Stream
: public ObjectImpl<Stream>
{    
public:
    
    Stream();
    ~Stream();
    
public:
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;    
    
public:
    
    core::string to;    
    core::string from;
    core::string idr;
    
};

XMPPCORE_HEADER_END

# endif