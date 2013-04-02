
# ifndef __NNTNS_TEXTVIEW_F6E2A58E55DC4BBF97C7CEBDF553E07D_H_INCLUDED
# define __NNTNS_TEXTVIEW_F6E2A58E55DC4BBF97C7CEBDF553E07D_H_INCLUDED

# include "NSControl+NNT.h"
# include "NSScrollView+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NNTNSTextView : NSTextView

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NSScrollView+NNT.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

class TextView
: public View< TextView, NNTNSTextView >
{
    typedef View< NNTNSTextView > super;
    
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

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif