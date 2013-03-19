
# ifndef __WSI_XMPP_IM_PRIORITY_338D40733EBF4791A7BC2FDE6CF439FD_H_INCLUDED
# define __WSI_XMPP_IM_PRIORITY_338D40733EBF4791A7BC2FDE6CF439FD_H_INCLUDED

# include "XimIM.h"

XMPPIM_HEADER_BEGIN

class Priority
: public ObjectImpl<Priority>
{
    typedef ObjectImpl<Priority> super;
    
public:
    
    Priority();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    virtual void process(Client&);
    
    int priority;
    
};

XMPPIM_HEADER_END

# endif
