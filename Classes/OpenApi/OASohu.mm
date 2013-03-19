
# import "Core.h"
# import "OASohu.h"
# import "OAuthParser.h"
# import "HttpRequest.h"
# import "UIOAuthView.h"
# import "OADefines.h"
# import "../UIKit/UIOAToggleView.res"

WSI_BEGIN_OBJC

@implementation OARequestSohu

- (id)init {
    
    self = [super init];
    self.urlRequest = @"http://api.t.sohu.com/oauth/request_token";
    self.urlAuthorize = @"http://api.t.sohu.com/oauth/authorize";
    self.urlAccess = @"http://api.t.sohu.com/oauth/access_token";
    
    self.appKey = OA_SOHU_APPKEY;
    self.appSecret = OA_SOHU_APPSECRET;
    
    self.signature = (sec_signature_func_t){ signature_hmac_sha1_name, signature_hmac_sha1 };
    self.version = (version_t){ 1, 0, 0, "1.0"};
    
    self.classRpc = [HttpRequest_Get class];
    return self;
}

- (void)renew {
    
    [super renew];
    self.nonce = kNSStringNonceSimple();
}

- (void)generateParameters:(NSMutableDictionary *)__dict {
    
    wsi::ns::MutableDictionary dict(__dict);
    dict[@"oauth_consumer_key"] = [self.appKey OAEncode];
    dict[@"oauth_nonce"] = [self.nonce OAEncode];
    dict[@"oauth_signature_method"] = [self.signature.method_name() OAEncode];
    dict[@"oauth_timestamp"] = self.timestamp;
    dict[@"oauth_version"] = [NSString stringWithUTF8String:self.version.ver];
}

- (NSString*)baseString {
    
    wsi::ns::MutableDictionary dict;
    dict[@"oauth_callback"] = [@"null" OAEncode];
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.urlRequest OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
#ifdef WSI_DEBUG
    trace_obj(ret);
#endif
    
    return ret;
}

- (NSMutableArray*)get_extend_datas {
    
    return nil;
}

- (NSString*)url {
    
    [self renew];
    
    NSString *str_base = [self baseString];
    
    NSString* str_secret = [NSString stringWithFormat:@"%@&", [self.appSecret OAEncode]];
    NSString* str_signed = [self signatureString:str_base secret:str_secret];
    
    wsi::ns::MutableDictionary dict;
    dict[@"oauth_signature"] = [str_signed OAEncode]; 
    dict[@"oauth_callback"] = [@"null" OAEncode];
    
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.urlRequest];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
#ifdef WSI_DEBUG
    trace_obj(ret);
#endif
    
    return ret;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

@end

@implementation OAuthorizeSohu

- (id)authView {
    UIOAuthView *authview = (UIOAuthView *)[super authView];
    authview.showClose = YES;
    return authview;
}

@end

@implementation OAccessSohu

- (NSString*)baseString {
    
    wsi::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_verifier"] = self.request.verifier;
    dict[@"oauth_token"] = self.request.token;
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.request.urlAccess OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSString*)headerString {
    
    return nil;
}

- (NSMutableArray*)get_extend_datas {
    return nil;
}

- (NSString*)url {
    
    [self.request renew];
    
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", [self.request.appSecret OAEncode], [self.request.token_secret OAEncode]];
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    
    wsi::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_verifier"] = self.request.verifier;
    dict[@"oauth_token"] = self.request.token;
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.request.urlAccess];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

- (BOOL)process:(NSObject *)__result {
    wsi::ns::MutableDictionary dict((NSMutableDictionary*)__result);
    self.request.access_token = dict[@"oauth_token"];
    self.request.access_token_secret = dict[@"oauth_token_secret"];
    return YES;
}

@end

@implementation OASohu

- (id)init {
    
    self = [super init];
    
    _request = [[OARequestSohu alloc] init];
    _authorize = [[OAuthorizeSohu alloc] initWithRequest:_request];
    _access = [[OAccessSohu alloc] initWithRequest:_request withAuth:_authorize];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)saveTo:(NSMutableDictionary*)__dict {
    wsi::ns::MutableDictionary dict(__dict);
    dict[@"::oauth::access_token"] = _request.access_token;
    dict[@"::oauth::access_token_secret"] = _request.access_token_secret;
    dict[@"::oauth::token"] = _request.token;
    dict[@"::oauth::token_secret"] = _request.token_secret;
    dict[@"::oauth::verifier"] = _request.verifier;
}

+ (NSString *)Name {
    return _W(@"SOHU MBLOG");
}

+ (NSString *)UniqueIdentity {
    return @"E7B9E9D3-96ED-4096-97A6-61713AE7FE9A";
}

+ (UIImage*)LogoImage {    
    WCGImage* imgRes = WCGImageLoadPngData(sohu_mblog, sizeof(sohu_mblog));
    return [UIImage imageWithCGImage:imgRes.image];
}

@end

@interface OASohuJsonParser : OAJsonParser @end

@implementation OASohuJsonParser

- (NSData*)parse_todata:(NSObject *)__obj {    
    NSString* str = [NSURL combineArguments:(NSArray*)__obj];
    return [str dataUsingEncoding:NSUTF8StringEncoding];
}

@end

@interface OASohuXmlParser : OAXmlParser @end

@implementation OASohuXmlParser

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end

@implementation OApiSohu

@synthesize sohu_params = _sohu_params;

- (id)init{
    
    self = [super init];
    self.version = (version_t){1, 0, 0, "1.0"};
    _sohu_params = [NSMutableArray new];
    return self;
}

- (void)dealloc {
    [_sohu_params release];
    [super dealloc];
}

- (void)setApiType:(OAuthApiType)type {
    if (_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser* parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {  
            self.url = [_url stringByAppendingString:@".json"];
            parser = [[OAJsonParser alloc] init];
        } break;
        case OAuthApiTypeXML: {     
            self.url = [_url stringByAppendingFormat:@".xml"];
            parser = [[OAXmlParser alloc] init];
        } break;
    }
    
    self.objparser = parser;
    safe_release(parser);
}

- (NSString*)baseString {
    wsi::ns::MutableDictionary dict;
    
    // base params.
    [self.request generateParameters:dict];
    dict[@"oauth_token"] = self.request.access_token;
    
    // params.
    for (NSPair *each in self.sohu_params) {
        dict[each.first] = [[each.second OAEncode] OAEncode];
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.baseUrl OAEncode]];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
# ifdef WSI_DEBUG
    trace_msg(ret);
# endif
    
    return ret;
}

- (NSString*)headerString {
    
    return nil;
}

- (NSMutableArray*)get_extend_datas {
    
    return nil;
}

- (NSString*)url {
    
    [self.request renew];
    
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", [self.request.appSecret OAEncode], [self.request.access_token_secret OAEncode]];
    
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    
    wsi::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_token"] = self.request.access_token;
    
    // params.
    for (NSPair *each in self.sohu_params) {
        dict[each.first] = [each.second OAEncode];
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.baseUrl];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@""]];
    
# ifdef WSI_DEBUG
    trace_msg(ret);
# endif
    
    return ret;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

- (NSMutableArray*)get_params {
    
    wsi::ns::MutableArray arr([self dup_params]);
    
    for (NSPair *each in self.sohu_params) {
        arr << pair(each.first, [each.second OAEncode]);
    }
    
    return arr;
}

@end

@implementation OApiSohuUserInfo

- (id)init {
    
    self = [super init];
    self.url = @"http://api.t.sohu.com/users/show";
    self.classRpc = [HttpRequest_Get class];
    return self;
}

- (NSMutableArray*)get_sohu_params {
    
    wsi::ns::MutableArray arr([super get_sohu_params]);
    return arr;
}

@end

@interface OApiSohuPost () 

@property (nonatomic, retain) NSMutableArray* arr_params;

@end

@implementation OApiSohuPost

@synthesize content;
@synthesize arr_params;

- (id)init {
    self = [super init];
    
    self.url = @"http://api.t.sohu.com/statuses/update";
    self.classRpc = [HttpRequest_Post class];
    
    return self;
}

- (void)dealloc {    
    [content release];
    [arr_params release];
    [super dealloc];
}

- (void)setApiType:(OAuthApiType)type {
    if (_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser* parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {
            self.url = [_url stringByAppendingString:@".json"];
            parser = [[OASohuJsonParser alloc] init];
        } break;
        case OAuthApiTypeXML: {
            self.url = [_url stringByAppendingFormat:@".xml"];
            parser = [[OASohuXmlParser alloc] init];
        } break;
    }
    
    self.objparser = parser;
    safe_release(parser);
}

- (NSMutableArray*)get_sohu_params {
    wsi::ns::MutableArray arr;
    arr << pair(@"status", content);
    return arr.consign();
}

- (NSMutableArray*)get_params {
    return arr_params;
}

- (NSMutableArray*)get_extend_datas {
    wsi::ns::MutableArray arr([self dup_extend_datas]);
    arr << [Model SetHttpHeaderValue:@"api.t.sohu.com" forField:@"HTTP/1.0 Host"];
    return arr;
}

- (void)body_params{
    
    [self.request renew];
    
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", [self.request.appSecret OAEncode], [self.request.access_token_secret OAEncode]];
    
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    
    wsi::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_token"] = self.request.access_token;
    
    // params.
    for (NSPair *each in self.sohu_params) {
        dict[each.first] = [each.second OAEncode];
    }
    
    NSDictionary *tmp_dict = dict;
    wsi::ns::MutableArray arr;
    for (id each in tmp_dict) {
        arr << pair(each, [tmp_dict valueForKey:each]);
    }
    arr_params = [[NSMutableArray alloc] initWithArray:arr];
}

- (NSString*)url {    
    [self body_params];
    return _url;
}

@end

WSI_END_OBJC
