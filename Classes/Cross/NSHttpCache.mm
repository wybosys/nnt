
# import "Core.h"
# import "NSHttpCache.h"

NNT_BEGIN_OBJC

@implementation NSHttpCache

+ (void)clearAllCookies {
    for(NSHTTPCookie *cookie in [[NSHTTPCookieStorage sharedHTTPCookieStorage] cookies]) {
        [[NSHTTPCookieStorage sharedHTTPCookieStorage] deleteCookie:cookie];
    }
}

+ (void)clearCookieOfRequest:(NSURLRequest *)req {
    [[NSURLCache sharedURLCache] removeCachedResponseForRequest:req];
}

+ (void)clearAllResponses {
    [[NSURLCache sharedURLCache] removeAllCachedResponses];
}

+ (void)clearResponseOfDomain:(NSString *)dom {
    for(NSHTTPCookie *cookie in [[NSHTTPCookieStorage sharedHTTPCookieStorage] cookies]) {
        if([[cookie domain] isEqualToString:dom]) {
            [[NSHTTPCookieStorage sharedHTTPCookieStorage] deleteCookie:cookie];
        }
    }
}

+ (void)clearResponseOfURL:(NSURL *)url {
    for(NSHTTPCookie *cookie in [[NSHTTPCookieStorage sharedHTTPCookieStorage] cookies]) {
        if([[cookie commentURL] isEqual:url])
            [[NSHTTPCookieStorage sharedHTTPCookieStorage] deleteCookie:cookie];
    }
}

+ (void)clearResponseOfRequest:(NSURLRequest *)req {
    [NSHttpCache clearResponseOfURL:req.URL];
}

@end

NNT_END_OBJC
