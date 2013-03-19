
# ifndef __NNT_PAY_ALIPAYAPI_B5CD7A6143BF44EA9763D35692905723_H_INCLUDED
# define __NNT_PAY_ALIPAYAPI_B5CD7A6143BF44EA9763D35692905723_H_INCLUDED

# import "PayNullApi.h"

NNT_BEGIN_HEADER_OBJC

typedef enum {
    AlipayApiSuc = 1,
    AlipayApiError = -1,
    AlipayApiTypeError = -2,
    AlipayApiLostPartner = -3,
    AlipayApiLostSeller = -4,
    AlipayApiLostTradeNo = -5,
    AlipayApiLostAmount = -6,
    AlipayApiLostRSAKey = -7,
} AlipayApiCode;

@interface AlipayApi : PayNullApi

@property (nonatomic, assign) AlipayApiCode errcode;

+ (NSString*)generateTradeNo;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(pay)

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
