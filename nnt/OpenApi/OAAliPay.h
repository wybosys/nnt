
# ifndef __NNT_OA_ALIPAY_2A67D8F28B6A4EB2A6A96703960F826E_H_INCLUDED
# define __NNT_OA_ALIPAY_2A67D8F28B6A4EB2A6A96703960F826E_H_INCLUDED

# import "OAuth.h"

NNT_BEGIN_HEADER_OBJC

@interface OARequestAlipay : OARequest_2_0
@end

@interface OAuthorizeAlipay : OAuthorize_2_0
@end

@interface OAccessAlipay : OAccess_2_0
@end

@interface OApiAlipay : OACommonApi_2_0
@end

@interface OAliPay : OAuth_2_0
@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(alipay)

typedef oauth::Provider<OAliPay> Provider;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
