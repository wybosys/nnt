
# ifndef __OASOHU_93B9ACD7C97A4B2DBA73CEE7E07A1C0C_H_INCLUDED
# define __OASOHU_93B9ACD7C97A4B2DBA73CEE7E07A1C0C_H_INCLUDED

# import "OAuth.h"

NNT_BEGIN_HEADER_OBJC

@interface OARequestSohu : OARequest_1_0 
@end

@interface OAuthorizeSohu : OAuthorize_1_0
@end

@interface OAccessSohu : OAccess_1_0
@end 

@interface OASohu : OAuth_1_0
@end

@interface OApiSohu : OACommonApi_1_0 {
    NSMutableArray *_sohu_params;
}

@property (nonatomic, retain, getter = get_sohu_params) NSMutableArray *sohu_params;

- (NSMutableArray*)get_sohu_params;

@end

@interface OApiSohuUserInfo : OApiSohu 
@end

@interface OApiSohuPost : OApiSohu {
    
}

@property (nonatomic, copy) NSString *content;

@end

NNT_END_HEADER_OBJC

#endif