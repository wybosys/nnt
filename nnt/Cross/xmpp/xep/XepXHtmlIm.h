
# ifndef __NNT_XMPP_XEP_XHTMLIM_861A9FC81A2149A08A2815014CA77535_H_INCLUDED
# define __NNT_XMPP_XEP_XHTMLIM_861A9FC81A2149A08A2815014CA77535_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

NNTCLASS(HtmlMessage);

class HtmlMessage
: public ObjectImpl<HtmlMessage>
{
    typedef ObjectImpl<HtmlMessage> super;
    
public:
    
    HtmlMessage();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
      
    core::string body;
    xmlnode_t data;
    
    virtual bool getdata(core::data&, xmlnode_t const&) const;
    core::string getdata() const;
    
    virtual void process_filter(xmlnode_t*, Client&);
    
};

XMPPXEP_HEADER_END

# endif
