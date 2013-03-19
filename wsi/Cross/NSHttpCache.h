
# ifndef __WSI_CROSS_NSHTTPCACHE_FB8164CF9A374C1C8B68D0E64E37C1A0_H_INCLUDED
# define __WSI_CROSS_NSHTTPCACHE_FB8164CF9A374C1C8B68D0E64E37C1A0_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSHttpCache : WSIObject

//! clear all cookies.
+ (void)clearAllCookies;

//! clear cookie for request.
+ (void)clearCookieOfRequest:(NSURLRequest*)req;

//! clear all responses.
+ (void)clearAllResponses;

//! clear response for domain.
+ (void)clearResponseOfDomain:(NSString*)dom;

//! clear response for url.
+ (void)clearResponseOfURL:(NSURL*)url;

//! clear response for request.
+ (void)clearResponseOfRequest:(NSURLRequest*)req;

@end

WSI_END_HEADER_OBJC

# endif
