
# ifndef __NNT_CONTEXT_USER_8E9468CD486C42F5A5CE711BAE1811DE_H_INCLUDED
# define __NNT_CONTEXT_USER_8E9468CD486C42F5A5CE711BAE1811DE_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(Context);
NNTDECL_EXTERN_CLASS(NNTConfiguration);

@interface User : NNTObject {

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
    NNTConfiguration* _configuration;
    
    //! reference to context.
    Context *_ctx;
}

@property (nonatomic, copy) NSString *nickname;
@property (nonatomic, copy) NSString *passwd;
@property (nonatomic, readonly, copy) NSString *identity;
@property (nonatomic, copy) NSString *token;
@property (nonatomic, readonly) BOOL logined;
@property (nonatomic, retain, readonly) NNTConfiguration* configuration;
@property (nonatomic, assign) Context *ctx;

//! login & logout.
- (void)login:(NSString*)identity;
- (void)logout;

//! get configuration.
+ (NNTConfiguration*)configurationOfIdentity:(NSString*)identity;
+ (NSString*)configurationNameOfIdentity:(NSString*)identity;

@end

NNT_EXTERN signal_t kSignalUserLogin;
NNT_EXTERN signal_t kSignalUserLogout;
NNT_EXTERN signal_t kSignalUserLoginStatusChanged;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "NNTConfiguration.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class Context;

class User
: public ns::Object< ::User>
{
    typedef ns::Object< ::User> super;
    
public:
    
    typedef ::nnt::store::ns::Configuration configuration_type;
    
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
        NNTConfiguration* conf = [::User configurationOfIdentity:idr];
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# endif
