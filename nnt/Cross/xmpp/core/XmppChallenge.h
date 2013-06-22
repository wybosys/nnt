
# ifndef __XMPP_CHALLENGE_AC8CC687E47E4310845C3329036CF027_H_INCLUDED
# define __XMPP_CHALLENGE_AC8CC687E47E4310845C3329036CF027_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

class Challenge
: public ObjectImpl<Challenge>
{
public:
    
    Challenge();
    
    static bool couldload(xmlnode_t const*);
    virtual bool load(xmlnode_t const*);
    virtual void process(Client&);
  
public:
    
    core::string realm, nonce, qop;
    
};

XMPPCORE_HEADER_END

# endif