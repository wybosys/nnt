
# ifndef __WSI_XMPP_CORE_CLOSE_1DB0FC7A4FCE489D9C54BA74E673BA61_H_INCLUDED
# define __WSI_XMPP_CORE_CLOSE_1DB0FC7A4FCE489D9C54BA74E673BA61_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Close
: public ObjectImpl<Close>
{
    typedef ObjectImpl<Close> super;
    
public:
    
    Close();
    
    virtual void process(Client&);
    virtual bool save(core::data&) const;

};

XMPPCORE_HEADER_END

# endif
