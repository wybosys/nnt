
# ifndef __NNT_OPENAPI_WECHAT_D851BC7271AF46D4BAAA5A63A44671C7_H_INCLUDED
# define __NNT_OPENAPI_WECHAT_D851BC7271AF46D4BAAA5A63A44671C7_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(WeChat);

@interface WeChat : NNTObject {
    
    NSString *_appid, *_callback;
    
    NNTDECL_PRIVATE(WeChat);
}

@property (nonatomic, copy) NSString *appid, *callback;

- (void)execute:(id)obj;

@end

@interface WeChatPost : NNTObject {
    NSString *_content;
}

@property (nonatomic, copy) NSString *content;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(tencent)
NNT_BEGIN_NS(wechat)

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

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
