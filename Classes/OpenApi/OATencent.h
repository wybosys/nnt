
# ifndef __WSI_OA_TENCENT_D7C5ED979171489D86A25C115082155F_H_INCLUDED
# define __WSI_OA_TENCENT_D7C5ED979171489D86A25C115082155F_H_INCLUDED

# import "OAuth.h"

WSI_BEGIN_HEADER_OBJC

@interface OARequestTencent : OARequest_1_0 {
    
    NSString *urlCallback;
}

@property (nonatomic, copy) NSString *urlCallback;

@end

@interface OAuthorizeTencent : OAuthorize_1_0 {
    
}

- (NSString*)valueForKey:(NSString *)key ofQuery:(NSString*)query;

@end

@interface OAccessTencent : OAccess_1_0
@end

@interface OATencent : OAuth_1_0
@end

@interface OATencentWeibo : OATencent
@end

@interface OApiTencentQQ : OACommonApi_1_0 {
    NSString *str_apiType;
    NSMutableArray *_tencent_params;
}

@property (nonatomic, copy) NSString *str_apiType;
@property (nonatomic, retain, getter = get_tencent_params) NSMutableArray *tencent_params;

- (NSMutableArray*)get_tencent_params;

@end

@interface OApiTencentUserInfo : OApiTencentQQ 
@end

@interface OApiTencentWeiboPost : OApiTencentQQ {
}

@property (nonatomic, copy) NSString *content, *clientip;
@property (nonatomic, copy) NSString *jing, *wei;

@end

@interface OApiTencentWeiboShow : OApiTencentQQ {
}

@property (nonatomic, copy) NSString *id;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(tencent)

typedef oauth::Provider<OATencent> Provider;

WSI_BEGIN_NS(weibo)

typedef oauth::PostFunction<OApiTencentUserInfo> Userinfo;
typedef oauth::PostFunction<OApiTencentWeiboPost> Post;

WSI_END_NS

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
