
# import "Core.h"
# import "OATencentOS.h"
# import "OADefines.h"
# import "UIOAuthView.h"
# import "HttpRequest.h"
# import "OAuthParser.h"
# import "../UIKit/UIOAToggleView.res"
# import "Mime+NNT.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

@implementation OARequestQQOS

- (id)init {
    self = [super init];
    
# ifdef NNT_TARGET_MAC
    self.urlAuthorize = @"https://graph.qq.com/oauth2.0/authorize";
# else
    self.urlAuthorize = @"https://graph.z.qq.com/moc2/authorize";
# endif
    
    self.urlAccess = @"https://graph.qq.com/oauth2.0/me";
    
    self.clientId = OA_TENCENT_OPENSNS_APPID;
    self.clientSecret = OA_TENCENT_OPENSNS_APPKEY;
    
    self.responseType = @"token";    
    self.scopes = ns::MutableArray() << @"do_like" << @"get_user_info" << @"add_share" << @"add_t" << @"add_pic_t" << @"get_info" << @"get_other_info";
    self.redirectUrl = @"";
    
    return self;
}

@end

@implementation OAuthorizeQQOS

- (id)authView {    
    UIOAuthView* authview = (UIOAuthView*)[super authView];
    authview.title.text = [OATencentOS Name];

    [authview registerFilter:@"access_token=(\\w+)&expires_in=(\\d+)" signal:@"authorize_success" type:UIWebViewFilterTypeStartLoad];
    [authview connect:@"authorize_success" sel:@selector(act_authorize_success:) obj:self];
    
    return authview;
}

- (void)act_authorize_success:(NNTEventObj*)evt {    
    ns::Array arr([evt.result captureComponentsMatchedByRegex:@"access_token=(\\w+)&expires_in=(\\d+)"]);
    
    self.request.access_token = arr[1U];
    self.expire = [arr[2U] intValue];
    
    // send success.
    [self success];        
}

@end

@interface OAQQOSParser : NullObjParser
@end

@implementation OAQQOSParser

- (id)to_object:(id)data {
    NSString* str = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
    NSArray* arr = [str captureComponentsMatchedByRegex:@"callback\\((.+)\\);"];
    [str release];
    if ([arr count] != 2) {
        return nil;
    }
    NSString* json_data = (NSString*)[arr objectAtIndex:1];
    return [NNTObject json_decode:json_data];
}

@end

@implementation OAccessQQOS

- (id)init {
    self = [super init];
    
    self.classRpc = [HttpRequest_Get class];

    OAQQOSParser* parser = [[OAQQOSParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    return self;
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr([self dup_params]);
    arr << pair(@"access_token", self.request.access_token);
    return arr;
}

- (BOOL)process:(id)__result {
    ns::Dictionary dict(__result);
    self.request.user_id = dict[@"openid"];
    return YES;
}

@end

@implementation OATencentOS

- (id)init {
    self = [super init];
    
    _request = [[OARequestQQOS alloc] init];
    _authorize = [safe_alloc(OAuthorizeQQOS) initWithRequest:_request];
    _access = [safe_alloc(OAccessQQOS) initWithRequest:_request withAuth:_authorize];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

+ (NSString*)Name {
    return _W(@"TENCENT OPENSPACE");
}

+ (NSString*)UniqueIdentity {
    return @"88fc14ac-1d5f-11e1-abdc-9323fa5f2e84";
}

+ (UIImage*)LogoImage {
    NgImage* imgRes = NgImageLoadPngData(tencent_openspace, sizeof(tencent_openspace));
    return [UIImage imageWithCGImage:imgRes.image];
}

@end

@interface OATencentOSParser : OAJsonParser

@end

@implementation OATencentOSParser

- (NSData*)parse_todata:(NSArray *)obj {
    NSString* str = [NSURL combineArguments:obj];
    return [str dataUsingEncoding:NSASCIIStringEncoding];
}

@end

@implementation OApiTencentOS

@synthesize strApiType;

- (id)init {
    self = [super init];
    
    //OATencentOSParser* parser = [[OATencentOSParser alloc] init];
    //self.objparser = parser;
    //safe_release(parser);
    
    return self;
}

- (void)dealloc {
    safe_release(strApiType);
    [super dealloc];
}

- (NSMutableArray*)dup_params {
    ns::MutableArray arr([super dup_params]);
    arr << pair(@"access_token", self.request.access_token) \
    << pair(@"oauth_consumer_key", self.request.clientId) \
    << pair(@"openid", self.request.user_id);
    return arr;
}

- (NSURL*)get_url {
    return [NSURL URLWithString:self.url];
}

@end

@implementation OApiQQOSUserInfo

- (id)init {
    self = [super init];
    
    self.url = @"https://graph.qq.com/user/get_user_info";
    self.classRpc = [HttpRequest_Get class];
    
    return self;
}

@end

@implementation OApiQQOSAddShare

@synthesize title, reference, content, image, site;

- (id)init {
    self = [super init];
    
    self.url = @"https://graph.qq.com/share/add_share";
    self.classRpc = [HttpRequest_Get class];
    self.site = @"http://libwsi.sf.net";
    
    self.reference = ns::String(@"http://") + NNTGetProjectURL();
    self.site = self.reference;
    
    return self;
}

- (void)dealloc {
    safe_release(title);
    safe_release(reference);
    safe_release(content);
    safe_release(image);
    [super dealloc];
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);

    arr << pair(@"title", [title OAEncode]) << pair(@"url", [reference OAEncode]) << pair(@"site", site);
    
    if ([content notEmpty])
        arr << pair(@"summary", [content OAEncode]);
    
    if (image)
        arr << pair(@"images", image.absoluteString);
    
    return arr;
}

@end

NNT_END_OBJC