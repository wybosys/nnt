
# ifndef __NNT_XMPP_IMCLIENTOR_4F46F0D6B9F64A56ACD5C7134910CA82_H_INCLUDED
# define __NNT_XMPP_IMCLIENTOR_4F46F0D6B9F64A56ACD5C7134910CA82_H_INCLUDED

# include "XmppIMClient.h"
# include "XmppClientor.h"
# include "im/XimContact.h"
# include "im/XimUser.h"

XMPP_HEADER_BEGIN

NNTDECL_PRIVATE_HEAD_CXX(IMClientor);

class IIMClientor
{
public:
    
    virtual ~IIMClientor() {}
    
    //! create group from users.
    virtual im::Group* mkgrp(im::User const*, im::Group*, im::User::group const&) const = 0;
    
    //! save.
    virtual bool save(im::Group*) = 0;
    
};

NNTCLASS(IMClientor);

class IMClientor
: public Clientor,
public IIMClientor
{
    NNTDECL_PRIVATE_CXX(IMClientor);
    
public:
    
    IMClientor();
    IMClientor(IMClient&);
    ~IMClientor();
    
public:
    
    void set(IMClient&);
    
    //! type cast.
    IMClient const* operator -> () const;
    IMClient* operator -> ();
    operator IMClient  const& () const;
    operator IMClient& ();
    IMClient const& client() const;
    IMClient& client();
    
};

XMPP_HEADER_END

# endif
