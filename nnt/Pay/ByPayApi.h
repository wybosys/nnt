
# ifndef __WSI_PAY_UNIPAY_43395A86606A4575A3B031DA69A2BA83_H_INCLUDED
# define __WSI_PAY_UNIPAY_43395A86606A4575A3B031DA69A2BA83_H_INCLUDED

# import "PayNullApi.h"

WSI_BEGIN_HEADER_OBJC

@interface ByPayApi : PayNullApi

@property (nonatomic, copy) NSString *client_id, *partner_id;
@property (nonatomic, retain) NSData *result;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(pay)

class ByPay
: public tpl::PayObject<ByPay, ByPayApi>
{
public:
    
    WSIDECL_PROPERTY_COPY(client_id, NSString*);
    WSIDECL_PROPERTY_COPY(partner_id, NSString*);
    WSIDECL_PROPERTY_RETAIN(result, NSData*);
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
