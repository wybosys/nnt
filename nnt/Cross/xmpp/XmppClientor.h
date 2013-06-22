
# ifndef __NNT_XMPP_CLIENTOR_8AD4517A9FF64AB1AE78AFF1E51CBAF5_H_INCLUDED
# define __NNT_XMPP_CLIENTOR_8AD4517A9FF64AB1AE78AFF1E51CBAF5_H_INCLUDED

# include "XmppClient.h"

XMPP_HEADER_BEGIN

NNTDECL_PRIVATE_HEAD_CXX(Clientor);

class Clientor
: public cxx::Object<>
{
    
    NNTDECL_PRIVATE_CXX(Clientor);
    
public:
    
    Clientor();
    Clientor(Client&);
    ~Clientor();
    
public:
    
    void set(Client&);
    
    //! type cast.
    Client const* operator -> () const;
    Client* operator -> ();
    operator Client  const& () const;
    operator Client& ();
    Client const& client() const;
    Client& client();
    
protected:
    
    Client* _client;
    
};

XMPP_HEADER_END

# endif
