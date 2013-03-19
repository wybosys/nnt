
# ifndef __WSI_XMPP_IM_MESSAGE_848D6A86C795489F906C042538CCDE71_H_INCLUDED
# define __WSI_XMPP_IM_MESSAGE_848D6A86C795489F906C042538CCDE71_H_INCLUDED

# include "XimIM.h"

XMPPIM_HEADER_BEGIN

WSICLASS(Message);

class Message
: public ObjectImpl<Message>
{
    typedef ObjectImpl<Message> super;
    
public:
    
    Message();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;    
    virtual void process(Client&);
    virtual void update(Client const&);
    
    //! content of message.
    core::string content;
    
};

XMPPIM_HEADER_END

# endif