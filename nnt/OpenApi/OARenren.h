
# ifndef __NNT_OA_RENREN_F3AB57E2771D4517A90B463DC0EC8B1A_H_INCLUDED
# define __NNT_OA_RENREN_F3AB57E2771D4517A90B463DC0EC8B1A_H_INCLUDED

# import "OAuth.h"

NNT_BEGIN_HEADER_OBJC

@interface OARequestRenRen : OARequest_2_0

@end

@interface OAuthorizeRenRen : OAuthorize_2_0

- (NSString*)valueForKey:(NSString *)key ofQuery:(NSString*)query;

@end

@interface OAccessRenRen : OAccess_2_0 

@end

@interface OARenRen : OAuth_2_0 

@end

@interface OApiRenRen : OACommonApi_2_0 {
    NSString *str_apiType;
}

@property (nonatomic, copy) NSString *str_apiType;

@end

@interface OApiRenRenUserInfo: OApiRenRen 

@end

@interface OApiRenRenWeiboPost : OApiRenRen 

@property (nonatomic, copy) NEED NSString *title, *content;

@end


// renren API V2.0
@interface OApiRenRen_2_0 : OACommonApi_2_0

@end

@interface OApiRenRenUserInfo_2_0 : OApiRenRen_2_0

@end

@interface OApiRenRenUserLoginGet_2_0 : OApiRenRen_2_0

@property (nonatomic, readonly) NSString *user_id, *nickname;

@end

typedef enum {
    PRIVATE,    //仅自己可见
    PUBLIC,     //所有人可见
    PASSWORD,   //密码访问可见
    FRIEND,     //仅好友可见
} AccessControlType;

@interface OApiRenRenBlogPut_2_0 : OApiRenRen_2_0

@property (nonatomic, copy) NEED NSString *title, *content;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(renren)

typedef oauth::Provider<OARenRen> Provider;

NNT_BEGIN_NS(sns)

typedef oauth::Function<OApiRenRenUserInfo> Userinfo;
typedef oauth::Function<OApiRenRenUserInfo_2_0> Userinfo_2_0;
typedef oauth::Function<OApiRenRenUserLoginGet_2_0> UserLoginGet_2_0;
typedef oauth::Function<OApiRenRenBlogPut_2_0> BolgPut_2_0;

class Post
: public oauth::PostFunction<OApiRenRenWeiboPost>
{
public:
    
    void set_title(ns::String const& str)
    {
        this->_self.title = str;
    }
    
    void set_content(ns::String const& str)
    {
        this->_self.content = str;
    }
    
};

class BlogPut
: public oauth::PostFunction<OApiRenRenBlogPut_2_0>
{
public:
    
    void set_title(ns::String const& str)
    {
        this->_self.title = str;
    }
    
    void set_content(ns::String const& str)
    {
        this->_self.content = str;
    }
};

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
