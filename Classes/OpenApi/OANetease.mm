
# import "Core.h"
# import "OANetease.h"
# import "OAuthParser.h"
# import "HttpRequest.h"
# import "UIOAuthView.h"
# import "OADefines.h"
# import "../UIKit/UIOAToggleView.res"

using namespace ::wsi;

NNT_BEGIN_OBJC

@implementation OARequestNetease

@synthesize urlCallback;

- (id)init {
    self = [super init];
    
    self.urlRequest = @"http://api.t.163.com/oauth/request_token";
    self.urlAuthorize = @"http://api.t.163.com/oauth/authorize";
    self.urlAccess = @"http://api.t.163.com/oauth/access_token";
    
    self.appKey = OA_NETEASE_APPKEY;
    self.appSecret = OA_NETEASE_APPSECRET;
    
    self.signature = (sec_signature_func_t){ signature_hmac_sha1_name,signature_hmac_sha1 };
    self.version = (version_t){ 1, 0, 0, "1.0"};
    self.urlCallback = @"null";
    
    self.classRpc = [HttpRequest_Get class];
    
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


- (NSString *)baseString {
    
    ns::MutableDictionary dict;
    dict[@"oauth_callback"] = [urlCallback OAEncode];
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.urlRequest OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSString *)headerString {
    return nil;
}

- (void)generateParameters:(NSMutableDictionary *)__dict {
    
    ns::MutableDictionary dict(__dict);
    dict[@"oauth_consumer_key"] = [self.appKey OAEncode];
    dict[@"oauth_nonce"] = [self.nonce OAEncode];
    dict[@"oauth_signature_method"] = [self.signature.method_name() OAEncode];
    dict[@"oauth_timestamp"] = self.timestamp;
    dict[@"oauth_version"] = [NSString stringWithUTF8String:self.version.ver];
}

- (NSMutableArray *)get_extend_datas {
    return nil;
}

- (NSString *)url {
    
    [self renew];
    NSString *str_base = [self baseString];
    NSString *str_secret = [NSString stringWithFormat:@"%@&", self.appSecret];
    NSString *str_signed = [self signatureString:str_base secret:str_secret];
    
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

@implementation OAuthorizeNetease

- (id)authView {
    UIOAuthView* authview = (UIOAuthView *)[super authView];
    authview.title.text = [OANetease Name];
    
    [authview registerFilter:@"id=\"verifier\">(\\w+)<" signal:@"authorize_success"  type:UIWebViewFilterTypeLoaded];
    [authview connect:@"authorize_success" sel:@selector(act_authorize_success:) obj:self];
    
    return authview;
}

- (void)act_authorize_success:(NNTEventObj *)evt {
    UIOAuthView *authview = (UIOAuthView *)evt.sender;
    
    NSString *str = authview.web.content;
    NSArray *arr = [str captureComponentsMatchedByRegex:@"id=\"verifier\">(\\w+)<"];
    self.request.verifier = [arr objectAtIndex:1];
    
    [self success];
}


@end

@implementation OAccessNetease

- (NSString *)baseString {
    
    ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_verifier"] = self.request.verifier;
    dict[@"oauth_token"] = self.request.token;
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&",HttpRequestGetMethod(self.classRpc),[self.request.urlAccess OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSString *)headerString {
    return nil;
}

- (NSMutableArray*)get_extend_datas {
    return nil;
}


- (NSString *)url {
    
    [self.request renew];
    NSString *str_base = [self baseString];
    NSString *str_secret = [NSString stringWithFormat:@"%@&%@", self.request.appSecret, self.request.token_secret];
    NSString *str_signed = [self.request signatureString:str_base secret:str_secret];
    
    ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_verifier"] = self.request.verifier;
    dict[@"oauth_token"] = self.request.token;
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.request.urlAccess];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSURL *)get_url {
    return [NSURL URLWithString:self.url];
}

- (BOOL)process:(NSObject *)__result {
    ns::MutableDictionary dict((NSMutableDictionary *)__result);
    self.request.access_token = dict[@"oauth_token"];
    self.request.access_token_secret = dict[@"oauth_token_secret"];
    return YES;
}


@end

@implementation OANetease

- (id)init {
    self = [super init];
    
    _request = [[OARequestNetease alloc] init];
    _authorize = [[OAuthorizeNetease alloc] initWithRequest:_request];
    _access = [[OAccessNetease alloc] initWithRequest:_request withAuth:_authorize];
   
    return self;
}

+ (NSString *)Name {
    return _W(@"NETEASE OPEN");
}

+ (NSString *)UniqueIdentity {
    return @"4A28F8A5-C696-45E6-A6B5-0B30E4097979";
}

@end

@implementation OANeteaseWeibo

+ (NSString *)Name {
    return _W(@"NETEASE MBLOG");
}

+ (NSString *)UniqueIdentity {
    return @"6d60939e-1d5a-11e1-a4ac-5f16cecb4ab2";
}

+ (UIImage*)LogoImage {    
    WCGImage* imgRes = WCGImageLoadPngData(netease_mblog, sizeof(netease_mblog));
    return [UIImage imageWithCGImage:imgRes.image];
}

@end

@implementation OApiNetease

- (id)init {
    self = [super init];
    return self;
}

- (void)setApiType:(OAuthApiType)type {
    if(_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser *parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {
            self.url = [_url stringByAppendingString:@".json"];
            parser = [[OAJsonParser alloc] init];
        }break;
        case OAuthApiTypeXML: {
            self.url = [_url stringByAppendingString:@".xml"];
            parser = [[OAJsonParser alloc] init];
        }break;
    }
    
    self.objparser = parser;
    safe_release(parser);
}

- (NSString *)baseString {
    ns::MutableDictionary dict;
    
    // base params.
    [self.request generateParameters:dict];
    dict[@"oauth_token"] = self.request.access_token;
    
    // params.
    for (NSPair *each in self.params) {
        if (![self isUrlParameter:each])
            continue;
        
        dict[each.first] = [[each.second OAEncode] OAEncode];
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.baseUrl OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSMutableArray *)get_extend_datas {
    
    return nil;
}

- (NSString *)url {
    
    [self.request renew];
    
    NSString *str_base = [self baseString];
    NSString *str_secret = [NSString stringWithFormat:@"%@&%@", self.request.appSecret, self.request.access_token_secret];
    NSString *str_signed = [self.request signatureString:str_base secret:str_secret];
    
    wsi::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_token"] = self.request.access_token;
    
    // params.
    for (NSPair *each in self.params) {
        if (![self isUrlParameter:each])
            continue;
        
        dict[each.first] = [each.second OAEncode];
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.baseUrl];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSURL *)get_url {
    return [NSURL URLWithString:self.url];
}

- (BOOL)process:(NSDictionary *)res {
    ns::Dictionary dict(res);
    
    self.result = dict;
    
    return YES;
}

@end

@implementation OApiNetUserInfo

- (id)init {
    self = [super init];
    
    self.url = @"http://api.t.163.com/users/show";
    self.classRpc = [HttpRequest_Get class];
    
    return self;
}

@end

@implementation OApiNeteaseWeiboPost

@synthesize content;

- (id)init {
    self = [super init];
    
    self.url = @"http://api.t.163.com/statuses/update";
    self.classRpc = [HttpRequest_Post class];
    self.cacheUpdate = YES;
    
    return self;
}

-(void)dealloc {
    [content release];
    [super dealloc];
}

- (NSMutableArray *)get_params {
    ns::MutableArray arr([self dup_params]);
    
    arr << pair(@"status", content);
    
    return arr;
}

@end

@interface OANeteasePicJsonParser : OAJsonParser

@property (nonatomic, copy) NSString* appKey;

@end

@implementation OANeteasePicJsonParser

@synthesize appKey;

- (id)init {
    self = [super init];
    
    self.contentType = @"multipart/form-data;boundary=wsi";
    
    return self;
}

- (void)dealloc {
    //zero_release(appKey);
    [super dealloc];
}

- (NSData*)parse_todata:(NSArray *)obj {
    ns::MutableDictionary dict;
    for (NSPair* each in obj) {
        dict[each.first] = each.second;
    }
    
    ns::MutableData body;
    ns::String str;
    
    ns::Data pic((NSData*)dict[@"pic"]);
    
    ns::String boundaryS = @"--wsi\r\n";
    ns::String boundaryE = @"--wsi--";
    
    // append pic.
    body.append(core::type_cast<core::data>(boundaryS));
    str = @"content-disposition:form-data;name=\"pic\";filename=\"unknown.png\" \r\n";
    body.append(core::type_cast<core::data>(str));
    str = @"content-type:image/png \r\n\r\n";
    body.append(core::type_cast<core::data>(str));
    body.append(pic);
    str = @"\r\n";
    body.append(core::type_cast<core::data>(str));
    
    // append status.
    body.append(core::type_cast<core::data>(boundaryS));
    str = @"content-disposition:form-data;name=\"status\" \r\n\r\n";
    body.append(core::type_cast<core::data>(str));
    str = (NSString*)dict[@"status"];
    body.append(core::type_cast<core::data>(str));
    str = @"\r\n";
    body.append(core::type_cast<core::data>(str));
    
    // append appkey.
    body.append(core::type_cast<core::data>(boundaryS));
    str = @"content-disposition:form-data;name=\"source\" \r\n\r\n";
    body.append(core::type_cast<core::data>(str));
    str = self.appKey;
    body.append(core::type_cast<core::data>(str));
    str = @"\r\n";
    body.append(core::type_cast<core::data>(str));
    
    // end.
    str = @"\r\n";
    body.append(core::type_cast<core::data>(str));
    body.append(core::type_cast<core::data>(boundaryE));
    
    return body.consign();
}

@end

@implementation OApiNeteaseWeiboUpload

@synthesize content, image, imageData;

- (id)init {
    self = [super init];
    
    self.url = @"http://api.t.163.com/statuses/upload";
    self.classRpc = [HttpRequest_Post class];
    self.cacheUpdate = YES;
    self.content = @"";
    
    return self;
}

-(void)dealloc {
    safe_release(content);
    safe_release(image);
    safe_release(imageData);
    
    [super dealloc];
}

- (NSMutableArray *)get_params {
    ns::MutableArray arr([super dup_params]);

    if (imageData)
        arr << pair(@"pic", imageData);
    else if (image)
        arr << pair(@"pic", image.dataAsPNG);
    
    arr << pair(@"source", ns::String(self.request.appKey) + @"\r\n");
    arr << pair(@"status", content);
    
    return arr;
}

- (BOOL)isUrlParameter:(NSPair *)obj {
    if ([obj.first isEqualToString:@"pic"])
        return NO;
    return YES;
}

- (void)setApiType:(OAuthApiType)type {
    if (_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser* parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {
            self.url = [_url stringByAppendingString:@".json"];
            OANeteasePicJsonParser* json = [[OANeteasePicJsonParser alloc] init];
            json.appKey = self.request.appKey;
            parser = json;
        } break;
        case OAuthApiTypeXML: {
        } break;
    }
    
    self.objparser = parser;
    safe_release(parser);
}

- (BOOL)process:(id)res {
    ns::Dictionary data(res);
    NSString* imgurl = data[@"upload_image_url"];
    
    OApiNeteaseWeiboPost* pos = [[OApiNeteaseWeiboPost alloc] initWithRequest:self.request];
    pos.apiType = self.apiType;
    pos.content = imgurl;
    BOOL suc = [pos retrieve_sync];
    [pos release];
    
    return suc;
}

@end

@implementation OApiNetSuggestions

- (id)init {
    self = [super init];
    
    self.url = @"http://api.t.163.com/users/suggestions";
    self.classRpc = [HttpRequest_Get class];
    
    return self;
}

@end

NNT_END_OBJC