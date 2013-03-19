
# ifndef __WSI_XMPP_IM_XPHOTO_676206ABD89641A7B7ABC38ECF942419_H_INCLUDED
# define __WSI_XMPP_IM_XPHOTO_676206ABD89641A7B7ABC38ECF942419_H_INCLUDED

# include "XimIm.h"

XMPPIM_HEADER_BEGIN

class XPhoto
: public ObjectImpl<XPhoto>
{
    typedef ObjectImpl<XPhoto> super;
    
public:
    
    XPhoto();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual void process(Client&);
    
    core::string value;
    
};

XMPPIM_HEADER_END

# endif
