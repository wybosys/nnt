
# ifndef __NNT_ERROR_E667BFB7201B4CA3913E135A2D652376_H_INCLUDED
# define __NNT_ERROR_E667BFB7201B4CA3913E135A2D652376_H_INCLUDED

# ifdef NNT_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class Error
: public ns::Object<NSError>
{
    
    typedef ns::Object<NSError> super;
    
public:
    
    Error()
    {
        
    }
    
    Error(id r)
    : super(r)
    {
        
    }
    
    ns::Dictionary user_info() const
    {
        return this->_self.userInfo;
    }
    
    ns::String description() const
    {
        return this->_self.localizedDescription;
    }
    
    ns::String failure_reason() const
    {
        return this->_self.localizedFailureReason;
    }
    
    ns::String recovery_suggestion() const
    {
        return this->_self.localizedRecoverySuggestion;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif
