
# ifndef __NNT_XMPP_XEP_OFFLINEMESSAGE_1DC235EFDDCE41A99DC874645457AF16_H_INCLUDED
# define __NNT_XMPP_XEP_OFFLINEMESSAGE_1DC235EFDDCE41A99DC874645457AF16_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class OfflineMessage
: public ObjectImpl<OfflineMessage>
{
    typedef ObjectImpl<OfflineMessage> super;
    
public:
    
    OfflineMessage();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    virtual void update(Client const&);
  
    cor::Jid from;
};

XMPPXEP_HEADER_END

# endif
