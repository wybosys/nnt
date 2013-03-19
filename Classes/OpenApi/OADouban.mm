
# import "Core.h"
# import "OADouban.h"
# import "OAuthParser.h"
# import "HttpRequest.h"
# import "UIOAuthView.h"
# import "OADefines.h"
# import "XmlParser.h"
# import "OADefines.h"
# import "../UIKit/UIOAToggleView.res"

NNT_BEGIN_OBJC

@implementation OARequestDouban

@synthesize urlCallback;

- (id)init {
    
    self = [super init];
    
    self.urlRequest = @"http://www.douban.com/service/auth/request_token";
    self.urlAuthorize = @"http://www.douban.com/service/auth/authorize";
    self.urlAccess = @"http://www.douban.com/service/auth/access_token";
    
    self.appKey = OA_DOUBAN_APPKEY;
    self.appSecret = OA_DOUBAN_APPSECRET;
    
    self.signature = (sec_signature_func_t){ signature_hmac_sha1_name, signature_hmac_sha1 };
    
    self.version = (version_t){1, 0, 0, "1.0"};
    
    self.classRpc = [HttpRequest_Get class];
    
    self.cacheUpdate = YES;
    
    return self;
}

- (void)renew {    
    [super renew];
    self.nonce = kNSStringNonceSimple();
}

- (NSString*)baseString {    
    ::nnt::ns::MutableDictionary dict;
    [self generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.urlRequest OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSMutableArray*)get_extend_datas {
    return nil;
}

- (NSString*)url {    
    [self renew];
    
    NSString *str_base = [self baseString];
    
    NSString* str_secret = [NSString stringWithFormat:@"%@&", self.appSecret];
    NSString* str_signed = [self signatureString:str_base secret:str_secret];
    
    ::nnt::ns::MutableDictionary dict;    
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

@implementation OAuthorizeDouban

- (id)authView {
    UIOAuthView* authview = (UIOAuthView*)[super authView];
    authview.title.text = [OADouban Name];
    
    [authview registerFilter:@"http://www\\.douban\\.com/service/auth/::oauth::success" signal:@"success" target:self type:UIWebViewFilterTypeStartLoad].shouldStartLoad = NO;
    [self connect:@"success" sel:@selector(act_success:)];
    
    return authview;
}

- (void)act_success:(NNTEventObj*)evt {
    [self success];
}

@end

@implementation OAccessDouban

- (NSString*)baseString {
    
    ::nnt::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_token"] = self.request.token;
    
    NSString *ret = [NSString stringWithFormat:@"%@&%@&", HttpRequestGetMethod(self.classRpc), [self.request.urlAccess OAEncode]];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"%3D" andSegSep:@"%26" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSMutableArray*)get_extend_datas {
    return nil;
}

- (NSString*)url {
    
    [self.request renew];
    
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@&%@", self.request.appSecret, self.request.token_secret];
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    
    ::nnt::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict[@"oauth_signature"] = [str_signed OAEncode];

    dict[@"oauth_token"] = self.request.token;
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.request.urlAccess];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

- (BOOL)process:(NSObject *)__result {
    ::nnt::ns::MutableDictionary dict((NSMutableDictionary*)__result);
    self.request.access_token = dict[@"oauth_token"];
    self.request.access_token_secret = dict[@"oauth_token_secret"];
    return YES;
}

@end

@implementation OADouban

- (id)init {    
    self = [super init];
    
    _request = [[OARequestDouban alloc] init];
    _authorize = [[OAuthorizeDouban alloc] initWithRequest:_request];
    _access = [[OAccessDouban alloc] initWithRequest:_request withAuth:_authorize];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)saveTo:(NSMutableDictionary*)__dict {
    ::nnt::ns::MutableDictionary dict(__dict);
    dict[@"::oauth::access_token"] = _request.access_token;
    dict[@"::oauth::access_token_secret"] = _request.access_token_secret;
    dict[@"::oauth::token"] = _request.token;
    dict[@"::oauth::token_secret"] = _request.token_secret;
}

+ (NSString*)Name {
    return _W(@"DOUBAN");
}

+ (NSString*)UniqueIdentity {
    return @"C24ED9F3-997E-45E2-A9D8-DD5DA3C5598E";
}

+ (UIImage*)LogoImage {
    NgImage* imgRes = NgImageLoadPngData(douban, sizeof(douban));
    return [UIImage imageWithCGImage:imgRes.image];
}

@end

@interface OADoubanXmlParser : OAJsonParser 
@end

@implementation OADoubanXmlParser

- (id)init {
    self = [super init];
    self.contentType = @"application/atom+xml";
    return self;
}

- (NSData*)parse_todata:(NSArray *)__obj {
    XmlParser* xml = [[XmlParser alloc] initWithRootNode:[XmlNode nodeWithName:@"entry"]];
    XmlNode* root = xml.rootNode;
    [root addNamespace:@"" href:@"http://www.w3.org/2005/Atom"];
    [root addNamespace:@"db" href:@"http://www.douban.com/xmlns/"];
    
    for (NSPair* each in __obj) {
        [root addNodeByName:each.first].value = each.second;
    }
    
    XmlNode* node = [root addNodeByName:@"db:attribute"];
    node.value = @"private";
    [node addAttributeByName:@"name" value:@"privacy"];
    
    node = [root addNodeByName:@"db:attribute"];
    node.value = @"yes";
    [node addAttributeByName:@"name" value:@"can_reply"];
    
    NSString* xmlstring = [xml toString];
    
    [xml release];
    
    return [xmlstring dataUsingEncoding:NSUTF8StringEncoding];
}

@end

@implementation OApiDouban

- (id) init {    
    self = [super init];
    
    OADoubanXmlParser* parser = [[OADoubanXmlParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (NSString*)baseString {
    ::nnt::ns::MutableDictionary dict;
    
    // base params.
    [self.request generateParameters:dict];
    dict.remove(@"oauth_version");
    dict[@"oauth_token"] = self.request.access_token;
            
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
    trace_msg(str_secret);
    NSString* str_signed = [self.request signatureString:str_base secret:str_secret];
    trace_msg(str_signed);
    
    ::nnt::ns::MutableDictionary dict;
    [self.request generateParameters:dict];
    dict.remove(@"oauth_version");
    dict[@"oauth_signature"] = [str_signed OAEncode];
    dict[@"oauth_token"] = self.request.access_token;
    
    NSString *header = [NSString stringWithFormat:@"OAuth realm=\"\", %@", [dict combineWithKVSep:@"=" andSegSep:@", " keysur:@"" valsur:@"\""]];
    trace_msg(header);
    return header;
}

- (NSString*)url {
    return self.baseUrl;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

- (BOOL)process:(NSObject *)__result {
    ::nnt::ns::Dictionary dict((NSDictionary*)__result);
    NSNumber* code = dict[@"error_code"];
    self.error_msg = dict[@"error"];
    if ([code intValue] != 0) {
        return NO;
    }
    self.result = dict[@"data"];
    return YES;
}

- (NSMutableArray*)get_params {    
    ::nnt::ns::MutableArray arr([self dup_params]);        
    return arr;
}

@end

@implementation OApiDoubanUserInfo

- (id)init {
    self = [super init];
    self.url = @"http://api.douban.com/people";
    self.classRpc = [HttpRequest_Get class];
    return self;
}

@end

@implementation OApiDoubanDiaryPost

@synthesize content;
@synthesize title;

- (id)init {        
   self = [super init];
    self.url = @"http://api.douban.com/notes";
    
    return self;
}

- (void)dealloc {
    [content release];
    [title release];
    [super dealloc];
}

- (NSMutableArray*)get_params {    
    ::nnt::ns::MutableArray arr([super dup_params]);

    arr << pair(@"content", content);
    arr << pair(@"title", title);
    
    return arr;
}

@end

NNT_END_OBJC