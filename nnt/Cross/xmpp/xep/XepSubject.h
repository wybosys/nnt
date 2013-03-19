
# ifndef __NNT_XMPP_XEP_SUBJECT_6FCBD19EBAFD43058B99D49490E0C580_H_INCLUDED
# define __NNT_XMPP_XEP_SUBJECT_6FCBD19EBAFD43058B99D49490E0C580_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class Subject
: public ObjectImpl<Subject>
{
    typedef ObjectImpl<Subject> super;
    
public:
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
    core::string value;
    
};

XMPPXEP_HEADER_END

# endif
