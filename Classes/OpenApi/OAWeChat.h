
# ifndef __WSI_OPENAPI_WECHAT_D851BC7271AF46D4BAAA5A63A44671C7_H_INCLUDED
# define __WSI_OPENAPI_WECHAT_D851BC7271AF46D4BAAA5A63A44671C7_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(WeChat);

@interface WeChat : WSIObject {
    
    NSString *_appid, *_callback;
    
    WSIDECL_PRIVATE(WeChat);
}

@property (nonatomic, copy) NSString *appid, *callback;

- (void)execute:(id)obj;

@end

@interface WeChatPost : WSIObject {
    NSString *_content;
}

@property (nonatomic, copy) NSString *content;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(tencent)
WSI_BEGIN_NS(wechat)

class Post
: public ns::Object<WeChatPost>
{
public:
    
    void set_content(ns::String const& str)
    {
        this->_self.content = str;
    }
    
    ns::String content() const
    {
        return this->_self.content;
    }
    
};

class Provider
: public ns::Object<WeChat>
{
public:
    
    Provider();
    ~Provider();
    
    template <typename apiT>
    void execute(apiT const& api)
    {
        [this->_self execute:api];
    }
    
    void set_appid(ns::String const& str)
    {
        this->_self.appid = str;
    }
    
    void set_callback(ns::String const& str)
    {
        this->_self.callback = str;
    }
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
