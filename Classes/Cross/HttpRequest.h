
# ifndef __WSI_CROSS_HTTPREQUEST_B95B43A3840E428D80A9CC72723877B3_H_INCLUDED
# define __WSI_CROSS_HTTPREQUEST_B95B43A3840E428D80A9CC72723877B3_H_INCLUDED

# include "NullRpc.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_PROTOCOL(IObjParser);
WSIDECL_PRIVATE_HEAD(HttpRequest);

@interface HttpRequest : NullRpc {
    
    //! method, default is POST.
    NSString *method;
    
    //! cookies urls. it will be clean before each call.
    NSArray* cookieURLs;
    
    WSIDECL_PRIVATE(HttpRequest);
}

@property (nonatomic, copy)   NSString *method;
@property (nonatomic, retain) NSArray* cookieURLs;

- (id)init;
- (id)initWithMethod:(NSString*)method;

@end

@interface HttpRequest_Post : HttpRequest

+ (NSString*)Method;

@end

@interface HttpRequest_Get : HttpRequest

- (id)init;

+ (NSString*)Method;

@end

WSI_EXTERN NSString* HttpRequestGetMethod(Class cls);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)

class HttpRequest
: public ns::Object< ::HttpRequest>
{
public:
};

class HttpGetRequest
: public ns::Object< ::HttpRequest_Get >
{
public:
};

class HttpPostRequest
: public ns::Object< ::HttpRequest_Post >
{
public:
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif // objc-cxx

# endif // objc

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)
WSI_BEGIN_NS(rpc)

class HttpRequest
: public NullImplementation
{
public:
    
    HttpRequest();
    virtual ~HttpRequest();

};

WSI_END_NS
WSI_END_NS
WSI_END_NS

# endif // cxx

# endif