
# ifndef __WSI_QZ_TRANSITION_D454D5B6A0614CC7B66AEA4421913FC7_H_INCLUDED
# define __WSI_QZ_TRANSITION_D454D5B6A0614CC7B66AEA4421913FC7_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSI_EXTERN NSString* kCATransitionPageCurl;
WSI_EXTERN NSString* kCATransitionPageUnCurl;
WSI_EXTERN real kCATransitionDuration;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "QzAnimation.h"

WSI_BEGIN_HEADER_CXX 
WSI_BEGIN_NS(qz)

class Transition
: public Animation<CATransition>
{
public:
    
    Transition()
    {
        set_duration(kCATransitionDuration);
    }

    void set_duration(real sec)
    {
        [this->_self setDuration:sec];
    }
    
    void set_type(ns::String const& str)
    {
        this->_self.type _assign_ str;
    }
    
    void set_subtype(ns::String const& str)
    {
        this->_self.subtype _assign_ str;
    }
    
    inline operator CAAnimation* () const
    {
        return (CAAnimation*)this->_self;
    }
    
};

WSI_END_NS 
WSI_END_HEADER_CXX

# endif

# endif