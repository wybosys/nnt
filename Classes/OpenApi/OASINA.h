
# ifndef __NNT_OA_SINA_1A640D28B1B5462882AE22CA0490E870_H_INCLUDED
# define __NNT_OA_SINA_1A640D28B1B5462882AE22CA0490E870_H_INCLUDED

# import "OAuth.h"

NNT_BEGIN_HEADER_OBJC

@interface OARequestSina : OARequest_2_0
@end

@interface OAuthorizeSina : OAuthorize_2_0
@end

@interface OAccessSina : OAccess_2_0
@end

@interface OApiSina : OACommonApi_2_0
@end

@interface OASina : OAuth_2_0
@end

@interface OASinaWeibo : OASina 
@end

@interface OApiSinaUserinfo : OApiSina

@property (nonatomic, copy) NSString* uid;

@end

@interface OApiSinaWeiboPost : OApiSina

@property (nonatomic, copy) NSString* content;

@end

@interface OApiSinaWeiboUpload : OApiSina

@property (nonatomic, copy) NSString* content;
@property (nonatomic, retain) WCGImage* image;
@property (nonatomic, retain) NSData* imageData;

@end

@interface OApiSinaFriendshipsCreate : OApiSina

@property (nonatomic, copy) NSString *screen_name;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(sina)

typedef oauth::Provider<OASina> Provider;

NNT_BEGIN_NS(weibo)

typedef oauth::Function<OApiSinaUserinfo> Userinfo;
typedef oauth::PostFunction<OApiSinaWeiboPost> Post;
typedef oauth::UploadFunction<OApiSinaWeiboUpload> Upload;

NNT_END_NS

typedef weibo::Post WeiboPost;
typedef weibo::Upload WeiboUpload;

NNT_BEGIN_NS(friendships)

class Create
: public oauth::Function<OApiSinaFriendshipsCreate>
{
public:
    
    void set_name(ns::String const& str)
    {
        this->_self.screen_name = str;
    }
    
};

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif