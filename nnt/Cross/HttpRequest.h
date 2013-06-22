
# ifndef __NNT_CROSS_HTTPREQUEST_B95B43A3840E428D80A9CC72723877B3_H_INCLUDED
# define __NNT_CROSS_HTTPREQUEST_B95B43A3840E428D80A9CC72723877B3_H_INCLUDED

# include "NullRpc.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_PROTOCOL(IObjParser);
NNTDECL_PRIVATE_HEAD(HttpRequest);

@interface HttpRequest : NullRpc {
    
    //! method, default is POST.
    NSString *method;
    
    //! cookies urls. it will be clean before each call.
    NSArray* cookieURLs;
    
    NNTDECL_PRIVATE(HttpRequest);
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

NNT_EXTERN NSString* HttpRequestGetMethod(Class cls);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif // objc-cxx

# endif // objc

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cross)
NNT_BEGIN_NS(rpc)

class HttpRequest
: public NullImplementation
{
public:
    
    HttpRequest();
    virtual ~HttpRequest();

};

NNT_END_NS
NNT_END_NS
NNT_END_NS

# endif // cxx

# endif