
# ifndef __WSI_OA_ALIPAY_2A67D8F28B6A4EB2A6A96703960F826E_H_INCLUDED
# define __WSI_OA_ALIPAY_2A67D8F28B6A4EB2A6A96703960F826E_H_INCLUDED

# import "OAuth.h"

WSI_BEGIN_HEADER_OBJC

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

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(alipay)

typedef oauth::Provider<OAliPay> Provider;

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
