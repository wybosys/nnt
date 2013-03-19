
# import "Core.h"
# import "OAuth.h"
# import "NullObjParser.h"
# import "HttpRequest.h"
# import "Server.h"
# import "Context.h"
# import "UIOAuthView.h"
# import "Mime+NNT.h"

using namespace ::wsi;

NNT_BEGIN_OBJC

signal_t kSignalAuthorizeSuccess = @"::nnt::authorize::success";
signal_t kSignalAuthorizeFailed = @"::nnt::authorize::failed";
signal_t kSignalAuthorizeExit = @"::nnt::authorize::exit";

NSString* kOAuthCallbackSuccess = @"::oauth::success";
NSString* kOAuthCallbackCancel = @"::oauth::cancel";

@implementation NSString (OAuth)

- (NSString *)OAEncode {
    NSString *result = (NSString *)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,
                                                                           (CFStringRef)self,
                                                                           NULL,
																		   CFSTR("!*'();:@&=+$,/?%#[]"),
                                                                           kCFStringEncodingUTF8);
    return [result autorelease];
}

- (NSString*)OADecode {
	NSString *result = (NSString *)CFURLCreateStringByReplacingPercentEscapesUsingEncoding(kCFAllocatorDefault,
																						   (CFStringRef)self,
																						   CFSTR(""),
																						   kCFStringEncodingUTF8);
    [result autorelease];
	return result;
}

+ (NSString *)OAEncode:(NSString*)str {
    return [str OAEncode];
}

+ (NSString *)OADecode:(NSString*)str {
    return [str OADecode];
}

@end

@interface OAuthParser : NullObjParser

@end

@implementation OAuthParser

- (id)init {
    self = [super init];
    self.contentType = kMimeTypeFormUrlEncoded;
    return self;
}

- (id)to_object:(id)data {
    NSString* str = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
    trace_msg([str OADecode]);
    NSArray* arr_result = [str componentsSeparatedByString:@"&"];
    
    ns::MutableDictionary dict_result;
    for (NSString* each in arr_result) {
        NSArray *arr_each = [each componentsSeparatedByString:@"="];
        if ([arr_each count] == 2) {
            dict_result[arr_each.first] = arr_each.second;
        }
    }
    [str release];    
    int err_code = [dict_result[@"error_code"] intValue];
    if (err_code) {
        NSString* msg = [dict_result[@"error"] OADecode];
        trace_msg(msg);
        [self emit:kSignalParserError result:msg];
        return nil;
    }
    
    // successfull.
    return dict_result.consign();
}

@end

@implementation OARequest

@synthesize urlRequest = _urlRequest, urlAuthorize = _urlAuthorize, urlAccess = _urlAccess, realm = _realm;
@synthesize appKey = _appKey, appSecret = _appSecret, appId = _appId;
@synthesize signature = _signature;
@synthesize nonce = _nonce, timestamp = _timestamp;

- (id)init {
    self = [super init];
    
    self.version = (version_t){0, 0, 0, "0.0"};
    self.classRpc = [HttpRequest_Post class];
    
    OAuthParser *parser = [[OAuthParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    self.realm = @"";
    
    return self;
}

- (void)dealloc {
    safe_release(_urlRequest);
    safe_release(_urlAuthorize);
    safe_release(_urlAccess);
    safe_release(_realm);
    safe_release(_appId);
    safe_release(_appKey);
    safe_release(_appSecret);
    safe_release(_nonce);
    safe_release(_timestamp);
    
    [super dealloc];
}

- (void)renew {
    //self.nonce = kNSStringNonce();
    self.nonce = [kNSStringNonce() md5];
    self.timestamp = kNSStringTimestamp();
}

- (NSString*)url {
    return self.urlRequest;
}

@end

@implementation OARequest_1_0

@synthesize token = _token, token_secret = _token_secret, verifier = _verifier, access_token = _access_token, access_token_secret = _access_token_secret, user_id = _user_id;

- (id)init {
    self = [super init];
    
    self.version = (version_t){1, 0, 0, "1.0"};
    self.user_id = @"";
    
    return self;
}

- (void)dealloc {
    safe_release(_token);
    safe_release(_token_secret);
    safe_release(_verifier);
    safe_release(_access_token);
    safe_release(_access_token_secret);
    safe_release(_user_id);

    [super dealloc];
}

- (NSString*)signatureString:(NSString *)ctext secret:(NSString *)secret {
    return self.signature.method(ctext, secret);
}

- (NSString*)baseString {
    ns::MutableDictionary dict;
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.urlRequest OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    return ret;
}

- (NSString*)headerString {
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@&", self.appSecret];
    //trace_msg(str_secret);
    NSString* str_signed = [self signatureString:str_base secret:str_secret];
    //trace_msg(str_signed);
    
    ns::MutableDictionary dict;
    dict[@"oauth_signature"] = [str_signed OAEncode];    
    [self generateParameters:dict];
    
    NSString *header = [NSString stringWithFormat:@"OAuth %@", [dict combineWithKVSep:@"=" andSegSep:@", " keysur:@"" valsur:@"\""]];
    return header;
}

- (void)generateParameters:(NSMutableDictionary*)__dict {
    ns::MutableDictionary dict(__dict);
    dict[@"oauth_consumer_key"] = [self.appKey OAEncode];
    dict[@"oauth_nonce"] = [self.nonce OAEncode];
    dict[@"oauth_signature_method"] = [self.signature.method_name() OAEncode];
    dict[@"oauth_timestamp"] = self.timestamp;
    dict[@"oauth_version"] = [NSString stringWithUTF8String:self.version.ver];    
    
    // add params.
    for (NSPair* each in self.params) {
        if ([each isKindOfClass:[NSPair class]] == NO)
            continue;
        dict[each.first] = each.second;
    }
}

- (NSMutableArray*)get_extend_datas {
    [self renew];
    
    NSMutableArray *ret = [self dup_extend_datas];
    MURLHeaderField *seg = [[MURLHeaderField alloc] init];
    seg.mech = MURLHeaderFieldMechSet;
    seg.value = [self headerString];
    seg.field = @"Authorization";
    [ret addObject:seg];
    [seg release];
    return ret;
}

# pragma mark parser from data.

- (BOOL)process:(NSObject *)__result {
    ns::MutableDictionary dict((NSMutableDictionary*)__result);
    self.token = dict[@"oauth_token"];
    self.token_secret = dict[@"oauth_token_secret"];
    return YES;
}

@end

@implementation OAuthorize_1_0

@synthesize urlCallback = _urlCallback, request = _request;

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAuthorizeSuccess)
NNTEVENT_SIGNAL(kSignalAuthorizeFailed)
NNTEVENT_SIGNAL(kSignalAuthorizeExit)
NNTEVENT_END

- (id)initWithRequest:(OARequest_1_0 *)req {
    self = [super init];
    
    self.request = req;
    self.urlCallback = kOAuthCallbackSuccess;
        
    return self;
}

- (void)dealloc {
    safe_release(_urlCallback);
    safe_release(_request);

    [super dealloc];
}

- (BOOL)go {
    if (_urlCallback == nil)
        return NO;
        
    NNT_AUTORELEASEPOOL_BEGIN
    
    NSString* go_url = [self url];
        
    safe_release(_authView);
    _authView = [[self authView] retain];
    [self openAuthView:go_url];
    
    if ([_authView isKindOfClass:[UIOAuthView class]]) {
        UIOAuthView* view = (UIOAuthView*)_authView;
        if (view.buttonClose) {
            [view.buttonClose connect:kSignalButtonClicked sel:@selector(failed) obj:self];
        }
    }
    
    NNT_AUTORELEASEPOOL_END
    
    return YES;
}

- (id)authView {
    UIOAuthView* authview = [[UIOAuthView alloc] initWithZero];
    authview.showClose = YES;
        
    [authview registerFilter:kOAuthCallbackSuccess type:UIWebViewFilterTypeError].shouldStartLoad = NO;
    [authview registerFilter:kOAuthCallbackCancel type:UIWebViewFilterTypeStartLoad].shouldStartLoad = NO;
    
    [[authview connect:kOAuthCallbackSuccess sel:@selector(act_callback:) obj:self] mainThread];
    [[authview connect:kOAuthCallbackCancel sel:@selector(act_callback:) obj:self] mainThread];
    
    return [authview autorelease];
}

- (void)openAuthView:(NSString*)url {
    [_authView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:url]]];
    [_authView execute];
}

- (void)closeAuthView {
    [_authView close];
    zero_release(_authView);
}

- (void)success {
    [self closeAuthView];
    
    // event.
    [self emit:kSignalAuthorizeSuccess result:self.request];    
    [self emit:kSignalAuthorizeExit];
}

- (void)failed {
    [self closeAuthView];
    
    // event.
    [self emit:kSignalAuthorizeFailed];
    [self emit:kSignalAuthorizeExit];
}

- (void)act_callback:(NNTEventObj*)evt {
    NSString* callback = (NSString*)evt.result;        
    
    NSArray* arr_callback = [callback componentsSeparatedByString:@"?"];
    if ([arr_callback count] != 2) {
        if ([callback matchedByRegex:kOAuthCallbackCancel full:NO]) {                        
            // failed.
            [self failed];                        
            return;
        }
        trace_fmt(@"skip callback: %@", callback);
        return;
    }
    NSString* scheme = [arr_callback objectAtIndex:0];
    NSString* values = [arr_callback objectAtIndex:1];
    
    if ([scheme isEqualToString:kOAuthCallbackSuccess]) {
        // parser the reutrn url.
        NSArray* arr_result = [values componentsMatchedByRegex:@"(\\w+)=(\\w+)"];
        ns::MutableDictionary dict_result;
        for (NSString* each in arr_result) {
            NSArray *arr_each = [each componentsSeparatedByString:@"="];
            if ([arr_each count] == 2) {
                dict_result[arr_each.first] = arr_each.second;
            }
        }
        
        if ([self.request.token isEqualToString:dict_result[@"oauth_token"]]) {        
            self.request.verifier = dict_result[@"oauth_verifier"];
            // send success.
            [self success];
        }
    }
}

- (NSString*)url {
    NSString* ret = [NSString stringWithFormat:@"%@?oauth_token=%@&oauth_callback=%@", self.request.urlAuthorize, self.request.token, self.urlCallback];
    return ret;
}

@end

@implementation OAccess_1_0

@synthesize request = _request, auth = _auth;

- (id)initWithRequest:(OARequest_1_0 *)req withAuth:(OAuthorize_1_0*)au {
    self = [super init];
    
    self.request = req;
    self.auth = au;
    
    self.version = (version_t){1, 0, 0, "1.0"};
    
    OAuthParser *parser = [[OAuthParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    self.classRpc = [HttpRequest_Post class];
    
    return self;
}

- (void)dealloc {
    safe_release(_request);
    safe_release(_auth);

    [super dealloc];
}

- (NSString*)baseString {
    ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_verifier"] = self.request.verifier;
    dict[@"oauth_token"] = self.request.token;
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.request.urlAccess OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
# ifdef NNT_DEBUG
    trace_msg(ret);
# endif
    return ret;
}

- (NSString*)headerString {
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", self.request.appSecret, self.request.token_secret];
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    
    ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_verifier"] = (::nnt::ignore_null)self.request.verifier;
    dict[@"oauth_token"] = self.request.token;
    
    NSString *header = [NSString stringWithFormat:@"OAuth %@", [dict combineWithKVSep:@"=" andSegSep:@", " keysur:@"" valsur:@"\""]];
# ifdef NNT_DEBUG   
    trace_msg(header);
# endif
    return header;
}

- (NSMutableArray*)get_extend_datas {
    [self.request renew];
    
    NSMutableArray *ret = [self dup_extend_datas];
    MURLHeaderField *seg = [[MURLHeaderField alloc] init];
    seg.mech = MURLHeaderFieldMechSet;
    seg.value = [self headerString];
    seg.field = @"Authorization";
    [ret addObject:seg];
    [seg release];
    return ret;
}

- (NSString*)url {
    return self.request.urlAccess;
}

# pragma mark parser from data.

- (BOOL)process:(NSObject *)__result {
    ns::MutableDictionary dict((NSMutableDictionary*)__result);
    self.request.access_token = dict[@"oauth_token"];
    self.request.access_token_secret = dict[@"oauth_token_secret"];
    self.request.user_id = dict[@"user_id"];
    return YES;
}

@end

@interface OACommonApiParser : OAuthParser @end

@implementation OACommonApiParser

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end

@implementation OACommonApi_1_0

@synthesize request = _request;

- (id)init {
    self = [super init];
    
    self.version = (version_t){1, 0, 0, "1.0"};
    
    OACommonApiParser *parser = [[OACommonApiParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    self.classRpc = [HttpRequest_Post class];
    
    return self;
}

- (id)initWithRequest:(OARequest_1_0 *)req {
    self = [self init];
    
    self.request = req;
    
    return self;
}

- (id)initWithOAuth:(OAuth_1_0*)auth {
    self = [self initWithRequest:auth.request];    
    return self;
}

- (void)dealloc {
    safe_release(_request);

    [super dealloc];
}

- (NSString*)baseString {
    ns::MutableDictionary dict;
    
    // base params.
    [self.request generateParameters:dict];
    dict[@"oauth_token"] = self.request.access_token;    
    
    // params.
    for (NSPair *each in self.params) {
        if ([self isUrlParameter:each] == NO)
            continue;
        dict[each.first] = [[each.second OAEncode] OAEncode];
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.baseUrl OAEncode]];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
# ifdef NNT_DEBUG
    trace_msg(ret);
# endif
    return ret;
}

- (NSString*)headerString {
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", self.request.appSecret, self.request.access_token_secret];
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    
    ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_token"] = self.request.access_token;    
    
    NSString *header = [NSString stringWithFormat:@"OAuth %@", [dict combineWithKVSep:@"=" andSegSep:@", " keysur:@"" valsur:@"\""]];
# ifdef NNT_DEBUG    
    trace_msg(header);
# endif
    return header;
}

- (NSMutableArray*)get_extend_datas {
    [self.request renew];
    
    NSMutableArray *ret = [self dup_extend_datas];
    MURLHeaderField *seg = [[MURLHeaderField alloc] init];
    seg.mech = MURLHeaderFieldMechSet;
    seg.value = [self headerString];
    seg.field = @"Authorization";
    [ret addObject:seg];
    [seg release];
    return ret;
}

- (BOOL)process:(NSObject *)__result {
    ns::Dictionary dict((NSDictionary*)__result);
    self.error_code = dict[@"error_code"];
    self.error_msg = dict[@"error"];
    if (self.error_msg != nil) {
        return NO;
    }
    self.result = dict;
    return YES;
}

- (NSString*)url {
    NSMutableString* ret = [[NSMutableString alloc] initWithString:_url];
    [ret appendString:[self combineArguments:YES]];    
    return [ret autorelease];
}

- (NSString*)baseUrl {
    return _url;
}

- (BOOL)retrieve_sync {
    return [SERV() retrieve_model:self];
}

@end

@implementation OANullApi

@synthesize apiType = _apiType;

- (NSString*)combineArguments:(BOOL)isURL {
    NSMutableString* ret = [[NSMutableString alloc] init];
    NSArray* argus = self.params;
    
    for (uindex i = 0; i < argus.count; ++i) {
        NSPair* pair = (NSPair*)[argus objectAtIndex:i];
        
        if (isURL && ![self isUrlParameter:pair])
            continue;
        
        if (i == 0) {
            [ret appendString:@"?"];
        } else {
            [ret appendString:@"&"];
        }
        
        // append key value.
        if (pair.first == nil) {
            dthrow_msg(@"oauth::api", @"pass a nil argument as key.");
            pair.first = @"";
        }
        if (pair.second == nil) {
            dthrow_msg(@"oauth::api", @"pass a nil argument as value.");
            pair.first = @"";
        }
        
        [ret appendString:pair.first];
        [ret appendString:@"="];
        [ret appendString:pair.second];
        
    }

    return [ret autorelease];
}

- (BOOL)isUrlParameter:(NSPair*)obj {
    return YES;
}

@end

@implementation OAuth_1_0

@dynamic callback;
@synthesize isValid = _isValid;
@synthesize request = _request;

- (id)init {
    self = [super init];
    
    _isValid = NO;
    
    return self;
}

- (id)initFromData:(NSDictionary*)dict {
    self = [self init];
    if (NO == [self loadFrom:dict]) {
        [self release];
        return nil;
    }
    return self;
}

- (void)dealloc {
    safe_release(_request);
    safe_release(_authorize);
    safe_release(_access);

    [super dealloc];
}

//! name.
+ (NSString*)Name {
    return @"OAUTH";
}

+ (NSString*)UniqueIdentity {
    return @"d3bb50e6-1b1d-11e1-a292-af5ab6b7767f";
}

+ (UIImage*)LogoImage {
    return nil;
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAuthorizeSuccess)
NNTEVENT_SIGNAL(kSignalAuthorizeFailed)
NNTEVENT_END

- (NSString*)callback {
    return _authorize.urlCallback;
}

- (void)setCallback:(NSString *)callback {
    _authorize.urlCallback = callback;
}

- (void)retrieve {
    [self retain];
    
    if (NO == [SERV() retrieve_model:_request]) {
        return;
    }
    
    if (NO == [_authorize is_connected:kSignalAuthorizeSuccess sel:@selector(__act_authorize_suc:) obj:self]) {
        [_authorize connect:kSignalAuthorizeSuccess sel:@selector(__act_authorize_suc:) obj:self];
    }
    
    if (NO == [_authorize is_connected:kSignalAuthorizeFailed sel:@selector(__act_authorize_failed:) obj:self]) {
        [_authorize connect:kSignalAuthorizeFailed sel:@selector(__act_authorize_failed:) obj:self];
    }
    
    if (NO == [_authorize is_connected:kSignalAuthorizeExit sel:@selector(__act_exit) obj:self]) {
        [_authorize connect:kSignalAuthorizeExit sel:@selector(__act_exit) obj:self];
    }
    
    [_authorize performSelectorOnMainThread:@selector(go) withObject:nil waitUntilDone:YES];
}

- (void)__act_exit {
    safe_release(self);
}

- (void)__act_authorize_suc:(NNTEventObj*)evt {
    if (NO == [SERV() retrieve_model:_access]) {
        _isValid = NO;
        [self emit:kSignalAuthorizeFailed result:_request];
        return;
    }
    
    _isValid = YES;
    [self emit:kSignalAuthorizeSuccess result:_request];
}

- (void)__act_authorize_failed:(NNTEventObj*)evt {
    [self emit:kSignalAuthorizeFailed result:_request];
}

- (id)api:(NSString *)url cls:(Class)cls {
    if (_isValid == NO)
        return nil;
    OACommonApi_1_0* obj = [[cls alloc] initWithRequest:(id)_request];
    obj.url = url;
    return [obj autorelease];
}

- (id)api:(id)api {
    if ([api isKindOfClass:[OACommonApi_1_0 class]]) {
        ((OACommonApi_1_0*)api).request = _request;
        return api;
    }
    return nil;
}

# pragma mark redirect.

@dynamic user_id;

- (NSString*)user_id {
    return _request.user_id;
}

# pragma mark serial.

- (void)saveTo:(NSMutableDictionary*)__dict {
    ns::MutableDictionary dict(__dict);
    
    dict[@"::nnt::oauth::version"] = @"1.0";
    dict[@"::nnt::oauth::access_token"] = _request.access_token;
    dict[@"::nnt::oauth::access_token_secret"] = _request.access_token_secret;
    dict[@"::nnt::oauth::token"] = _request.token;
    dict[@"::nnt::oauth::token_secret"] = _request.token_secret;
    dict[@"::nnt::oauth::user_id"] = _request.user_id;
    dict[@"::nnt::oauth::verifier"] = _request.verifier;
}

- (BOOL)loadFrom:(NSDictionary*)__dict {
    ns::Dictionary dict(__dict);
    
    ns::String ver = dict[@"::nnt::oauth::version"];
    if (ver != ns::String(@"1.0"))
        return NO;
    
    _request.access_token = dict[@"::nnt::oauth::access_token"];
    _request.access_token_secret = dict[@"::nnt::oauth::access_token_secret"];
    _request.token = dict[@"::nnt::oauth::token"];
    _request.token_secret = dict[@"::nnt::oauth::token_secret"];
    _request.user_id = dict[@"::nnt::oauth::user_id"];
    _request.verifier = dict[@"::nnt::oauth::verifier"];
    
    return YES;
}

@end

@implementation OARequest_2_0

@synthesize clientId = _clientId, clientSecret = _clientSecret;
@synthesize responseType = _responseType, grantType = _grantType, code = _code, redirectUrl = _redirectUrl, redirectCancelUrl = _redirectCancelUrl;
@synthesize scopes = _scopes;
@synthesize access_token = _access_token;
@synthesize expires = _expires, remind = _remind, user_id = _user_id;

- (id)init {
    self = [super init];
    
    self.version = (version_t){2, 0, 0, "2.0"};
    self.redirectUrl = @"wsi://oauth/2.0/redirect";
    self.redirectCancelUrl = @"wsi://oauth/2.0/cancel";
    self.responseType = @"code";
    self.code = @"";
    self.user_id = @"";
    
    return self;
}

- (void)dealloc {
    safe_release(_clientId);
    safe_release(_clientSecret);
    safe_release(_responseType);
    safe_release(_grantType);
    safe_release(_code);
    safe_release(_redirectUrl);
    safe_release(_redirectCancelUrl);
    safe_release(_scopes);
    safe_release(_access_token);
    safe_release(_user_id);
    
    [super dealloc];
}

- (NSMutableArray*)scopes {
    NNT_SYNCHRONIZED(self)
    
    if (_scopes == nil)
        _scopes = [[NSMutableArray alloc] initWithCapacity:4];

    NNT_SYNCHRONIZED_END
    
    return _scopes;
}

- (void)generateParameters:(NSMutableDictionary*)__dict {
    ns::MutableDictionary dict(__dict);
    
    dict[@"client_id"] = self.clientId;    
    dict[@"redirect_uri"] = self.redirectUrl;
    dict[@"scope"] = (::nnt::ignore_null)[self generateScopes];
    
    // add params.
    for (NSPair* each in self.params) {
        if ([each isKindOfClass:[NSPair class]] == NO)
            continue;
        dict[each.first] = each.second;
    }
}

- (NSString*)generateScopes {
    if (_scopes.count == 0)
        return nil;
    NSString* str = [_scopes componentsJoinedByString:@","];
    return str;
}

@end

@implementation OAuthorize_2_0

@synthesize request = _request;
@synthesize expire = _expire;

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAuthorizeSuccess)
NNTEVENT_SIGNAL(kSignalAuthorizeFailed)
NNTEVENT_SIGNAL(kSignalAuthorizeExit)
NNTEVENT_END

- (id)initWithRequest:(OARequest_2_0 *)req {
    self = [super init];
    self.request = req;
    return self;
}

- (void)dealloc {
    zero_release(_request);
    [super dealloc];
}

- (BOOL)go {    
    if (self.request.redirectUrl == nil) {
        dthrow_msg(@"NULL", @"redirect url is NULL");
        return NO;
    }
    
    NNT_AUTORELEASEPOOL_BEGIN
    
    NSString* go_url = [self url];
    safe_release(_authView);
    _authView = [[self authView] retain];
    
    [self openAuthView:go_url];
    
    if ([_authView isKindOfClass:[UIOAuthView class]]) {
        UIOAuthView* view = (UIOAuthView*)_authView;
        if (view.buttonClose) {
            [view.buttonClose connect:kSignalButtonClicked sel:@selector(failed) obj:self];
        }
    }
    
    NNT_AUTORELEASEPOOL_END
    
    return YES;
}

- (id)authView {    
    UIOAuthView* authview = [[UIOAuthView alloc] initWithZero];
    
    // show close button.
    authview.showClose = YES;
    
    // connect cb.
    [authview registerFilter:kOAuthCallbackCancel type:UIWebViewFilterTypeStartLoad].shouldStartLoad = NO;
    [[authview connect:kOAuthCallbackCancel sel:@selector(act_callback:) obj:self] mainThread];
        
    return [authview autorelease];
}

- (void)openAuthView:(UIOAuthView*)authview url:(NSString*)url {
    [authview loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:url]]];
    [authview execute];
}

- (void)openAuthView:(NSString*)url {
    [_authView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:url]]];
    [_authView execute];
}

- (void)closeAuthView:(UIOAuthView*)authview {
    [authview close];
}

- (void)closeAuthView {
    [_authView close];
    zero_release(_authView);
}

- (void)success {
    // emit success.
    [self emit:kSignalAuthorizeSuccess result:self.request];
    
    // exit.
    [self emit:kSignalAuthorizeExit];
    
    // close auth view.
    [self closeAuthView];
}

- (void)failed {
    // emit failed.
    [self emit:kSignalAuthorizeFailed];
    
    // exit.
    [self emit:kSignalAuthorizeExit];
    
    // close auth view.
    [self closeAuthView];
}

- (void)act_callback:(NNTEventObj*)evt {
    NSString* callback = (NSString*)evt.result;        
    
    NSArray* arr_callback = [callback componentsSeparatedByString:@"?"];
    if ([arr_callback count] != 2) {
        if ([callback matchedByRegex:kOAuthCallbackCancel full:NO]) {            
            
            // close auth view.
            [self closeAuthView:(id)evt.sender];
            
            // failed.
            [self failed];                        
            return;
        }
# ifdef NNT_DEBUG
        trace_fmt(@"skip callback: %@", callback);
# endif
        return;
    }
}

- (NSString*)url {
    ns::MutableDictionary dict;

    dict[@"response_type"] = [self.request.responseType OAEncode];

    [self.request generateParameters:dict];
    
    NSString *ret = nil;
    
    if ([self.request.urlAuthorize rangeOfString:@"?"].location == NSNotFound)
        ret = self.request.urlAuthorize + ns::String(@"?");
    else
        ret = self.request.urlAuthorize + ns::String(@"&");
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

@end

@implementation OAccess_2_0

@synthesize request = _request;
@synthesize authorize = _authorize;

- (id)init {
    self = [super init];
    
    OAuthParser *parser = [[OAuthParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    self.classRpc = [HttpRequest_Post class];
    
    return self;
}

- (id)initWithRequest:(OARequest_2_0 *)req withAuth:(OAuthorize_2_0*)auth {
    self = [self init];
    
    self.request = req;
    self.authorize = auth;
    
    return self;
}

- (NSString*)url {
    NSString* ret = self.request.urlAccess;
    NSString* str_params = [NSURL combineArguments:self.params];
    if (str_params) {
        if ([ret rangeOfString:@"?"].location == NSNotFound)
            ret = ret + ns::String(@"?");
        else
            ret = ret + ns::String(@"&");
        ret = ret + ns::String(str_params);
    }
    return ret;
}

@end

@implementation OAuth_2_0

@synthesize request = _request;
@synthesize isValid = _isValid;

- (id)init {
    self = [super init];
    
    _isValid = NO;
    
    return self;
}

- (void)dealloc {    
    safe_release(_request);
    safe_release(_authorize);
    safe_release(_access);

    [super dealloc];
}

- (id)initFromData:(NSDictionary*)dict {
    self = [self init];
    if (NO == [self loadFrom:dict]) {
        [self release];
        return nil;
    }
    return self;
}

//! name.
+ (NSString*)Name {
    
    return @"OAUTH2";
}

+ (NSString*)UniqueIdentity {
    return @"C9F47128-5571-47AE-9437-9781623ABE00";
}

+ (UIImage*)LogoImage {
    return nil;
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAuthorizeSuccess)
NNTEVENT_SIGNAL(kSignalAuthorizeFailed)
NNTEVENT_END

//! retrieve from server.
- (void)retrieve {    
    [self retain];
    
    if (NO == [_authorize is_connected:kSignalAuthorizeSuccess sel:@selector(__act_authorize_suc:) obj:self]) {
        [_authorize connect:kSignalAuthorizeSuccess sel:@selector(__act_authorize_suc:) obj:self];
    }
    
    if (NO == [_authorize is_connected:kSignalAuthorizeFailed sel:@selector(__act_authorize_failed:) obj:self]) {
        [_authorize connect:kSignalAuthorizeFailed sel:@selector(__act_authorize_failed:) obj:self];
    }
    
    if (NO == [_authorize is_connected:kSignalAuthorizeExit sel:@selector(__act_exit) obj:self]) {
        [_authorize connect:kSignalAuthorizeExit sel:@selector(__act_exit) obj:self];
    }
    
    [_authorize performSelectorOnMainThread:@selector(go) withObject:nil waitUntilDone:YES];
}

- (void)__act_exit {
    safe_release(self);
}

- (void)__act_authorize_suc:(NNTEventObj*)evt {
    // check if access needed.
    if (self.request.urlAccess) {
        if (NO == [SERV() retrieve_model:_access]) {
            _isValid = NO;
            [self emit:kSignalAuthorizeFailed result:_request];
            return;
        }
    }
    
    _isValid = YES;
    [self emit:kSignalAuthorizeSuccess result:_request];
}

- (void)__act_authorize_failed:(NNTEventObj*)evt {
    [self emit:kSignalAuthorizeFailed result:_request];
}

// serial.
- (void)saveTo:(NSMutableDictionary*)__dict {
    ns::MutableDictionary dict(__dict);
    
    dict[@"::nnt::oauth::version"] = @"2.0";
    dict[@"::nnt::oauth::access_token"] = _request.access_token;
    dict[@"::nnt::oauth::code"] = _request.code;
    dict[@"::nnt::oauth::user_id"] = _request.user_id;
    dict[@"::nnt::oauth::remind"] = tostr(_request.remind);
    dict[@"::nnt::oauth::expire"] = tostr(_request.expires);
    
}

- (BOOL)loadFrom:(NSDictionary*)__dict {
    ns::Dictionary dict(__dict);
    
    ns::String ver = dict[@"::nnt::oauth::version"];
    if (ver != ns::String(@"2.0"))
        return NO;
    
    _request.access_token = dict[@"::nnt::oauth::access_token"];
    _request.code = dict[@"::nnt::oauth::code"];
    _request.user_id = dict[@"::nnt::oauth::user_id"];
    _request.remind = core::touint(dict[@"::nnt::oauth::remind"]);
    _request.expires = core::touint(dict[@"::nnt::oauth::expire"]);
    
    return YES;
}

@end

@implementation OACommonApi_2_0

@synthesize request = _request;

- (id)init {
    self = [super init];
    
    self.version = (version_t){2, 0, 0, "2.0"};
    
    OACommonApiParser *parser = [[OACommonApiParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    self.classRpc = [HttpRequest_Post class];
    
    return self;
}

- (id)initWithRequest:(OARequest_2_0 *)req {
    self = [self init];
    
    self.request = req;
    
    return self;
}

- (id)initWithOAuth:(OAuth_2_0*)auth {
    self = [self initWithRequest:auth.request];    
    return self;
}

- (void)dealloc {
    safe_release(_request);

    [super dealloc];
}

- (BOOL)process:(NSObject *)__result {
    ns::Dictionary dict((NSDictionary*)__result);
    self.error_code = dict[@"error_code"];
    self.error_msg = dict[@"error"];
    if (self.error_msg != nil) {
        return NO;
    }
    self.result = dict;
    return YES;
}

- (NSString*)url {
    NSMutableString* ret = [[NSMutableString alloc] initWithString:_url];
    [ret appendString:[self combineArguments:YES]];
    return [ret autorelease];
}

- (NSMutableArray*)get_params {
    return [self dup_params];
}

- (NSString*)baseUrl {
    return _url;
}

- (BOOL)retrieve_sync {
    return [SERV() retrieve_model:self];
}

@end

NNT_END_OBJC