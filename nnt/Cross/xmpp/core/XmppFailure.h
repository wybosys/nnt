
# ifndef __WSI_XMPP_CORE_FAILURE_3BC574FC4980404E90480339703B2699_H_INCLUDED
# define __WSI_XMPP_CORE_FAILURE_3BC574FC4980404E90480339703B2699_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Failure
: public ObjectImpl<Failure>
{    
public:
    
    Failure();
    ~Failure();
    
public:
    
    static bool couldload(xmlnode_t const*);    
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;   
    
    //! ec.
    ErrorCode err;
    
};

XMPPCORE_HEADER_END

# endif