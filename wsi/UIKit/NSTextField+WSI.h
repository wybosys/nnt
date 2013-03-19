
# ifndef __WSINS_TEXTFIELD_BD94C50603C64535857268CD1A1A8B87_H_INCLUDED
# define __WSINS_TEXTFIELD_BD94C50603C64535857268CD1A1A8B87_H_INCLUDED

# include "NSControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSINSTextField : NSTextField

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "NSControl+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

class TextField
: public Control < TextField, WSINSTextField >
{
    typedef Control < TextField, WSINSTextField > super;
    
public:
    
    TextField()
    {
        PASS;
    }
    
    void init()
    {
        this->_self = [[objc_type alloc] initWithZero];
    }
    
    inline ns::String get_text() const
    {
        return super::string_value();
    }
    
    inline void set_text(ns::String const& str)
    {
        super::set_value(str);
    }
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif