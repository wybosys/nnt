
# ifndef __WSINS_TEXTVIEW_F6E2A58E55DC4BBF97C7CEBDF553E07D_H_INCLUDED
# define __WSINS_TEXTVIEW_F6E2A58E55DC4BBF97C7CEBDF553E07D_H_INCLUDED

# include "NSControl+WSI.h"
# include "NSScrollView+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface WSINSTextView : NSTextView

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "NSScrollView+WSI.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(ui)

class TextView
: public View< TextView, WSINSTextView >
{
    typedef View< WSINSTextView > super;
    
public:
    
    TextView()
    {
        PASS;
    }        
    
    ~TextView()
    {
        PASS;
    }
        
    inline ns::String string_value() const
    {
        return this->_self.string;
    }
    
    inline void set_value(ns::String const& str)
    {
        [this->_self setString:str];
    }
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif