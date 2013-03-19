
# ifndef __WSI_OA_KAIXIN_B8D063AED22C4332ACF9C611A513FE2F_H_INCLUDED
# define __WSI_OA_KAIXIN_B8D063AED22C4332ACF9C611A513FE2F_H_INCLUDED

# import "OAuth.h"

WSI_BEGIN_HEADER_OBJC

@interface OARequestKaixin : OARequest_1_0 {
    
    NSString *urlCallback;
}

@property (nonatomic, copy) NSString *urlCallback;

@end

@interface OAuthorizeKaixin  : OAuthorize_1_0 {
    
}

@end

@interface OAccessKaixin  : OAccess_1_0
@end

@interface OAKaixin  : OAuth_1_0
@end

@interface OApiKaixin  : OACommonApi_1_0 {
    NSString *str_apiType;
    NSMutableArray *_kaixin_params;
}

@property (nonatomic, copy) NSString *str_apiType;
@property (nonatomic, retain, getter = get_kaixin_params) NSMutableArray *kaixin_params;

@end

@interface OApiKaixinUserInfo : OApiKaixin 
@end

@interface OApiKaixinDiaryPost : OApiKaixin 

@property (nonatomic, copy) NEED NSString *content, *title;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(kaixin)

typedef oauth::Provider<OAKaixin> Provider;

WSI_BEGIN_NS(sns)

typedef oauth::Function<OApiKaixinUserInfo> Userinfo;

class Post
: public oauth::PostFunction<OApiKaixinDiaryPost>
{
public:
    
    void set_content(ns::String const& str)
    {
        this->_self.content = str;
    }
    
    void set_title(ns::String const& str)
    {
        this->_self.title = str;
    }
    
};

WSI_END_NS

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
