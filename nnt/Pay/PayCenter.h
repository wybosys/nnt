
# ifndef __NNT_PAYCENTER_55EEBCF63F6B4579920C0CD4C1D0AB54_H_INCLUDED
# define __NNT_PAYCENTER_55EEBCF63F6B4579920C0CD4C1D0AB54_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface PayCenter : NNTObject {
    
    @private
    NSDictionary *classes;
}

//! get instance.
+ (PayCenter*)getInstance;

//! send.
- (BOOL)send:(NSString*)api data:(id)data;
- (BOOL)send:(NSString*)api data:(id)data handle:(OUT id*)handle;

@end

NNT_EXTERN signal_t kSignalPayReceive;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(pay)

class Center
: public ns::Object< ::PayCenter >
{
    typedef ns::Object< ::PayCenter > super;
    
public:
    
    Center()
    {
        PASS;
    }
    
    bool send(ns::String const& api, id da)
    {
        return YES == [this->_self send:api data:da];
    }
    
};

NNT_END_NS

typedef pay::Center PayCenter;

NNT_END_HEADER_CXX

# endif

# endif