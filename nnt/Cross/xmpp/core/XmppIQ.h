
# ifndef __NNT_XMPP_IQ_A8EABE4ACE8446898810F002BB199AEE_H_INCLUDED
# define __NNT_XMPP_IQ_A8EABE4ACE8446898810F002BB199AEE_H_INCLUDED

# include "XmppCore.h"
# include "XmppJID.h"

XMPPCORE_HEADER_BEGIN

NNTCLASS(IQ);

class IQ
: public ObjectImpl<IQ>
{
public:
    
    IQ();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool save(core::data&) const;
    virtual void update(Client const&);
    
public:
    
    //! ids.
    Jid from, to;
    
    //! identifier.
    core::string idr;
    
    //! iq type, set, get.. .
    IqType type;
    core::string str_type;
    
    //! root node.
    xmlnode_t root;
    
};

XMPPCORE_HEADER_END

# endif