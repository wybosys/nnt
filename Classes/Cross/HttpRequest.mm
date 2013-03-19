
# import "Core.h"
# import "HttpRequest.h"
# import "Model.h"
# import "NullObjParser.h"

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(HttpRequest, NSObject)

WSIDECL_PRIVATE_IMPL(HttpRequest)

WSIDECL_PRIVATE_END

@interface HttpRequest ()

- (void)_cookie_clean;

@end

@implementation HttpRequest

@synthesize method;
@synthesize cookieURLs;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(HttpRequest);
    
    self.method = @"POST";
    
    return self;
}

- (id)initWithMethod:(NSString *)__method {
    self = [self init];
    
    self.method = __method;
    
    return self;
}

- (void)dealloc {
    zero_release(cookieURLs);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)_cookie_clean {
    NSHTTPCookieStorage* mgr = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    for (NSString* each in cookieURLs) {
        NSArray* cookies = [mgr cookiesForURL:
                            [NSURL URLWithString:each]];        
        for (NSHTTPCookie* cookie in cookies) {                                
            [mgr deleteCookie:cookie];
        }
    }	
}

- (NSObject*)call:(Model *)model withUrl:(NSURL*)url {
    [super call:model withUrl:url];
    
    if (url == nil) {
        trace_msg(@"url is nil");
        return nil;
    }
    
    if (self.verbose)
        trace_obj(url);
    
    WSIRPC_CALLROUND;
    WSIMACRO_LOCKOBJ(self);
    
    // clean.
    [self _cookie_clean];
    
    // get data from model by parser.
    id <NullObjParser> parser = model.objparser;
    if (nil == parser) {
        trace_msg(@"object-parser is nil");
        return nil;
    }
    
    // convert params.
    id params = model.params;            
    
    // connect
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    
    // set method of http.
    [request setHTTPMethod:self.method];
    
    // set content type.
    [request setValue:parser.contentType forHTTPHeaderField:@"Content-Type"];
    
    // write extend fields.
    NSArray *arr_extends = model.extendDatas;
    for (id extend in arr_extends) {
        if ([extend isKindOfClass:[MURLHeaderField class]]) {
            MURLHeaderField *obj = (MURLHeaderField*)extend;
            switch (obj.mech) {
                case MURLHeaderFieldMechAdd: [request addValue:obj.value forHTTPHeaderField:obj.field]; break;
                case MURLHeaderFieldMechSet: [request setValue:obj.value forHTTPHeaderField:obj.field]; break;
            }
            
            trace_fmt(@"%@: %@", obj.field, obj.value);
        }
    }
    
    // write params as body.
    NSData *data_params = [parser parse_todata:params];
    if (data_params && [data_params length]) {
        [request setValue:tostr(data_params.length) forHTTPHeaderField:@"Content-length"];
        [request setHTTPBody:data_params];
    } else {
        [request setValue:@"0" forHTTPHeaderField:@"Content-length"];
    }
    
    // respone
    NSURLResponse *respone = nil;
    NSError *error = nil;
    
    // get data.
    NSData *repdata = [WSINSURLConnection sendSynchronousRequest:request
                                               returningResponse:&respone
                                                           error:&error];
    if (nil == repdata
        && error) {
        //trace_fmt(@"failed to send request [%@]: %@",
        //          url.absoluteString,
        //          error.localizedDescription);
        if (model.verbose)
            [Msgbox fatal:error.localizedDescription];
        return nil;
    }
    
    if (model.verboseData && self.verbose) {
        NSString *str_rc = [[NSString alloc] initWithBytes:[repdata bytes] 
                                                    length:[repdata length] 
                                                  encoding:parser.dataEncoding];
        trace_msg(str_rc);
        [str_rc release];
    }
    
    // parser result
    NSObject* ret = nil;
    if (repdata) {
        ret = [parser parse_object:repdata]; 
    }
    
    return ret;
}

- (BOOL)is_connected {
    return YES;
}

- (void)disconnect {
    PASS;
}

@end

@implementation HttpRequest_Post

+ (NSString*)Method {
    return @"POST";
}

@end

@implementation HttpRequest_Get

- (id)init {
    self = [super init];
    
    self.method = @"GET";
    
    return self;
}

+ (NSString*)Method {
    return @"GET";
}

@end

NSString* HttpRequestGetMethod(Class cls) {
    if (class_existMethod(cls, @selector(Method)) == NO)
        return nil;
    return [cls Method];
}

WSI_END_OBJC
