
# ifndef __WSI_XMPP_IM_USER_12E9FDFBD3C14432ABC15116CEA46E59_H_INCLUDED
# define __WSI_XMPP_IM_USER_12E9FDFBD3C14432ABC15116CEA46E59_H_INCLUDED

# include "XimIM.h"
# include "../core/XmppJID.h"

XMPPIM_HEADER_BEGIN

WSICLASS(User);

class User
: public RefObject
{
public:
    
    class group
    {
    public:
        core::string name;
    };
    
    typedef core::list<group*> groups_type;
    
    User();
    virtual ~User();
    
    //! name.
    core::string name;
    
    //! jid of user.
    cor::Jid jid;
    
    //! group.
    groups_type groups;
    
};

XMPPIM_HEADER_END

# endif