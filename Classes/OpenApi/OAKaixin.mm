
# import "Core.h"
# import "OAKaixin.h"
# import "OAuthParser.h"
# import "HttpRequest.h"
# import "UIOAuthView.h"
# import "OADefines.h"
# import "../UIKit/UIOAToggleView.res"

NNT_BEGIN_OBJC

@implementation OARequestKaixin

@synthesize urlCallback;

- (id)init {    
    self = [super init];
    
    self.urlRequest = @"http://api.kaixin001.com/oauth/request_token";
    self.urlAuthorize = @"http://api.kaixin001.com/oauth/authorize";
    self.urlAccess = @"http://api.kaixin001.com/oauth/access_token";
    
    self.appKey = OA_KAIXIN_APPKEY;
    self.appSecret = OA_KAIXIN_APPSECRET;
    
    self.signature = (sec_signature_func_t){ signature_hmac_sha1_name, signature_hmac_sha1 };
    
    self.version = (version_t){1, 0, 0, "1.0"};
    
    self.classRpc = [HttpRequest_Get class];
    
    self.cacheUpdate = YES;
    
    return self;
}

- (void)renew {
    
    [super renew];
    self.nonce = [NSString stringWithFormat:@"%u", arc4random() % (9999999 - 123400) + 123400];
}

- (NSString*)baseString {
    
    wsi::ns::MutableDictionary dict;

    dict[@"oauth_callback"] = [@"oob" OAEncode];
    dict[@"scope"] = @"create_diary";
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
    
    dict[@"oauth_callback"] = [@"oob" OAEncode]; 
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"scope"] = @"create_diary";
    
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.urlRequest];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

@end

@implementation OAuthorizeKaixin

- (id)authView {
    UIOAuthView *authview = (UIOAuthView *)[super authView];
    authview.title.text = [OAKaixin Name];
    
    [authview.web enableJQuery];
    authview.showClose = YES;
    [authview.web.additionalJavascript addObject:@"$('.gb1-12').attr('onclick', 'window.open(\"::oauth::cancel\")');"];
    
    [authview registerFilter:@"你获取到的授权码是：<b>(\\w+)<" signal:@"authorize_success"  type:UIWebViewFilterTypeLoaded].shouldStartLoad = NO;
    [authview connect:@"authorize_success" sel:@selector(act_authorize_success:) obj:self];
    
    return authview;
}

- (void)act_authorize_success:(NNTEventObj *)evt {
    UIOAuthView *authview = (UIOAuthView *)evt.sender;
    NSString *str = authview.web.content;
    NSArray *arr = [str captureComponentsMatchedByRegex:@"你获取到的授权码是：<b>(\\w+)<"];
    self.request.verifier = [arr objectAtIndex:1];
    [self success];
}

@end

@implementation OAccessKaixin

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

@implementation OAKaixin

- (id)init {    
    self = [super init];
    
    _request = [[OARequestKaixin alloc] init];
    _authorize = [[OAuthorizeKaixin alloc] initWithRequest:_request];
    _access = [[OAccessKaixin alloc] initWithRequest:_request withAuth:_authorize];
    
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
    return _W(@"KAIXIN");
}

+ (NSString*)UniqueIdentity {
    return @"C24ED9F3-997E-45E2-A9D8-DD5DA3C5598E";
}

+ (UIImage*)LogoImage {    
    WCGImage* imgRes = WCGImageLoadPngData(kaixin_mblog, sizeof(kaixin_mblog));
    return [UIImage imageWithCGImage:imgRes.image];
}

@end


@interface OAKaixinJsonParser : OAJsonParser
@end

@implementation OAKaixinJsonParser

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end

@interface OAKaixinXmlParser : OAXmlParser 
@end

@implementation OAKaixinXmlParser

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end



@implementation OApiKaixin

@synthesize str_apiType;
@synthesize kaixin_params = _kaixin_params;

- (id) init {    
    self = [super init];
    _kaixin_params = [NSMutableArray new];
    return self;
}

- (void)dealloc {    
    [str_apiType release];
    [_kaixin_params release];
    [super dealloc];
}

- (void)setApiType:(OAuthApiType)type {
    if (_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser* parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {            
            self.str_apiType = @".json";
            parser = [[OAKaixinJsonParser alloc] init];
        } break;
        case OAuthApiTypeXML: {            
            self.str_apiType = @".xml";
            parser = [[OAKaixinXmlParser alloc] init];
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
    for (NSPair *each in self.kaixin_params) {
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
    for (NSPair *each in self.kaixin_params) {
        dict[each.first] = [each.second OAEncode];
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.baseUrl];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@""]];
    
# ifdef NNT_DEBUG
    trace_msg(ret);
# endif
    
    return ret;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

- (BOOL)process:(NSObject *)__result {
    wsi::ns::Dictionary dict((NSDictionary*)__result);
    NSNumber* code = dict[@"error_code"];
    self.error_msg = dict[@"error"];
    if ([code intValue] != 0) {
        return NO;
    }
    self.result = dict[@"data"];
    return YES;
}

- (NSMutableArray*)get_params {
    
    wsi::ns::MutableArray arr([self dup_params]);
    
    for (NSPair *each in self.kaixin_params) {
        arr << pair(each.first, [each.second OAEncode]);
    }
    
    return arr;
}

@end

@implementation OApiKaixinUserInfo

- (id)init {
    
    self = [super init];
    self.url = @"http://api.kaixin001.com/users/me";
    self.classRpc = [HttpRequest_Get class];
    return self;
}

@end

@implementation OApiKaixinDiaryPost

@synthesize content;
@synthesize title;

- (id)init {
    
    self = [super init];
    self.url = @"http://api.kaixin001.com/diary/create";
    return self;
}

- (void)dealloc {
    
    [content release];
    [title release];
    [super dealloc];
}

- (NSMutableArray*)get_kaixin_params {
    
    wsi::ns::MutableArray arr([super dup_params]);
    arr << pair(@"scope", @"create_diary");
    arr << pair(@"content", content);
    arr << pair(@"title", title);
    
    return arr;
}

@end

NNT_END_OBJC
