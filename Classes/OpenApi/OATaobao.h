
# ifndef __WSI_OA_TAOBAO_67FE1FE081714FF5A686B32C016CAAD6_H_INCLUDED
# define __WSI_OA_TAOBAO_67FE1FE081714FF5A686B32C016CAAD6_H_INCLUDED

# import "OAuth.h"

WSI_BEGIN_HEADER_OBJC

@interface OARequestTaobao : OARequest_2_0

@property (nonatomic, copy) NSString* refresh_token;

@end

@interface OAuthorizeTaobao : OAuthorize_2_0
@end

@interface OAccessTaobao : OAccess_2_0
@end

@interface OApiTaobao : OACommonApi_2_0

@property (nonatomic, assign) BOOL inSandbox;

@end

@interface OATaobao : OAuth_2_0
@end

@interface OATaobaoUserinfo : OApiTaobao

@property (nonatomic, copy) NSString *nick, *fields;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(taobao)

typedef oauth::Provider<OATaobao> Provider;
typedef oauth::Function<OATaobaoUserinfo> Userinfo;

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
