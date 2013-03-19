
# ifndef __NNT_QZ_TRANSITION_D454D5B6A0614CC7B66AEA4421913FC7_H_INCLUDED
# define __NNT_QZ_TRANSITION_D454D5B6A0614CC7B66AEA4421913FC7_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNT_EXTERN NSString* kCATransitionPageCurl;
NNT_EXTERN NSString* kCATransitionPageUnCurl;
NNT_EXTERN real kCATransitionDuration;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "QzAnimation.h"

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(qz)

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

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

# endif