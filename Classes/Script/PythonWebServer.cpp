
# include "Core.h"
# include "PythonWebServer.h"
# include "python.site.prv/pynnt.h"
# include "Python+NNT.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(python)

NNTDECL_PRIVATE_BEGIN_CXX(HttpRequest)

void init()
{

}

void dealloc()
{

}

script::Python py;

NNTDECL_PRIVATE_END_CXX

HttpRequest::HttpRequest()
{
    NNTDECL_PRIVATE_CONSTRUCT(HttpRequest);
}

HttpRequest::~HttpRequest()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool HttpRequest::process()
{
    return false;
}

WebRequest::WebRequest()
{
    
}

WebRequest::~WebRequest()
{
    
}

FileRequest::FileRequest()
{
    
}

FileRequest::~FileRequest()
{
    
}

bool FileRequest::process()
{
    return true;
}

NNT_END_NS
NNT_END_CXX