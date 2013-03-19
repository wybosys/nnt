
# ifndef __WSI_CONTEXT_USER_8E9468CD486C42F5A5CE711BAE1811DE_H_INCLUDED
# define __WSI_CONTEXT_USER_8E9468CD486C42F5A5CE711BAE1811DE_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(Context);
WSIDECL_EXTERN_CLASS(WSIConfiguration);

@interface User : WSIObject {

    //! name.
    NSString *_nickname;
    
    //! passwd.
    NSString *_passwd;
    
    //! id. use for login.
    NSString* _identity;
    
    //! token.
    NSString* _token;
    
    //! login state.
    BOOL _logined;
    
    //! configuration.
    WSIConfiguration* _configuration;
    
    //! reference to context.
    Context *_ctx;
}

@property (nonatomic, copy) NSString *nickname;
@property (nonatomic, copy) NSString *passwd;
@property (nonatomic, readonly, copy) NSString *identity;
@property (nonatomic, copy) NSString *token;
@property (nonatomic, readonly) BOOL logined;
@property (nonatomic, retain, readonly) WSIConfiguration* configuration;
@property (nonatomic, assign) Context *ctx;

//! login & logout.
- (void)login:(NSString*)identity;
- (void)logout;

//! get configuration.
+ (WSIConfiguration*)configurationOfIdentity:(NSString*)identity;
+ (NSString*)configurationNameOfIdentity:(NSString*)identity;

@end

WSI_EXTERN signal_t kSignalUserLogin;
WSI_EXTERN signal_t kSignalUserLogout;
WSI_EXTERN signal_t kSignalUserLoginStatusChanged;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "WSIConfiguration.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class Context;

class User
: public ns::Object< ::User>
{
    typedef ns::Object< ::User> super;
    
public:
    
    typedef ::wsi::store::ns::Configuration configuration_type;
    
    User()
    : super(nil),
    _config(NULL)
    {
        PASS;
    }
    
    ~User()
    {
        safe_delete(_config);
    }
    
    void set_nick(String const& str)
    {
        this->_self.nickname = str;
    }
    
    String nickname() const
    {
        return this->_self.nickname;
    }
    
    void login(String const& identity)
    {
        [this->_self login:identity];
    }
    
    void set_passwd(String const& pwd)
    {
        this->_self.passwd = pwd;
    }        
    
    String passwd() const
    {
        return this->_self.passwd;
    }
    
    void logout()
    {
        [this->_self logout];
    }
    
    bool is_logined() const
    {
        return this->_self.logined;
    }
    
    String identity() const
    {
        return this->_self.identity;
    }
    
    void set_token(String const& str)
    {
        this->_self.token = str;
    }
    
    String token() const
    {
        return this->_self.token;
    }
    
    configuration_type& configuration()
    {
        if (_config == NULL)
            _config = new configuration_type(this->_self.configuration);
        else
            _config->renew(this->_self.configuration);
        return *_config;
    }
    
    static configuration_type Configuration(ns::String const& idr)
    {
        WSIConfiguration* conf = [::User configurationOfIdentity:idr];
        return configuration_type(conf);
    }
    
    static ns::String ConfigurationName(ns::String const& idr)
    {
        return [::User configurationNameOfIdentity:idr];
    }
    
protected:
    
    configuration_type* _config;
    
    friend class Context;
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# endif
