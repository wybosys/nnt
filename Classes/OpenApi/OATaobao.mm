
# import "Core.h"
# import "OATaobao.h"
# import "OADefines.h"
# import "OAuthParser.h"
# import "UIOAuthView.h"
# import "Mime+WSI.h"
# import "HttpRequest.h"

using namespace ::wsi;

WSI_BEGIN_OBJC

@implementation OARequestTaobao

@synthesize refresh_token;

- (id)init {
    self = [super init];
    
# ifdef WSI_TARGET_MAC
    self.urlAuthorize = @"https://oauth.taobao.com/authorize";
# else
    self.urlAuthorize = @"https://oauth.taobao.com/authorize?view=wap";
# endif
    
    self.urlAccess = @"https://oauth.taobao.com/token";
    
    self.clientId = OA_TAOBAO_APPKEY;
    self.clientSecret = OA_TAOBAO_APPSECRET;
    
    self.signature = (sec_signature_func_t){ signature_hmac_sha1_name, signature_hmac_sha1 };
    
    self.grantType = @"refresh_token";
    self.responseType = @"token";
    self.scopes = ns::MutableArray()
    //<< @"promotion"
    << @"item"
    //<< @"usergrade"
    ;
    
    return self;
}

- (void)dealloc {
    safe_release(refresh_token);
    
    [super dealloc];
}

@end

@implementation OAuthorizeTaobao

- (id)authView {
    UIOAuthView *authview = (UIOAuthView*)[super authView];
    authview.title.text = [OATaobao Name];
    
    [authview registerFilter:@"wsi://oauth/2.0/redirect#" signal:@"authorize_success" type:UIWebViewFilterTypeStartLoad];
    [authview connect:@"authorize_success" sel:@selector(act_authorize_success:) obj:self];
    
    return authview;
}

- (void)act_authorize_success:(WSIEventObj*)evt {
    // get refresh token.
    ns::Array res([evt.result captureComponentsMatchedByRegex:@"refresh_token=(\\w+)"]);
    OARequestTaobao* req = (OARequestTaobao*)self.request;
    req.refresh_token = res[1];
    
    // send success.
    [self success];
}

@end

@implementation OAccessTaobao

- (id)init {
    self = [super init];
    
    OAJsonParser* parser = [[OAJsonParser alloc] init];
    self.objparser = parser;
    safe_release(parser);
    
    return self;
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);
    OARequestTaobao* req = (OARequestTaobao*)self.request;
    
    arr << ns::Pair(@"refresh_token", req.refresh_token) << ns::Pair(@"grant_type", req.grantType) << ns::Pair(@"client_id", req.clientId) << ns::Pair(@"client_secret", req.clientSecret);
    
    return arr;
}

- (BOOL)process:(NSDictionary*)res {
    ns::Dictionary data(res);
    
    self.request.access_token = data[@"access_token"];
    self.request.user_id = data[@"taobao_user_id"];
    
    return YES;
}

@end

@implementation OATaobao

- (id)init {
    self = [super init];
    
    _request = [[OARequestTaobao alloc] init];
    _authorize = [[OAuthorizeTaobao alloc] initWithRequest:_request];
    _access = [[OAccessTaobao alloc] initWithRequest:_request withAuth:_authorize];
    
    return self;
}

+ (NSString*)Name {
    return _W(@"TAOBAO OPEN");
}

+ (NSString*)UniqueIdentity {
    return @"b222d494-f7f0-11e1-92c3-406c8f4e5bc9";
}

@end

@interface OATaobaoJsonParser : OAJsonParser @end

@implementation OATaobaoJsonParser

- (id)init {
    self = [super init];
    
    self.contentType = kMimeTypeFormUrlEncoded;
    
    return self;
}

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end

@interface OATaobaoXmlParser : OAXmlParser @end

@implementation OATaobaoXmlParser

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end

@implementation OApiTaobao

@synthesize inSandbox;

- (id)init {
    self = [super init];
    
    self.inSandbox = NO;
    self.url = @"https://eco.taobao.com/router/rest";
    
    return self;
}

- (void)setInSandbox:(BOOL)val {
    if (inSandbox == val)
        return;
    inSandbox = val;
    
    if (inSandbox)
        self.url = @"http://gw.api.tbsandbox.com/router/rest";
    else
        self.url = @"https://eco.taobao.com/router/rest";
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);
    
    arr << ns::Pair(@"method", self.method) << ns::Pair(@"access_token", self.request.access_token) << ns::Pair(@"format", TRIEXP(_apiType == OAuthApiTypeJSON, @"json", @"xml")) << ns::Pair(@"v", @"2.0");
    
    core::Time tm = core::Time::Local();
    
    
    return arr;
}

- (void)setApiType:(OAuthApiType)type {
    if (_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser* parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {
            parser = [[OATaobaoJsonParser alloc] init];
        } break;
        case OAuthApiTypeXML: {
            parser = [[OATaobaoXmlParser alloc] init];
        } break;
    }
    
    self.objparser = parser;
    safe_release(parser);
}

@end

@implementation OATaobaoUserinfo

@synthesize nick, fields;

- (id)init {
    self = [super init];
    
    self.method = @"taobao.user.get";
    self.fields = @"user_id,nick";
    self.classRpc = [HttpRequest_Get class];
    
    return self;
}

- (void)dealloc {
    safe_release(nick);
    safe_release(fields);
    
    [super dealloc];
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);
    
    arr << ns::Pair(@"fields", fields);
    if ([nick notEmpty])
        arr << ns::Pair(@"nick", nick);
    
    return arr;
}

@end

WSI_END_OBJC