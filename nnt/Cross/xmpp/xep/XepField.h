
# ifndef __NNT_XMPP_XEP_FIELD_B0CF3CB7CE334BECA1CE01521F037FA7_H_INCLUDED
# define __NNT_XMPP_XEP_FIELD_B0CF3CB7CE334BECA1CE01521F037FA7_H_INCLUDED

# include "XepCore.h"

XMPPXEP_HEADER_BEGIN

class Field
: public RefObject
{
public:
    
    Field();
    Field(core::string const&);
    virtual ~Field();
    
    void set(core::string const&);
    core::string to_string() const;
    bool operator == (Field const& r) const;
    
    typedef core::vector<core::string> path_type;
    path_type path;
    
    operator core::string () const;
    Field& operator = (core::string const&);
    
    core::string protocol() const;
    core::string data() const;
    
};

inline_impl Field::operator core::string() const
{
    return to_string();
}

inline_impl Field& Field::operator = (core::string const& str)
{
    set(str);
    return *this;
}

XMPPXEP_HEADER_END

# endif
