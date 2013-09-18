
# import "Core.h"
# import "OASINA.h"
# import "OAuthParser.h"
# import "UIOAuthView.h"
# import "OADefines.h"
# import "../UIKit/UIOAToggleView.res"
# import "URLCodec.h"
# import "HttpRequest.h"
# import "Mime+NNT.h"

using namespace ::nnt;

NNT_BEGIN_OBJC
                                  
# define WEIBO_STATUS_LIMIT 140

@implementation OARequestSina

- (id)init {
    self = [super init];
    
    self.urlAuthorize = @"https://api.weibo.com/oauth2/authorize";
    self.urlAccess = @"https://api.weibo.com/oauth2/access_token";
    
    self.clientId = OA_SINA_APPKEY;
    self.clientSecret = OA_SINA_APPSECRET;
    
    self.signature = (sec_signature_func_t){ signature_hmac_sha1_name, signature_hmac_sha1 };
    
    return self;
}

@end

@implementation OAuthorizeSina

- (id)authView {
    UIOAuthView* authview = (UIOAuthView*)[super authView];
    authview.title.text = [OASina Name];
        
    [authview registerFilter:@"http://nnt//oauth/2.0/redirect\\?code=\\S+" signal:@"authorize_success" type:UIWebViewFilterTypeStartLoad].shouldStartLoad = NO;
    [authview connect:@"authorize_success" sel:@selector(act_authorize_success:) obj:self];
    
    [authview registerFilter:@"http://nnt//oauth/2.0/redirect\\?error" signal:@"authorize_failed" type:UIWebViewFilterTypeStartLoad].shouldStartLoad = NO;
    [authview connect:@"authorize_failed" sel:@selector(act_authorize_failed) obj:self];
    
    return authview;
}

- (void)act_authorize_success:(NNTEventObj*)evt {
    ns::URLDecode urldecode(evt.result);
    
    self.request.code = urldecode.value(@"code");
    
    // send success.
    [self success];
}

- (void)act_authorize_failed {
    [self failed];
}

@end

@implementation OAccessSina

- (id)init {
    self = [super init];
    
    JsonObjParser* parser = [[JsonObjParser alloc] init];
    self.objparser = parser;
    safe_release(parser);
    
    return self;
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr([self dup_params]);
    
    arr << ns::Pair(@"client_id", self.request.clientId) << ns::Pair(@"client_secret", self.request.clientSecret);
    arr << ns::Pair(@"grant_type", @"authorization_code") << ns::Pair(@"code", self.request.code) << ns::Pair(@"redirect_uri", self.request.redirectUrl);
    
    return arr;
}

- (BOOL)process:(id)res {
    ns::Dictionary dict(res);
    
    self.request.access_token = dict[@"access_token"];
    self.request.expires = core::touint(dict[@"expires_in"]);
    self.request.remind = core::touint(dict[@"remind_in"]);
    self.request.user_id = dict[@"uid"];
    
    return YES;
}

@end

@implementation OASina

- (id)init {
    self = [super init];
    
    _request = [[OARequestSina alloc] init];
    _authorize = [[OAuthorizeSina alloc] initWithRequest:_request];
    _access = [[OAccessSina alloc] initWithRequest:_request withAuth:_authorize];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

+ (NSString*)Name {
    return _W(@"SINA OPEN");
}

+ (NSString*)UniqueIdentity {
    return @"f51554b2-1b1d-11e1-84c4-cbf97b1748e9";
}

@end

@implementation OASinaWeibo

+ (NSString*)Name {
    return _W(@"SINA MBLOG");
}

+ (NSString*)UniqueIdentity {
    return @"f0ee7934-1d59-11e1-828e-3f2c7651654d";
}

+ (UIImage*)LogoImage {
    NgImage* imgRes = NgImageLoadPngData(sina_mblog, sizeof(sina_mblog));
    return [UIImage imageWithCGImage:imgRes.image];
}

@end

@interface OASinaJsonParser : OAJsonParser @end

@implementation OASinaJsonParser

- (id)init {
    self = [super init];
    
    self.contentType = kMimeTypeFormUrlEncoded;
    
    return self;
}

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end

@interface OASinaXmlParser : OAXmlParser @end

@implementation OASinaXmlParser

- (NSData*)parse_todata:(NSObject *)__obj {
    return nil;
}

@end

@implementation OApiSina

- (void)setApiType:(OAuthApiType)type {
    if (_apiType == type)
        return;
    _apiType = type;
    
    NullObjParser* parser = nil;
    switch (type) {
        case OAuthApiTypeJSON: {            
            self.url = [_url stringByAppendingString:@".json"];
            parser = [[OASinaJsonParser alloc] init];
        } break;
        case OAuthApiTypeXML: {            
            self.url = [_url stringByAppendingString:@".xml"];
            parser = [[OASinaXmlParser alloc] init];
        } break;
    }
    
    self.objparser = parser;
    safe_release(parser);
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);
    
    arr << ns::Pair(@"access_token", self.request.access_token);
    
    return arr;
}

@end

@implementation OApiSinaUserinfo

@synthesize uid;

- (id)init {
    self = [super init];
    
    self.url = @"https://api.weibo.com/2/users/show";
    self.classRpc = [HttpRequest_Get class];
    
    return self;
}

- (void)dealloc {
    safe_release(uid);
    
    [super dealloc];
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);
    
    if (uid == nil)
        arr << ns::Pair(@"uid", self.request.user_id);
    else
        arr << ns::Pair(@"uid", uid);
    
    return arr;
}

@end

@implementation OApiSinaWeiboPost

@synthesize content;

- (id)init {
    self = [super init];
    
    self.url = @"https://api.weibo.com/2/statuses/update";
    self.cacheUpdate = YES;
    
    return self;
}

- (void)dealloc {
    [content release];
    [super dealloc];
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);

    NSString* post = [[content copy] autorelease];
    if ([post length] > WEIBO_STATUS_LIMIT)
        post = [post substringToIndex:WEIBO_STATUS_LIMIT];
    post = [post OAEncode];
    arr << pair(@"status", post);
    
    return arr;
}

@end

@interface OASinaPicJsonParser : OASinaJsonParser 

@property (nonatomic, copy) NSString* appKey;

@end

@implementation OASinaPicJsonParser

@synthesize appKey;

- (id)init {
    self = [super init];
    
    self.contentType = @"multipart/form-data;boundary=nnt";
    
    return self;
}

- (void)dealloc {
    zero_release(appKey);
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
    
    ns::String boundaryS = @"--nnt\r\n";
    ns::String boundaryE = @"--nnt--";
    
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

@interface OASinaPicXmlParser : OASinaXmlParser

@property (nonatomic, copy) NSString* appKey;

@end

@implementation OASinaPicXmlParser

@synthesize appKey;

- (id)init {
    self = [super init];
    
    self.contentType = @"multipart/form-data, boundary=nnt";
    
    return self;
}

- (void)dealloc {
    zero_release(appKey);
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
    
    ns::String boundaryS = @"--nnt\r\n";
    ns::String boundaryE = @"--nnt--";
    
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

@implementation OApiSinaWeiboUpload

@synthesize content;
@synthesize image;
@synthesize imageData;

- (id)init {
    self = [super init];
    
    self.url = @"https://upload.api.weibo.com/2/statuses/upload";
    self.cacheUpdate = YES;
    
    return self;
}

- (void)dealloc {
    [content release];
    [image release];
    [imageData release];
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
            OASinaPicJsonParser* json = [[OASinaPicJsonParser alloc] init];
            json.appKey = self.request.appKey;
            parser = json;
        } break;
        case OAuthApiTypeXML: {            
            self.url = [_url stringByAppendingString:@".xml"];
            OASinaPicXmlParser* xml = [[OASinaPicXmlParser alloc] init];
            xml.appKey = self.request.appKey;
            parser = xml;
        } break;
    }
    
    self.objparser = parser;
    safe_release(parser);
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);
    
    NSString* post = [[content copy] autorelease];
    if ([post length] > WEIBO_STATUS_LIMIT)
        post = [post substringToIndex:WEIBO_STATUS_LIMIT];
    post = [post OAEncode];
    arr << pair(@"status", post);
    
    if (imageData)
        arr << pair(@"pic", imageData);
    else if (image)
        arr << pair(@"pic", [image dataAsPNG]);
    
    return arr;
}

- (BOOL)isUrlParameter:(NSPair*)obj {
    if ([obj.first isEqualToString:@"pic"])
        return NO;
    return YES;
}

@end

@implementation OApiSinaFriendshipsCreate

@synthesize screen_name;

- (id)init {
    self = [super init];
    
    self.url = @"http://api.t.sina.com.cn/friendships/create";
    self.cacheUpdate = YES;
    
    return self;
}

- (void)dealloc {
    zero_release(screen_name);
    [super dealloc];
}

- (NSMutableArray*)get_params {
    ::nnt::ns::MutableArray arr([self dup_params]);        
    arr << pair(@"screen_name", screen_name);
    return arr;
}

@end

NNT_END_OBJC