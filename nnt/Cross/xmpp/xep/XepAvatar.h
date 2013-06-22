
# ifndef __NNT_XMPP_XEP_AVATAR_F715554626304E748F884240B3EEDFA4_H_INCLUDED
# define __NNT_XMPP_XEP_AVATAR_F715554626304E748F884240B3EEDFA4_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class UserAvatar
: public ObjectImpl<UserAvatar>
{
    typedef ObjectImpl<UserAvatar> super;
    
public:
    
    UserAvatar();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
    //! idr of photo from XPhoto.
    core::string idr;
    
};

class IQAvatar
: public ObjectImpl<IQAvatar>
{
    typedef ObjectImpl<IQAvatar> super;
    
public:
    
    IQAvatar();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
};

XMPPXEP_HEADER_END

# endif
