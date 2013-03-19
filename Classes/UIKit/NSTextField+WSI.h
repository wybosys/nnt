
# ifndef __NNTNS_TEXTFIELD_BD94C50603C64535857268CD1A1A8B87_H_INCLUDED
# define __NNTNS_TEXTFIELD_BD94C50603C64535857268CD1A1A8B87_H_INCLUDED

# include "NSControl+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTNSTextField : NSTextField

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NSControl+NNT.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

class TextField
: public Control < TextField, NNTNSTextField >
{
    typedef Control < TextField, NNTNSTextField > super;
    
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

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif