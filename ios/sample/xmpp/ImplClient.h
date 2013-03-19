
# ifndef __IMPL_CLIENT_CFF7465F4E904FEAB0C042A6261F4FA7_H_INCLUDED
# define __IMPL_CLIENT_CFF7465F4E904FEAB0C042A6261F4FA7_H_INCLUDED

# include "XmppIMClientor.h"

NNTAPP_BEGIN

class Client
: public xmpp::IMClientor
{
    
    typedef xmpp::IMClientor super;
    typedef Client _class;
    
public:
    
    void set(xmpp::IMClient&);
    
    virtual xmpp::im::Group* mkgrp(xmpp::im::User const*, xmpp::im::Group*, xmpp::im::User::group const&) const;
    bool save(xmpp::im::Group*);
    
protected:
    
    void mdl_message(cxx::eventobj_t&);
    void mdl_xphoto(cxx::eventobj_t&);
    
};

NNTAPP_END

# endif
