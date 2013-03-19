
# ifndef __WSI_XMPP_XEP_BITSOFBINARY_60A16103CDFE4152B1C40B75504F44FD_H_INCLUDED
# define __WSI_XMPP_XEP_BITSOFBINARY_60A16103CDFE4152B1C40B75504F44FD_H_INCLUDED

# include "XepCore.h"
# include "XepField.h"

XMPPXEP_HEADER_BEGIN

class BitsOfBinary
: public ObjectImpl<BitsOfBinary>
{
    typedef ObjectImpl<BitsOfBinary> super;
    
public:
    
    BitsOfBinary();
    ~BitsOfBinary();
    
    static bool couldload(xmlnode_t const*);
    virtual void process(Client&);
    virtual bool load(xmlnode_t const*);
    virtual bool save(core::data&) const;
    
    Field field;
    
};

XMPPXEP_HEADER_END

# endif
