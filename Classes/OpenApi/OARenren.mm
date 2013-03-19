
# import "Core.h"
# import "OARenren.h"
# import "HttpRequest.h"
# import "UIOAuthView.h"
# import "OAuthParser.h"
# import "OADefines.h"
# import "OAuth.h"
# import "JsonObjParser.h"
# import "../UIKit/UIOAToggleView.res"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

//@interface OARenrenHttpRequest : HttpRequest @end
//
//@implementation OARenrenHttpRequest
//
//- (id)init {
//    self = [super init];    
//    self.cookieURLs = [NSArray arrayWithObjects:@"http://graph.renren.com", @"http://widget.renren.com", nil];    
//    return self;
//}
//
//@end

@implementation OARequestRenRen

- (id)init {
    self = [super init];
    
    self.urlAuthorize = @"https://graph.renren.com/oauth/authorize";
    self.urlAccess = @"https://graph.renren.com/oauth/token";
    
    self.clientId = OA_RENREN_CLIENTID;
    self.clientSecret = OA_RENREN_CLIENTSECRET;
    self.responseType = @"code";    
    self.grantType = @"authorization_code";    
    self.redirectUrl = @"http://widget.renren.com/callback.html";
    self.scopes = [NSMutableArray arrayWithObjects:@"publish_blog", nil];
    
    return self;
}

@end

@implementation OAuthorizeRenRen

- (id)authView {
    UIOAuthView* authview = (UIOAuthView*)[super authView];
    authview.title.text = [OARenRen Name];
    
    //[authview.web enableJQuery];
    [authview.web.additionalJavascript addObject:@"$('.close').attr('onclick', 'window.open(\"::oauth::cancel\")');"];
    
    [authview registerFilter:(self.request.redirectUrl + ns::String(@"#code=")) signal:@"authorize_success" type:UIWebViewFilterTypeStartLoad].shouldStartLoad = NO;
    
    [authview connect:@"authorize_success" sel:@selector(act_authorize_success:) obj:self];
    
    return authview;
}

- (void)act_authorize_success:(NNTEventObj*)evt {
    NSString *code = [self valueForKey:@"code" ofQuery:evt.result];

    self.request.code = code;

    // send success.
    [self success];        
}

- (NSString*)valueForKey:(NSString *)key ofQuery:(NSString*)query {
	NSArray *pairs = [query componentsSeparatedByString:@"#"];
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

@implementation OAccessRenRen

- (id)init {
    self = [super init];
    
    self.classRpc = [HttpRequest_Get class];
    
    JsonObjParser* parser = [[JsonObjParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    return self;
}

- (NSString*)url {
    
    wsi::ns::MutableDictionary dict;
    dict[@"response_type"] = [self.request.responseType OAEncode];
    dict[@"grant_type"] = [self.request.grantType OAEncode];
    dict[@"code"] = [self.request.code OAEncode];
    dict[@"client_secret"] = [self.request.clientSecret OAEncode];
    [self.request generateParameters:dict];
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.request.urlAccess];
    
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
    return ret;
}

- (BOOL)process:(id)__result {
    
    wsi::ns::MutableDictionary dict((NSMutableDictionary*)__result);
    self.request.access_token = dict[@"access_token"];
    return YES;
}

@end

@implementation OARenRen

- (id)init {
    
    self = [super init];
    
    _request = [[OARequestRenRen alloc] init];
    _authorize = [safe_alloc(OAuthorizeRenRen) initWithRequest:_request];
    _access = [safe_alloc(OAccessRenRen) initWithRequest:_request withAuth:_authorize];
    
    return self;
}

- (void)dealloc {
    
    [super dealloc];
}

+ (NSString*)Name {
    return _W(@"RENREN");
}

+ (NSString*)UniqueIdentity {
    return @"7144309c-1bd9-11e1-93ee-df44d327977c";
}

+ (UIImage*)LogoImage {    
    WCGImage* imgRes = WCGImageLoadPngData(renren_mblog, sizeof(renren_mblog));
    return [UIImage imageWithCGImage:imgRes.image];
}

- (void)saveTo:(NSMutableDictionary*)__dict {
    wsi::ns::MutableDictionary dict(__dict);
    dict[@"::oauth::access_token"] = _request.access_token;
    dict[@"::oauth::client_secret"] = _request.clientSecret;
}

- (BOOL)loadFrom:(NSDictionary*)__dict {
    wsi::ns::Dictionary dict(__dict);
    _request.access_token = dict[@"::oauth::access_token"];
    _request.clientSecret = dict[@"::oauth::client_secret"];
    return YES;
}

@end

@implementation OApiRenRen

@synthesize str_apiType;

- (id)init{
    self = [super init];
    
    self.version = (version_t){1, 0, 0, "1.0"};
    self.url = @"http://api.renren.com/restserver.do";
    
    return self;
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

- (NSMutableArray*)dup_params {
    wsi::ns::MutableArray arr([super dup_params]);
    arr << pair(@"access_token", self.request.access_token);
    arr << pair(@"format", str_apiType);
    arr << pair(@"v", [NSString stringWithUTF8String:self.version.ver]);
    arr << pair(@"method", self.method);
    return arr;
}

- (NSMutableArray*)get_params {
    wsi::ns::MutableArray arr([self dup_params]);
    return arr;
}

- (NSString*)baseString {
    wsi::ns::MutableDictionary dict;

    // params.
    for (NSPair *each in self.params) {
        dict[each.first] = each.second;
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@", [dict combineWithKVSep:@"=" andSegSep:@"" keysur:@"" valsur:@"" sort:@selector(compare:)]];
    
# ifdef NNT_DEBUG
    trace_msg(ret);
# endif
    
    return ret;
}

- (NSString*)url {
    
    NSString* str_base = [self baseString];
    NSString* str_secret = [NSString stringWithFormat:@"%@%@", str_base, self.request.clientSecret];
    NSString* str_signed = [str_secret md5];
    
    wsi::ns::MutableDictionary dict;
    dict[@"sig"] = str_signed;
    
    // params.
    for (NSPair *each in self.params) {
        dict[each.first] = each.second;
    }
    
    NSString *ret = [NSString stringWithFormat:@"%@?", self.baseUrl];
    ret = [NSString stringWithFormat:@"%@%@", ret, [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@""]];
    
# ifdef NNT_DEBUG
    trace_msg(ret);
# endif
    
    return ret;
}

- (BOOL)process:(NSObject *)__result {
    
    wsi::ns::Dictionary dict;
    
    if ([__result isKindOfClass:[NSArray class]]) {
        NSArray *__tmp_result = (NSArray*)__result;
        dict = ((NSDictionary*)[__tmp_result objectAtIndex:0]);
    }
    
    if ([__result isKindOfClass:[NSDictionary class]]) {
        dict = ((NSDictionary*)__result);
    }
    
    self.error_code = dict[@"code"] ? dict[@"code"] : nil;
    self.error_msg = dict[@"error"] ? dict[@"error"] : nil;
    if (self.error_msg != nil) {
        return NO;
    }
    
    self.result = dict;
    
    return YES;
}

@end

@implementation OApiRenRenUserInfo

- (id)init {
    
    self = [super init];
    
    self.method = @"users.getInfo";
    self.classRpc = [HttpRequest_Post class];
    
    return self;
}

@end

@implementation OApiRenRenWeiboPost

@synthesize title, content;

- (id)init {
    
    self = [super init];
    
    self.method = @"blog.addBlog";
    self.classRpc = [HttpRequest_Post class];
    
    return self;
}

- (void)dealloc {
    
    [title release];
    [content release];
    [super dealloc];
}

- (NSMutableArray*)get_params {
    wsi::ns::MutableArray arr([self dup_params]);
    uint length = 60;
    if ([content length] > length)
        content = [content substringToIndex:length];
    arr << pair(@"title", title) << pair(@"content", content);
    return arr;
}

@end

NNT_END_OBJC