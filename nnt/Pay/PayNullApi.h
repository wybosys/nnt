
# ifndef __NNT_PAY_PAYNULLAPI_1EB3A5B56AFE465D96772CE0CE09090F_H_INCLUDED
# define __NNT_PAY_PAYNULLAPI_1EB3A5B56AFE465D96772CE0CE09090F_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface PayNullApi : NNTObject {
    
    id _requestData;
    
}

@property (nonatomic, retain) id requestData;

//! identity.
+ (NSString*)identity;

//! send.
- (BOOL)send:(id)data;

@end

NNT_EXTERN signal_t kSignalPayReceive;
NNT_EXTERN signal_t kSignalPaySuccess;
NNT_EXTERN signal_t kSignalPayFailed;
NNT_EXTERN signal_t kSignalPaying;
NNT_EXTERN signal_t kSignalPayRestore;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(pay)
NNT_BEGIN_NS(tpl)

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

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif