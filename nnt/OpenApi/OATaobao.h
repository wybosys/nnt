
# ifndef __NNT_OA_TAOBAO_67FE1FE081714FF5A686B32C016CAAD6_H_INCLUDED
# define __NNT_OA_TAOBAO_67FE1FE081714FF5A686B32C016CAAD6_H_INCLUDED

# import "OAuth.h"

NNT_BEGIN_HEADER_OBJC

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

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(taobao)

typedef oauth::Provider<OATaobao> Provider;
typedef oauth::Function<OATaobaoUserinfo> Userinfo;

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
