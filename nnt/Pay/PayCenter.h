
# ifndef __WSI_PAYCENTER_55EEBCF63F6B4579920C0CD4C1D0AB54_H_INCLUDED
# define __WSI_PAYCENTER_55EEBCF63F6B4579920C0CD4C1D0AB54_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface PayCenter : WSIObject {
    
    @private
    NSDictionary *classes;
}

//! get instance.
+ (PayCenter*)getInstance;

//! send.
- (BOOL)send:(NSString*)api data:(id)data;
- (BOOL)send:(NSString*)api data:(id)data handle:(OUT id*)handle;

@end

WSI_EXTERN signal_t kSignalPayReceive;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(pay)

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

WSI_END_NS

typedef pay::Center PayCenter;

WSI_END_HEADER_CXX

# endif

# endif