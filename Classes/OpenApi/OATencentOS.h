
# ifndef __NNT_OA_TENCENT_OPENSPACE_8BB5EFA8053B441A8E7B4EDE9C43686C_H_INCLUDED
# define __NNT_OA_TENCENT_OPENSPACE_8BB5EFA8053B441A8E7B4EDE9C43686C_H_INCLUDED

# import "OAuth.h"

NNT_BEGIN_HEADER_OBJC

@interface OARequestQQOS : OARequest_2_0
@end

@interface OAuthorizeQQOS : OAuthorize_2_0
@end

@interface OAccessQQOS : OAccess_2_0
@end

@interface OATencentOS : OAuth_2_0 
@end

@interface OApiTencentOS : OACommonApi_2_0 {
    NSString* strApiType;
}

@property (nonatomic, copy) NSString *strApiType;

@end

@interface OApiQQOSUserInfo : OApiTencentOS
@end

@interface OApiQQOSAddShare : OApiTencentOS {
    NSString *title;
    NSString *reference;
    NSString *content;
    NSURL *image;
    NSString *site;
}

@property (nonatomic, copy) NEED NSString *title, *reference, *site;
@property (nonatomic, copy) OPTIONAL NSString *content;
@property (nonatomic, copy) OPTIONAL NSURL *image;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(tencent)
NNT_BEGIN_NS(opensns)

typedef oauth::Provider<OATencentOS> Provider;

NNT_BEGIN_NS(weibo)

typedef oauth::Function<OApiQQOSUserInfo> Userinfo;

class Post
: public oauth::PostFunction<OApiQQOSAddShare>
{
public:
    
    void set_title(ns::String const& str)
    {
        this->_self.title = str;
    }
    
    void set_reference(ns::String const& str)
    {
        this->_self.reference = str;
    }
    
    void set_image(ns::URL const& url)
    {
        this->_self.image = url;
    }
    
    void set_site(ns::String const& st)
    {
        this->_self.site = st;
    }
    
};

NNT_END_NS

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
