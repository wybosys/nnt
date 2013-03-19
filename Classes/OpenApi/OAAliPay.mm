
# import "Core.h"
# import "OAAliPay.h"
# import "HttpRequest.h"
# import "OADefines.h"
# import "UIOAuthView.h"
# import "URLCodec.h"

using namespace ::nnt;

NNT_BEGIN_OBJC

@implementation OARequestAlipay

- (id)init {
    self = [super init];
    
    self.urlAuthorize = @"https://mapi.alipay.com/gateway.do";
    
    self.clientId = OA_ALIPAY_PARTENER;
    self.clientSecret = OA_ALIPAY_KEY;
    
    self.signature = (sec_signature_func_t){ signature_md5_name, signature_md5 };
    
    return self;
}

@end

@implementation OAuthorizeAlipay

- (id)authView {
    UIOAuthView* av = [super authView];
    av.title.text = [OAliPay Name];
    
    return av;
}

- (NSString*)url {
    ns::MutableDictionary dict;
    
    dict[@"service"] = @"alipay.auth.authorize";
    dict[@"partner"] = self.request.clientId;
    dict[@"_input_charset"] = @"utf-8";
    dict[@"return_url"] = @"buy.daphne.cn";//self.request.redirectUrl;
    dict[@"target_service"] = @"user.auth.quick.login";
    
    // sign.
    ns::String str_sign = [dict combineWithKVSep:@"=" andSegSep:@"&" keysur:@"" valsur:@"" sort:@selector(compare:)];
    str_sign += self.request.clientSecret;
    str_sign = self.request.signature.method(str_sign, nil);
    
    dict[@"sign"] = str_sign;
    dict[@"sign_type"] = self.request.signature.method_name();
    
    ns::String ret = self.request.urlAuthorize;
    ret += @"?";
    ret += ns::URLEncode::encode(dict, ns::encoded);
    return ret;
}

@end

@implementation OAccessAlipay

- (id)init {
    self = [super init];
    
    return self;
}

- (NSMutableArray*)get_params {
    ns::MutableArray arr(super.get_params);
    
    return arr;
}

- (BOOL)process:(id)result {
    return YES;
}

@end

@implementation OAliPay

- (id)init {
    self = [super init];
    
    _request = [[OARequestAlipay alloc] init];
    _authorize = [[OAuthorizeAlipay alloc] initWithRequest:_request];
    _access = [[OAccessAlipay alloc] initWithRequest:_request withAuth:_authorize];
    
    return self;
}

+ (NSString*)Name {
    return _W(@"ALIPAY OPEN");
}

+ (NSString*)UniqueIdentity {
    return @"060E9481-09E6-4D72-902B-129120872592";
}

@end

NNT_END_OBJC
