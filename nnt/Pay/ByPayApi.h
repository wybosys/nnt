
# ifndef __NNT_PAY_UNIPAY_43395A86606A4575A3B031DA69A2BA83_H_INCLUDED
# define __NNT_PAY_UNIPAY_43395A86606A4575A3B031DA69A2BA83_H_INCLUDED

# import "PayNullApi.h"

NNT_BEGIN_HEADER_OBJC

@interface ByPayApi : PayNullApi

@property (nonatomic, copy) NSString *client_id, *partner_id;
@property (nonatomic, retain) NSData *result;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(pay)

class ByPay
: public tpl::PayObject<ByPay, ByPayApi>
{
public:
    
    NNTDECL_PROPERTY_COPY(client_id, NSString*);
    NNTDECL_PROPERTY_COPY(partner_id, NSString*);
    NNTDECL_PROPERTY_RETAIN(result, NSData*);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
