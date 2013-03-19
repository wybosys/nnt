
# import "Core.h"
# import "OATencent.h"
# import "OAuthParser.h"
# import "HttpRequest.h"
# import "UIOAuthView.h"
# import "OADefines.h"
# import "../UIKit/UIOAToggleView.res"

WSI_BEGIN_OBJC

@implementation OARequestTencent

@synthesize urlCallback;

- (id)init {    
    self = [super init];
    
    self.urlRequest = @"https://open.t.qq.com/cgi-bin/request_token";
    self.urlAuthorize = @"https://open.t.qq.com/cgi-bin/authorize";
    self.urlAccess = @"https://open.t.qq.com/cgi-bin/access_token";
    
    self.appKey = OA_TENCENT_OPENWEIBO_APPKEY;
    self.appSecret = OA_TENCENT_OPENWEIBO_APPSECRET;
    
    self.signature = (sec_signature_func_t){ signature_hmac_sha1_name, signature_hmac_sha1 };
    
    self.version = (version_t){1, 0, 0, "1.0"};
    
    self.urlCallback = @"null";
    
    return self;
}

- (void)dealloc {
    
    [urlCallback release];
    [super dealloc];
}

- (void)renew {
    
    [super renew];
    self.nonce = kNSStringNonceSimple();
}

- (NSString*)baseString {
    
    wsi::ns::MutableDictionary dict;
    dict[@"oauth_callback"] = [urlCallback OAEncode];
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.urlRequest OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSString*)headerString {
    
    return nil;
}

- (void)generateParameters:(NSMutableDictionary *)__dict {
    
    wsi::ns::MutableDictionary dict(__dict);
    dict[@"oauth_consumer_key"] = [self.appKey OAEncode];
    dict[@"oauth_nonce"] = [self.nonce OAEncode];
    dict[@"oauth_signature_method"] = [self.signature.method_name() OAEncode];
    dict[@"oauth_timestamp"] = self.timestamp;
    dict[@"oauth_version"] = [NSString stringWithUTF8String:self.version.ver];
}

- (NSMutableArray*)get_extend_datas {
    return nil;
}

- (NSString*)url {

    [self renew];
    
    NSString *str_base = [self baseString];
    
    NSString* str_secret = [NSString stringWithFormat:@"%@&", self.appSecret];
    NSString* str_signed = [self signatureString:str_base secret:str_secret];
    
    wsi::ns::MutableDictionary dict;
    dict[@"oauth_callback"] = [urlCallback OAEncode];
    dict[@"oauth_signature"] = [str_signed OAEncode]; 
    
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.urlRequest];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

@end

@implementation OAuthorizeTencent

- (id) authView {     
    UIOAuthView* authview = (UIOAuthView*)[super authView];
    authview.title.text = [OATencent Name];

    [authview.web enableJQuery];
    [authview.web.additionalJavascript addObject:@"$('#refuse_btn').attr('onclick', 'window.open(\"::oauth::cancel\")');"];
    
    [authview registerFilter:@"&v=" signal:@"authorize_success" type:UIWebViewFilterTypeStartLoad].shouldStartLoad = NO;
    
    [authview connect:@"authorize_success" sel:@selector(act_authorize_success:) obj:self];
    
    return authview;
}

- (void)act_authorize_success:(WSIEventObj*)evt {
    
    NSString *verifier = [self valueForKey:@"v" ofQuery:evt.result];
    wsi::ns::MutableDictionary dict_result;
    dict_result[@"oauth_verifier"] = verifier;
    
    self.request.verifier = dict_result[@"oauth_verifier"];
        
    // send success.
    [self success];        
}

- (NSString*)valueForKey:(NSString *)key ofQuery:(NSString*)query {
	NSArray *pairs = [query componentsSeparatedByString:@"&"];
	for(NSString *aPair in pairs){
		NSArray *keyAndValue = [aPair componentsSeparatedByString:@"="];
		if([keyAndValue count] != 2) continue;
		if([[keyAndValue objectAtIndex:0] isEqualToString:key]){
			return [keyAndValue objectAtIndex:1];
		}
	}
	return nil;
}

@end

@implementation OAccessTencent

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
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", self.request.appSecret, self.request.token_secret];
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

@implementation OATencent

- (id)init {
    
    self = [super init];
    
    _request = [[OARequestTencent alloc] init];
    _authorize = [[OAuthorizeTencent alloc] initWithRequest:_request];
    _access = [[OAccessTencent alloc] initWithRequest:_request withAuth:_authorize];
    
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

+ (NSString*)Name {
    return _W(@"TENCENT OPEN");
}

+ (NSString*)UniqueIdentity {
    return @"1f87d922-1b1e-11e1-9478-078f9fc13ff4";
}

@end

@implementation OATencentWeibo

+ (NSString*)Name {
    return _W(@"TENCENT MBLOG");
}

+ (NSString*)UniqueIdentity {
    return @"23f3fbd8-1d5a-11e1-b924-272a83edcb76";
}

+ (UIImage*)LogoImage {    
    WCGImage* imgRes = WCGImageLoadPngData(tencent_mblog, sizeof(tencent_mblog));
    return [UIImage imageWithCGImage:imgRes.image];
}

@end

@implementation OApiTencentQQ

@synthesize str_apiType;
@synthesize tencent_params = _tencent_params;

- (id) init {
    
    self = [super init];
    _tencent_params = [NSMutableArray new];
    return self;
}

- (void)dealloc {
    
    [str_apiType release];
    [_tencent_params release];
    [super dealloc];
}

- (void)setApiType:(OAuthApiType)type {
    if (_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser* parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {            
            self.str_apiType = @"json";
            parser = [[OAJsonParser alloc] init];
        } break;
        case OAuthApiTypeXML: {            
            self.str_apiType = @"xml";
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
    for (NSPair *each in self.tencent_params) {
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
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", self.request.appSecret, self.request.access_token_secret];
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    
    wsi::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    
    dict[@"oauth_token"] = self.request.access_token;

    // params.
    for (NSPair *each in self.tencent_params) {
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

- (BOOL)process:(NSObject *)__result {
    wsi::ns::Dictionary dict((NSDictionary*)__result);
    NSNumber* code = dict[@"ret"];
    self.error_msg = dict[@"msg"];
    if ([code intValue] != 0) {
        return NO;
    }
    self.result = dict[@"data"];
    return YES;
}

- (NSMutableArray*)get_tencent_params {
    wsi::ns::MutableArray arr;
    arr << pair(@"format", str_apiType);
    return arr.consign();
}

- (NSMutableArray*)get_params {
    
    wsi::ns::MutableArray arr([self dup_params]);
    
    for (NSPair *each in self.tencent_params) {
        arr << pair(each.first, [each.second OAEncode]);
    }
    
    return arr;
}

@end

@implementation OApiTencentUserInfo

- (id)init {
    
    self = [super init];
    self.url = @"http://open.t.qq.com/api/user/info";
    return self;
}

@end

@implementation OApiTencentWeiboPost

@synthesize content, clientip;
@synthesize jing, wei;

- (id)init {
    
    self = [super init];
    self.url = @"http://open.t.qq.com/api/t/add";
    self.cacheUpdate = YES;
    return self;
}

- (void)dealloc {
    
    [content release];
    [clientip release];
    [jing release];
    [wei release];
    [super dealloc];
}

- (NSMutableArray*)get_tencent_params {
    
    wsi::ns::MutableArray arr([super get_tencent_params]);
    arr << pair(@"content", content);
    
    if (clientip != nil) 
        arr << pair(@"clientip", clientip);
    
    if (jing)
        arr << pair(@"jing", jing);
    
    if (wei)
        arr<< pair(@"wei", wei);
    return arr;
}

@end

@implementation OApiTencentWeiboShow

@synthesize id;

- (id)init {
    self = [super init];
    self.url = @"http://open.t.qq.com/api/t/show";
    return self;
}

- (void)dealloc {
    
    [id release];
    [super dealloc];
}

- (NSMutableArray*)get_tencent_params {
    
    wsi::ns::MutableArray arr([super get_tencent_params]);
    arr << pair(@"id", id);
    return arr;
}

@end

WSI_END_OBJC