
# ifndef __WSI_XMPP_CORE_SUCCESS_46F4026B9211468CAC9C99B2888FAF08_H_INCLUDED
# define __WSI_XMPP_CORE_SUCCESS_46F4026B9211468CAC9C99B2888FAF08_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Success
: public ObjectImpl<Success>
{
    
public:
    
    Success();
    ~Success();
    
public:
    
    static bool couldload(xmlnode_t const*);    
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;   
    
};

XMPPCORE_HEADER_END

# endif