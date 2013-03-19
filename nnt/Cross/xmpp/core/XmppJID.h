
# ifndef __WSI_XMPP_CORE_JID_E276ED7C3E4648048336DA5974EA83CB_H_INCLUDED
# define __WSI_XMPP_CORE_JID_E276ED7C3E4648048336DA5974EA83CB_H_INCLUDED

# include "XmppCore.h"

XMPPCORE_HEADER_BEGIN

WSICLASS(Jid);

class Jid
{
public:
    
    Jid();
    Jid(core::string const&);
    
    //! set.
    Jid& operator = (core::string const&);
    
    //! is sample user.
    bool is_sameuser(Jid const& r) const;
    
    //! set str.
    void set(core::string const&);
    
    //! empty.
    bool empty() const;
    
    //! clear all.
    void clear();
    
    //! to str.
    core::string full() const;
    
    //! url.
    core::string bare() const;

    //! domain.
    core::string domain() const;
    
    core::string username;
    core::string address;
    core::string resource;
    
    // comp.
    core::string to_string() const;
    core::string to_address() const;
    
};

inline_impl core::string Jid::to_string() const
{
    return full();
}

inline_impl core::string Jid::to_address() const
{
    return bare();
}

inline_impl bool operator == (Jid const& l, Jid const& r)
{
    return 
    l.username == r.username &&
    l.address == r.address &&
    l.resource == r.resource;
}

inline_impl Jid& Jid::operator = (core::string const& str)
{
    set(str);
    return *this;
}

XMPPCORE_HEADER_END

# endif