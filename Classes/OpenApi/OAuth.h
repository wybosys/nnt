
# ifndef __NNT_OA_AUTH_183E2EDD5CA349BB8C08F187D3B1DB0C_H_INCLUDED
# define __NNT_OA_AUTH_183E2EDD5CA349BB8C08F187D3B1DB0C_H_INCLUDED

# import "OANull.h"
# import "../Security/SecSignature.h"

NNT_BEGIN_HEADER_OBJC

enum {
    OAuthApiTypeUnknown,
    OAuthApiTypeJSON,
    OAuthApiTypeXML,
};

typedef uint OAuthApiType;

NNT_EXTERN NSString* kOAuthHttpConentType;

// string category for oauth.
@interface NSString (OAuth)

- (NSString *)OAEncode;
- (NSString *)OADecode;
+ (NSString *)OAEncode:(NSString*)str;
+ (NSString *)OADecode:(NSString*)str;

@end

// oauth.
@interface OARequest : OANull {
 
    //! url for request.
    NSString* _urlRequest;
    
    //! url for authorize.
    NSString* _urlAuthorize;
    
    //! url for access.
    NSString* _urlAccess;
    
    //! app id.
    NSString* _appId;
    
    //! app key.
    NSString* _appKey;
    
    //! app secret.
    NSString* _appSecret;
    
    //! realm.
    NSString* _realm;
    
    //! nonce.
    NSString* _nonce;
    
    //! timestamp.
    NSString* _timestamp;
    
    //! signature struct.
    sec_signature_func_t _signature;
    
}

@property (nonatomic, copy) NSString *urlRequest, *urlAuthorize, *urlAccess, *realm;
@property (nonatomic, copy) NSString *appId, *appKey, *appSecret;
@property (nonatomic, assign) sec_signature_func_t signature;
@property (nonatomic, copy) NSString *nonce, *timestamp;

//! renew.
- (void)renew;

@end

@interface OARequest_1_0 : OARequest {
    NSString *_token,
    *_token_secret,
    *_verifier,
    *_access_token,
    *_access_token_secret,
    *_user_id;
}

@property (nonatomic, copy) NSString *token, *token_secret, *verifier, *access_token, *access_token_secret, *user_id;

//! get base string.
- (NSString*)baseString;

//! signature string.
- (NSString*)signatureString:(NSString*)ctext secret:(NSString*)secret;

//! get header string.
- (NSString*)headerString;

//! generate parameters into dict.
- (void)generateParameters:(NSMutableDictionary*)dict;

@end

@protocol OAuthorize_1_0 <NSObject>

- (NSString*)url;

@end

@interface OAuthorize_1_0 : NNTObject <OAuthorize_1_0> {
    
    //! url for callback.
    NSString* _urlCallback;
    
    //! auth handle.
    OARequest_1_0* _request;
    
    @protected
    
    //! oauth view.
    id _authView;
    
}

@property (nonatomic, copy) NSString* urlCallback;
@property (nonatomic, retain) OARequest_1_0* request;

//! init.
- (id)initWithRequest:(OARequest_1_0*)req;

//! access.
- (BOOL)go;

//! override.
- (id)authView;
- (void)openAuthView:(NSString*)url;
- (void)closeAuthView;

//! success & failed.
- (void)success;
- (void)failed;

@end

NNT_EXTERN signal_t kSignalAuthorizeSuccess;
NNT_EXTERN signal_t kSignalAuthorizeFailed;
NNT_EXTERN signal_t kSignalAuthorizeExit;

@interface OAccess_1_0 : OANull {
    
    //! request handle.
    OARequest_1_0* _request;
    
    //! auth handle.
    OAuthorize_1_0* _auth;
    
}

@property (nonatomic, retain) OARequest_1_0* request;
@property (nonatomic, retain) OAuthorize_1_0* auth;

//! init.
- (id)initWithRequest:(OARequest_1_0*)request withAuth:(OAuthorize_1_0*)auth;

//! base string.
- (NSString*)baseString;

//! header string.
- (NSString*)headerString;

@end

//! OAuth object.

@protocol OAuth <NSObject>

//! retrieve from server.
- (void)retrieve;

//! serial.
- (void)saveTo:(NSMutableDictionary*)dict;
- (BOOL)loadFrom:(NSDictionary*)dict;

@end

@interface OAuth_1_0 : NNTObject <OAuth> {
    
    OARequest_1_0* _request;
    OAuthorize_1_0* _authorize;
    OAccess_1_0* _access;
    
}

@property (nonatomic, readonly) OARequest_1_0* request;
@property (nonatomic, copy) NSString* callback;
@property (nonatomic, assign) BOOL isValid;

// redirect.
@property (nonatomic, readonly) NSString* user_id;

//! init.
- (id)init;
- (id)initFromData:(NSDictionary*)dict;

//! generate a api object.
- (id)api:(NSString*)url cls:(Class)cls;
- (id)api:(id)api;

//! name.
+ (NSString*)Name;
+ (NSString*)UniqueIdentity;
+ (UIImage*)LogoImage;

@end

@interface OANullApi : OANull {
    
    OAuthApiType _apiType;
    
}

@property (nonatomic, assign) OAuthApiType apiType;

//! combine arguments.
- (NSString*)combineArguments:(BOOL)isURL;

//! check if url's parameter.
- (BOOL)isUrlParameter:(NSPair*)obj;

@end

//! u can subclass to implementation a special api.
@interface OACommonApi_1_0 : OANullApi {
    
    OARequest_1_0* _request;
    
}

@property (nonatomic, retain) OARequest_1_0* request;
@property (nonatomic, readonly) NSString* baseUrl;

- (id)init;
- (id)initWithRequest:(OARequest_1_0*)req;
- (id)initWithOAuth:(id<OAuth>)auth;

//! retrieve.
- (BOOL)retrieve_sync;

@end

@interface OARequest_2_0 : OARequest {
    
    //! clientId.
    NSString *_clientId;
    
    //! client secret.
    NSString *_clientSecret;

    //! response type.
    NSString *_responseType;
    
    //! grant type.
    NSString *_grantType;
    
    //! code.
    NSString *_code;
    
    //! redirect url.
    NSString *_redirectUrl;
    
    //! cancel redirect url.
    NSString *_redirectCancelUrl;
    
    //! scopes.
    NSMutableArray* _scopes;
    
    //! access token.
    NSString* _access_token;
    
    //! expires and remind.
    uint _expires, _remind;
    
    //! uid.
    NSString* _user_id;
    
}

@property (nonatomic, copy) NSString *clientId, *clientSecret;
@property (nonatomic, copy) NSString *responseType, *grantType, *code, *redirectUrl, *redirectCancelUrl;
@property (nonatomic, retain) NSMutableArray* scopes;
@property (nonatomic, copy) NSString* access_token;
@property (nonatomic, assign) uint expires, remind;
@property (nonatomic, copy) NSString* user_id;

//! generate parameters into dict.
- (void)generateParameters:(NSMutableDictionary*)dict;

//! scopes string.
- (NSString*)generateScopes;

@end

@protocol OAuthorize_2_0 <NSObject>

- (NSString*)url;

@end

@interface OAuthorize_2_0 : NNTObject <OAuthorize_2_0> {

    OARequest_2_0 *_request;
    
    //! expire.
    time_t _expire;
    
    @protected
    //! oauth view.
    id _authView;
    
}

@property (nonatomic, retain) OARequest_2_0 *request;
@property (nonatomic, assign) time_t expire;

//! init.
- (id)initWithRequest:(OARequest_2_0*)req;

- (BOOL)go;

//! override.
- (id)authView;
- (void)openAuthView:(NSString*)url;
- (void)openAuthView:(id)authview url:(NSString*)url;
- (void)closeAuthView:(id)authview;
- (void)closeAuthView;

//! success & failed.
- (void)success;
- (void)failed;

@end

@interface OAccess_2_0 : OANull {

    OARequest_2_0 *_request;
    OAuthorize_2_0 *_authorize;
    
}

@property (nonatomic, retain) OARequest_2_0 *request;
@property (nonatomic, retain) OAuthorize_2_0 *authorize;

- (id)initWithRequest:(OARequest_2_0*)req withAuth:(OAuthorize_2_0*)auth;

@end

@interface OAuth_2_0 : NNTObject <OAuth> {
    
    OARequest_2_0* _request;
    OAuthorize_2_0* _authorize;
    OAccess_2_0* _access;
    
}

@property (nonatomic, assign) BOOL isValid;
@property (nonatomic, readonly) OARequest_2_0* request;

//! init.
- (id)init;
- (id)initFromData:(NSDictionary*)dict;

//! generate a api object.
//- (id)api:(NSString*)url cls:(Class)cls;
//- (id)api:(id)api;

//! name.
+ (NSString*)Name;
+ (NSString*)UniqueIdentity;
+ (UIImage*)LogoImage;

@end

@interface OACommonApi_2_0 : OANullApi {
    
    OARequest_2_0* _request;
    
}

@property (nonatomic, retain) OARequest_2_0* request;
@property (nonatomic, readonly) NSString* baseUrl;

- (id)init;
- (id)initWithRequest:(OARequest_2_0*)req;
- (id)initWithOAuth:(id<OAuth>)auth;

//! get.
- (BOOL)retrieve_sync;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(oauth)

template <typename apiT>
class Function
: public ns::Object<apiT>
{
public:
    
    Function()
    : _type(OAuthApiTypeJSON)
    {
        PASS;
    }
    
    void set_format(OAuthApiType type)
    {
        _type = type;
    }
    
    OAuthApiType format() const
    {
        return _type;
    }
    
    bool retrieve()
    {
        return [this->_self retrieve_sync];
    }
    
protected:
    
    OAuthApiType _type;
    
};

template <typename apiT>
class PostFunction
: public Function<apiT>
{
public:
    
    PostFunction()
    {
        
    }
    
    void set_content(ns::String const& str)
    {
        this->_self.content = str;
    }
    
    ns::String content() const
    {
        return this->_self.content;
    }
    
};

template <typename apiT>
class UploadFunction
: public PostFunction<apiT>
{
public:
    
    UploadFunction()
    {
        
    }
    
    void set_image(cg::Image const& img)
    {
        this->_self.image = img;
    }
    
    void set_image(ns::Data const& da)
    {
        this->_self.imageData = da;
    }
    
};

template <typename authT>
class Provider
: public ns::Object<authT>
{
public:
    
    Provider()
    {
        PASS;
    }
    
    void authorize()
    {
        [this->_self retrieve];
    }
    
    template <typename funcT>
    bool execute(funcT& func)
    {
        func.nsobject().request = this->_self.request;
        func.nsobject().apiType = func.format();
        return func.retrieve();
    }
        
    void save(ns::MutableDictionary& dict) const
    {
        [this->_self saveTo:dict];
    }
    
    bool load(ns::Dictionary const& dict)
    {
        return [this->_self loadFrom:dict] == YES;
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
