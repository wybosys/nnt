
# ifndef __WSI_PAY_PAYNULLAPI_1EB3A5B56AFE465D96772CE0CE09090F_H_INCLUDED
# define __WSI_PAY_PAYNULLAPI_1EB3A5B56AFE465D96772CE0CE09090F_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface PayNullApi : WSIObject {
    
    id _requestData;
    
}

@property (nonatomic, retain) id requestData;

//! identity.
+ (NSString*)identity;

//! send.
- (BOOL)send:(id)data;

@end

WSI_EXTERN signal_t kSignalPayReceive;
WSI_EXTERN signal_t kSignalPaySuccess;
WSI_EXTERN signal_t kSignalPayFailed;
WSI_EXTERN signal_t kSignalPaying;
WSI_EXTERN signal_t kSignalPayRestore;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(pay)
WSI_BEGIN_NS(tpl)

template <typename implT, typename objcT>
class PayObject
: public ns::Object<objcT>
{
public:
    
    PayObject()
    {
        PASS;
    }
    
    bool send(id data)
    {
        return YES == [this->_self send:data];
    }
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif